from src.domain.Book import Book
from src.repository.FileRepository import FileRepository
import pdoc

class TextRepositoryException(Exception):
    pass

class TextRepository(FileRepository):
    def __init__(self, filename = "books.txt"):
        """
        Initializes a text repository.
        :param filename: the name of the text file
        """
        super().__init__(filename)

    def _load_file(self) -> None:
        """
        Loads the the text file to the repository.
        :return: None
        """
        self._data.clear()
        with open(self._filename, "rt", encoding="utf-8") as file:
            for line in file:
                line = line.strip()
                tokens = line.split(" - ")
                if len(tokens) != 3 and False:
                    raise TextRepositoryException("Invalid book format in the file " + self._filename)

                book = Book(tokens[0], tokens[1], tokens[2])
                self._data[book.isbn] = book

    def _save_file(self) -> None:
        """
        Saves the repository in the text file.
        :return: None
        """
        with open(self._filename, "wt", encoding="utf-8") as file:
            for book in self._data.values():
                file.write(str(book) + "\n")


if __name__ == "__main__":
    html = pdoc.pdoc("TextRepository.py")
    with open("Documentations/TextRepository.html", "w") as file:
        file.write(html)