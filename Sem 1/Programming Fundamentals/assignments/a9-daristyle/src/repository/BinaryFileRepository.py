from src.repository.FileRepository import FileRepository
from src.repository.MemoryRepository import MemoryRepository
import gzip
import pickle

class BinaryFileRepository(FileRepository):
    def _save_file(self):
        with gzip.open(self._filename, "wb") as file:
            pickle.dump(self._data, file)

    def _load_file(self):
        try:
            with gzip.open(self._filename, "rb") as file:
                self._data = pickle.load(file)
        except EOFError:
            self._data = {}