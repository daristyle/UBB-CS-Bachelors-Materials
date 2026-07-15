from unittest import TestCase
from src.repository.MemoryRepository import MemoryRepository
from src.services.BookService import BookService
from src.domain.Book import Book

class TestBookService(TestCase):
    def test_book_service_1(self):
        service = BookService(MemoryRepository(Book))
        book1 = Book(1, "a", "b")
        book2 = Book(2, "c", "d")
        book3 = Book(3, "e", "f")

        service.add(book1)
        service.add(book2)
        service.add(book3)

        check = 0
        for book in service.get_all():
            if book == book1:
                check |= 1
            elif book == book2:
                check |= 2
            elif book == book3:
                check |= 4
        self.assertEqual(7, check)

        service.remove(book1)

        check = 0
        for book in service.get_all():
            if book == book1:
                check |= 1
            elif book == book2:
                check |= 2
            elif book == book3:
                check |= 4
        self.assertEqual(6, check)

        book2u = Book(2, "u", "u")
        service.update(book2u)

        check = 0
        for book in service.get_all():
            if book == book1:
                check |= 1
            elif book == book2u:
                check |= 2
            elif book == book3:
                check |= 4
        self.assertEqual(6, check)


