from src.domain.Book import Book
from src.domain.Client import Client
from src.domain.Rental import RentalException, Rental
from src.repository.MemoryRepository import MemoryRepository, RepositoryException
from src.services.BookService import BookService
from src.services.ClientService import ClientService
from src.services.RentalService import RentalService
from src.services.UndoService import UndoService, FunctionCall, Operation
from datetime import date
from faker import Faker
import random


class Services:
    def __init__(self, book_repo: MemoryRepository, client_repo: MemoryRepository, rental_repo: MemoryRepository):
        self._book_service = BookService(book_repo)
        self._client_service = ClientService(client_repo)
        self._rental_service = RentalService(rental_repo)
        self._undo_service = UndoService()

        faker = Faker()
        while len(self._book_service) < 25:
            id = faker.random_int(1, 10**6-1)
            title = faker.sentence(nb_words=4).rstrip(" ,.?!")
            author = faker.name()
            try:
                self._book_service.add(Book(id, title, author))
            except RepositoryException:
                pass
        while len(self._client_service) < 25:
            id = faker.random_int(1, 10**6-1, 1)
            name = faker.name()
            try:
                self._client_service.add(Client(id, name))
            except RepositoryException:
                pass

        if len(self._rental_service) < 20:
            clients_id = []
            books_id = []
            for obj in self._client_service.get_all():
                clients_id.append(obj.id)
            for obj in self._book_service.get_all():
                books_id.append(obj.id)

            random.shuffle(books_id)
            for i in range(0, 20):
                date1 = date.fromisoformat(faker.date())
                id = faker.random_int(1, 10**6-1)
                self.rent_book(books_id[i], clients_id[i], date1, id)

            for obj in self._rental_service.get_all():
                if random.random() < 0.5:
                    self.return_book(obj.id, date.today())


    def __do_nothing(self):
        pass

    def add_book(self, book: Book):
        """
        Adds a new book to the repository.
        :param book: book to be added
        :return: None
        """
        self._book_service.add(book)

        undo = FunctionCall(self._book_service.remove,book)
        redo = FunctionCall(self._book_service.add,book)
        self._undo_service.record([Operation(undo, redo)])

    def remove_book(self, book: Book):
        """
        Removes a book from the repository.
        :param book: book to be removed
        :return: None
        """
        old_book = self._book_service.get_by_id(book.id)
        if old_book is None:
            func = FunctionCall(self.__do_nothing)
            self._undo_service.record([Operation(func, func)])
            return

        self._book_service.remove(book)

        l = []
        undo = FunctionCall(self._book_service.add,book)
        redo = FunctionCall(self._book_service.remove,book)
        l.append(Operation(undo, redo))

        for rental in self._rental_service.get_all():
            if rental.book_id == book.id:
                self._rental_service.remove(rental)

                undo = FunctionCall(self._rental_service.add, rental)
                redo = FunctionCall(self._rental_service.remove,rental)
                l.append(Operation(undo, redo))

        self._undo_service.record(l)

    def update_book(self, book: Book):
        """
        Updates a book in the repository.
        :param book: the new book
        :return: None
        """
        old_book = self._book_service.get_by_id(book.id)
        if old_book is None:
            func = FunctionCall(self.__do_nothing)
            self._undo_service.record([Operation(func, func)])
            return

        self._book_service.update(book)

        undo = FunctionCall(self._book_service.update,old_book)
        redo = FunctionCall(self._book_service.update,book)
        self._undo_service.record([Operation(undo, redo)])

    def get_books(self):
        """
        Returns a list of all books.
        """
        return self._book_service.get_all()

    def add_client(self, client: Client):
        """
        Adds a new client to the repository.
        :param client: client to be added
        :return: None
        """
        self._client_service.add(client)

        undo = FunctionCall(self._client_service.remove, client)
        redo = FunctionCall(self._client_service.add, client)
        self._undo_service.record([Operation(undo, redo)])

    def remove_client(self, client: Client):
        """
        Removes a client from the repository.
        :param client: client to be removed
        :return: None
        """
        old_client = self._client_service.get_by_id(client.id)
        if old_client is None:
            func = FunctionCall(self.__do_nothing)
            self._undo_service.record([Operation(func, func)])
            return

        self._client_service.remove(client)

        l = []
        undo = FunctionCall(self._client_service.add, client)
        redo = FunctionCall(self._client_service.remove, client)
        l.append(Operation(undo, redo))

        for rental in self._rental_service.get_all():
            if rental.client_id == client.id:
                self._rental_service.remove(rental)

                undo = FunctionCall(self._rental_service.add, rental)
                redo = FunctionCall(self._rental_service.remove, rental)
                l.append(Operation(undo, redo))

        self._undo_service.record(l)


    def update_client(self, client: Client):
        """
        Updates a client in the repository.
        :param client: the new client
        :return: None
        """
        old_client = self._client_service.get_by_id(client.id)
        if old_client is None:
            func = FunctionCall(self.__do_nothing)
            self._undo_service.record([Operation(func, func)])
            return

        self._client_service.update(client)

        undo = FunctionCall(self._client_service.update, old_client)
        redo = FunctionCall(self._client_service.update, client)
        self._undo_service.record([Operation(undo, redo)])

    def get_clients(self):
        """
        Returns a list of all clients.
        """
        return self._client_service.get_all()

    def get_rentals(self):
        return self._rental_service.get_all()

    def rent_book(self, book_id: int, client_id: int, rent_date = date.today(), rent_id = -1):
        if len(self._book_service.search_id(book_id)) <= 0:
            raise RentalException("Book not found")
        if len(self._client_service.search_id(client_id)) <= 0:
            raise RentalException("Client not found")
        if self._rental_service.is_rented(book_id):
            raise RentalException("Book already rented")

        self._rental_service.rent_book(book_id, client_id, rent_date, rent_id)

    def return_book(self, rent_id: int, return_date = date.today()):
        self._rental_service.return_book(rent_id, return_date)

    def search_book_id(self, book_id: int):
        return self._book_service.search_id(book_id)

    def search_book_title(self, book_title: str):
        return self._book_service.search_title(book_title)

    def search_book_author(self, book_author: str):
        return self._book_service.search_author(book_author)

    def search_client_id(self, client_id: int):
        return self._client_service.search_id(client_id)

    def search_client_name(self, client_name: str):
        return self._client_service.search_name(client_name)

    def undo(self):
        self._undo_service.undo()

    def redo(self):
        self._undo_service.redo()

    @staticmethod
    def _get_stat(objects: list, property1, increment_value, l, property2):
        val = {}
        for x in l:
            val[property2(x)] = 0

        for obj in objects:
            val[property1(obj)] = increment_value(obj)

        return sorted(l, key=lambda x: val[property2(x)], reverse=True)

    def most_rented_books(self):
        return self._get_stat(self._rental_service.get_all(), property1=lambda x: x.book_id, increment_value=lambda x: 1, l=self._book_service.get_all(), property2=lambda x: x.id)

    def most_active_clients(self):
        return self._get_stat(self._rental_service.get_all(), property1=lambda x: x.client_id, increment_value=lambda x: (x.return_date - x.rental_date).days + 1 if x.return_date != date(1, 1, 1) else (date.today() - x.rental_date).days + 1, l=self._client_service.get_all(), property2=lambda x: x.id)

    def most_rented_authors(self):
        l = self._get_stat(self._rental_service.get_all(), property1=lambda x: x.book_id, increment_value=lambda x: 1, l=self._book_service.get_all(), property2=lambda x: x.id)
        return [book.author for book in l]