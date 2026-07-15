from src.repository.FileRepository import FileRepository
import gzip
import pickle
import pdoc

class BinaryRepository(FileRepository):
    def __init__(self, filename = "books.bin"):
        """
        Initializes a binary repository.
        :param filename: the name of the binary file
        """
        super().__init__(filename)

    def _load_file(self) -> None:
        """
        Loads the binary file to the repository.
        :return: None
        """
        try:
            with gzip.open(self._filename, "rb") as file:
                self._data = pickle.load(file)
        except EOFError:
            self._data = {}

    def _save_file(self) -> None:
        """
        Saves the repository in the binary file.
        :return: None
        """
        with gzip.open(self._filename, "wb") as file:
            pickle.dump(self._data, file)


if __name__ == "__main__":
    html = pdoc.pdoc("BinaryRepository.py")
    with open("Documentations/BinaryRepository.html", "w") as file:
        file.write(html)