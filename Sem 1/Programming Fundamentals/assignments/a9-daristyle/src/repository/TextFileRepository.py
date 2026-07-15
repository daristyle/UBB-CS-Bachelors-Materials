from src.repository.FileRepository import FileRepository
from src.repository.MemoryRepository import MemoryRepository

class TextFileRepository(FileRepository):
    def _save_file(self):
        with open(self._filename, "wt", encoding="utf-8") as file:
            for obj in self._data.values():
                file.write(str(obj) + "\n")

    def _load_file(self):
        self._data.clear()
        with open(self._filename, "rt", encoding="utf-8") as file:
            for line in file:
                line = line.strip()

                MemoryRepository.add(self, self._type.from_str(line))