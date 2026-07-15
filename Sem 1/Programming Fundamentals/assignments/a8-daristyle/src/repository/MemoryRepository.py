from src.domain.Book import Book
import pdoc

class DuplicateISBN(Exception):
    pass

class RepositoryIterator:
    def __init__(self, elements):
        self._elements = list(elements)
        self._index = -1

    def __next__(self):
        self._index += 1

        if self._index >= len(self._elements):
            raise StopIteration()

        return self._elements[self._index]

class MemoryRepository:
    def __init__(self):
        """
        Initialize the repository.
        """
        self._data = {}

    def __iter__(self) -> RepositoryIterator:
        """
        :return: An iterator over the repository elements.
        """
        return RepositoryIterator(self._data.values())

    def __len__(self) -> int:
        """
        :return: The number of elements in the repository.
        """
        return len(self._data)

    def add(self, book: Book) -> None:
        """
        Add a book to the repository.
        :param book: book to be added.
        :return: None
        Raises DuplicateISBN if book already exists.
        """
        if book.isbn in self._data:
            raise DuplicateISBN("Duplicate ISBN: " + str(book.isbn))

        self._data[book.isbn] = book

    def remove(self, book: Book) -> None:
        """
        Remove a book from the repository.
        :param book: book to be removed.
        :return: None
        """
        self._data.pop(book.isbn)

if __name__ == "__main__":
    html = pdoc.pdoc("MemoryRepository.py")
    with open("Documentations/MemoryRepository.html", "w") as file:
        file.write(html)