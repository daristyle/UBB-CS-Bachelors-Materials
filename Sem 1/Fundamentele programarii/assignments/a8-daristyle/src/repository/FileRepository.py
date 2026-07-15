from src.domain.Book import Book
from src.repository.MemoryRepository import MemoryRepository
from pathlib import Path
import pdoc

class FileRepository(MemoryRepository):
    def __init__(self, filename: str):
        """
        Initialize a file repository.
        :param filename: the name of the file
        """
        super().__init__()
        self._filename = filename
        self._init_file()
        self._load_file()

    def add(self, book: Book) -> None:
        """
        Adds a book to the repository.
        :param book: book to be added.
        :return: None
        """
        super().add(book)
        self._save_file()

    def remove(self, book: Book) -> None:
        """
        Removes a book from the repository.
        :param book: book to be removed.
        :return: None
        """
        super().remove(book)
        self._save_file()

    def _init_file(self) -> None:
        """
        Creates a file if it doesn't exist.
        :return: None
        """
        Path(self._filename).touch(exist_ok=True)

    def _load_file(self) -> None:
        """
        Loads the repository from the file.
        This method should be implemented by he classes that inherit this one
        :return: None
        """
        pass

    def _save_file(self) -> None:
        """
        Saves the file from the repository.
        This method should be implemented by he classes that inherit this one
        :return: None
        """
        pass


if __name__ == "__main__":
    html = pdoc.pdoc("FileRepository.py")
    with open("Documentations/FileRepository.html", "w") as file:
        file.write(html)