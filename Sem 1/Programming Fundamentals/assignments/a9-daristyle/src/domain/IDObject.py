from typing import Self

class IDObjectException(Exception):
    pass

class IDObject:
    def __init__(self, id: int):
        if not id.is_integer() or id < 0:
            raise IDObjectException("ID must be a positive integer")

        self._id = id

    @property
    def id(self) -> int:
        return self._id

    def __str__(self):
        pass

    @staticmethod
    def from_str(s: str) -> Self:
        pass
