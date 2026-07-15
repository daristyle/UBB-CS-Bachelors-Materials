from src.domain.Book import Book
from src.repository.MemoryRepository import DuplicateISBN
from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextRepository import TextRepository
from src.repository.BinaryRepository import BinaryRepository
from src.repository.JSONRepository import JSONRepository
from src.repository.SQLRepository import SQLRepository

def test_repository(repo):
    book = Book("2","1984", "George Orwell")
    repo.add(book)

    added = False
    for b in repo:
        if b == book:
            added = True

    assert added

    try:
        repo.add(book)
        assert False
    except DuplicateISBN:
        pass
    except:
        assert False


if __name__ == "__main__":
    test_repository(MemoryRepository())
    test_repository(TextRepository())
    test_repository(BinaryRepository())
    test_repository(JSONRepository())
    test_repository(SQLRepository())
