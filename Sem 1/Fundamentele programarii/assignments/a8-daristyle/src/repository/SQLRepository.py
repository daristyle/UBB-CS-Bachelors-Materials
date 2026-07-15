from src.domain.Book import Book
from src.repository.FileRepository import FileRepository
from src.repository.MemoryRepository import MemoryRepository
import sqlite3
import pdoc

class SQLRepository(FileRepository):
    def __init__(self, filename = "books.db"):
        """
        Initializes a SQL file repository.
        :param filename: the name of the database file
        """
        self._filename = filename
        self.__create_table()
        super().__init__(filename)

    def __create_table(self) -> None:
        """
        Creates the database table if it doesn't exist.
        :return: None
        """
        with sqlite3.connect(self._filename) as conn:
            conn.cursor().execute('''
                CREATE TABLE IF NOT EXISTS books (
                    isbn TEXT PRIMARY KEY,
                    title TEXT,
                    author TEXT
                    )
            ''')

            conn.commit()

    def add(self, book: Book) -> None:
        """
        Adds a book to the repository, only inserts the book in the database instead of erasing and rewriting the whole database.
        :param book: book to add to the repository
        :return: None
        """
        MemoryRepository.add(self, book)

        with sqlite3.connect(self._filename) as conn:
            conn.cursor().execute('''
                INSERT INTO books (isbn, title, author)
                VALUES (?, ?, ?)
            ''', (book.isbn, book.title, book.author)
            )
            conn.commit()

    def remove(self, book: Book) -> None:
        """
        Removes a book from the repository, only deletes the book from the database, instead of erasing and rewriting the whole database.
        :param book: book to be removed from the repository
        :return: None
        """
        MemoryRepository.remove(self, book)

        with sqlite3.connect(self._filename) as conn:
            conn.cursor().execute('''
                DELETE FROM books WHERE isbn = ?
            ''', (book.isbn,)
            )#python is dumb, so it needs a trailing comma to realize that (book.isbn)is a tuple not just some operation with parentheses

            conn.commit()

    def _load_file(self) -> None:
        """
        Loads the database to the repository.
        :return: None
        """
        with sqlite3.connect(self._filename) as conn:
            cursor = conn.cursor()

            cursor.execute('''
                SELECT isbn, title, author FROM books
            ''')

            self._data = {}
            for row in cursor.fetchall():
                MemoryRepository.add(self, Book(row[0], row[1], row[2]))

    def _save_file(self) -> None:
        """
        Saves the repository to the database.
        :return: None
        """
        with sqlite3.connect(self._filename) as conn:
            cursor = conn.cursor()
            for book in self._data.values():
                cursor.execute('''
                    INSERT INTO books (isbn, title, author)
                    Values (?, ?, ?)
                ''', (book.isbn, book.title, book.author)
                )

            conn.commit()


if __name__ == "__main__":
    html = pdoc.pdoc("SQLRepository.py")
    with open("Documentations/SQLRepository.html", "w") as file:
        file.write(html)