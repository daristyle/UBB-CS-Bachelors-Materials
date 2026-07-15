from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextRepository import TextRepository
from src.repository.BinaryRepository import BinaryRepository
from src.repository.JSONRepository import JSONRepository
from src.repository.SQLRepository import SQLRepository
from src.domain.Book import Book
from faker import Faker
from enum import Enum

class OperationType(Enum):
    ADD = 1
    REMOVE = 2

class Operation:
    def __init__(self, book: Book, type: OperationType):
        self._book = book
        self._type = type

    @property
    def book(self) -> Book:
        return self._book

    @property
    def type(self) -> OperationType:
        return self._type

class ServiceError(Exception):
    pass

class Services:
    def __init__(self, repository = MemoryRepository()):
        self._repo = repository
        self._history = []

        if len(self._repo) == 0:
            fake = Faker()
            for _ in range(10):
                self._repo.add(Book(fake.isbn13(), fake.sentence(nb_words=4).rstrip(".?!"), fake.name()))

    def add(self, book: Book):
        self._repo.add(book)
        self._history.append([Operation(book, OperationType.ADD)])

    def get_all(self):
        l = []
        for book in self._repo:
            l.append(book)

        return l

    def filter_starting_with(self, word: str):
        l = []
        for book in self._repo:
            if book.title.split(" ")[0].strip(",").lower() == word.lower():
                l.append(Operation(book, OperationType.REMOVE))
                self._repo.remove(book)

        self._history.append(l)

    def undo(self) -> None:
        if len(self._history) == 0:
            raise ServiceError("Nothing to undo")

        l = self._history.pop()

        for op in l:
            if op.type == OperationType.ADD:
                self._repo.remove(op.book)
            else:
                self._repo.add(op.book)
