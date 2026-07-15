from pathlib import Path
from src.domain.IDObject import IDObject
from src.repository.MemoryRepository import MemoryRepository

class FileRepository(MemoryRepository):
    def __init__(self, type, filename: str):
        super().__init__(type)

        self._filename = filename
        self._init_file()

        self._load_file()

    def add(self, obj: IDObject) -> None:
        super().add(obj)
        self._save_file()

    def remove_id(self, obj_id: int) -> None:
        super().remove_id(obj_id)
        self._save_file()

    def _init_file(self):
        Path(self._filename).touch(exist_ok=True)

    def _load_file(self):
        pass

    def _save_file(self):
        pass