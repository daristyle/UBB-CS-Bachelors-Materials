from src.repository.FileRepository import FileRepository
from src.repository.MemoryRepository import MemoryRepository
from src.domain.Book import Book
import json
import pdoc

class JSONRepository(FileRepository):
    def __init__(self, filename = "books.json"):
        """
        Initializes a JSON file repository.
        :param filename: the name of the JSON  file
        """
        super().__init__(filename)

    def _load_file(self) -> None:
        """
        Loads the JSON file to the repository.
        :return: None
        """
        try:
            self._data = {}
            with open(self._filename, "rt", encoding="utf-8") as file:
                data_dict = json.load(file)
                for book in data_dict:
                    MemoryRepository.add(self, Book.from_dict(book))
        except json.JSONDecodeError:
            self._data = {}

    def _save_file(self) -> None:
        """
        Saves the repository to a JSON file
        :return: None
        """
        with open(self._filename, "wt", encoding="utf-8") as file:
            data_dict = []
            for book in self._data.values():
                data_dict.append(book.to_dict())
            json.dump(data_dict, file)


if __name__ == "__main__":
    html = pdoc.pdoc("JSONRepository.py")
    with open("Documentations/JSONRepository.html", "w") as file:
        file.write(html)