from src.domain.IDObject import IDObject

class BookException(Exception):
    pass

class Book(IDObject):
    def __init__(self, id: int, title: str, author: str):
        super().__init__(id)

        self._title = title.strip()
        self._author = author.strip()

    @property
    def title(self) -> str:
        return self._title

    @property
    def author(self) -> str:
        return self._author

    def __str__(self):
        return str(self.id) + " - " + self.title + " - " + self.author

    @staticmethod
    def from_str(s: str) -> "Book":
        tokens = s.split(" - ")
        if len(tokens) != 3 or not tokens[0].isdigit():
            raise BookException("Invalid string format for a Book")

        return Book(int(tokens[0]), tokens[1], tokens[2])

    def __eq__(self, other: "Book") -> bool:
        return self.id == other.id and self.title.strip().lower() == other.title.strip().lower() and self.author.strip().lower() == other.author.strip().lower()

