import random

from src.domain.Book import Book
from src.domain.Client import Client
from src.domain.Rental import RentalException
from src.repository.MemoryRepository import MemoryRepository, RepositoryException
from src.services.BookService import BookService
from src.services.ClientService import ClientService
from src.services.RentalService import RentalService
from datetime import date
from faker import Faker

class Services:
    def __init__(self, book_repo: MemoryRepository, client_repo: MemoryRepository, rental_repo: MemoryRepository):
        self._book_service = BookService(book_repo)
        self._client_service = ClientService(client_repo)
        self._rental_service = RentalService(rental_repo)

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



    def add_book(self, book: Book):
        """
        Adds a new book to the repository.
        :param book: book to be added
        :return: None
        """
        self._book_service.add(book)

    def remove_book(self, book: Book):
        """
        Removes a book from the repository.
        :param book: book to be removed
        :return: None
        """
        self._book_service.remove(book)

    def update_book(self, book: Book):
        """
        Updates a book in the repository.
        :param book: the new book
        :return: None
        """
        self._book_service.update(book)

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

    def remove_client(self, client: Client):
        """
        Removes a client from the repository.
        :param client: client to be removed
        :return: None
        """
        self._client_service.remove(client)

    def update_client(self, client: Client):
        """
        Updates a client in the repository.
        :param client: the new client
        :return: None
        """
        self._client_service.update(client)

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
