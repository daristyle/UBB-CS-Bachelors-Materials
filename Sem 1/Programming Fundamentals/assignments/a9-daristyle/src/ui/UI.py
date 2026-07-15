from datetime import date

from texttable import Texttable

from src.domain.Book import Book
from src.domain.Client import Client
from src.domain.Rental import Rental
from src.repository.MemoryRepository import MemoryRepository
from src.services.Services import Services

class UI:
    def __init__(self, book_repo: MemoryRepository, client_repo: MemoryRepository, rental_repo: MemoryRepository):
        self._services = Services(book_repo, client_repo, rental_repo)

    def _print_main_menu(self):
        print("=====MAIN MENU======")
        print("1. Books menu")
        print("2. Clients menu")
        print("3. Manage Rentals")
        print("0. Exit")

    def _print_books_menu(self):
        print("=====BOOKS MENU======")
        print("1. Add a book")
        print("2. Delete a book")
        print("3. Edit a book")
        print("4. List all books")
        print("5. Search by ID")
        print("6. Search by title")
        print("7. Search by author")
        print("0. Back")

    def _print_client_menu(self):
        print("=====CLIENT MENU======")
        print("1. Add a client")
        print("2. Delete a client")
        print("3. Edit a client")
        print("4. List all clients")
        print("5. Search by ID")
        print("6. Search by name")
        print("0. Back")

    def _print_rental_menu(self):
        print("=====RENTAL MENU======")
        print("1. Rent a book")
        print("2. Return a book")
        print("3. List all rentals")
        print("0. Back")

    def _add_book(self, book: Book):
        self._services.add_book(book)
        print("Book added")

    def _remove_book(self, book: Book):
        self._services.remove_book(book)
        print("Book removed")

    def _edit_book(self, book: Book):
        self._services.update_book(book)
        print("Book edited")

    def _list_books(self, l):
        tt = Texttable()
        tt.add_row(["No.","Book ID", "Title", "Author"])
        i = 0
        for book in l:
            i += 1
            tt.add_row([i, book.id, book.title, book.author])

        print(tt.draw())

    def _list_all_books(self):
        self._list_books(self._services.get_books())

    def _list_books_id(self, book_id: int):
        self._list_books(self._services.search_book_id(book_id))

    def _list_books_title(self, title: str):
        self._list_books(self._services.search_book_title(title))

    def _list_books_author(self, author: str):
        self._list_books(self._services.search_book_author(author))

    def _add_client(self, client: Client):
        self._services.add_client(client)
        print("Client added")

    def _remove_client(self, client: Client):
        self._services.remove_client(client)
        print("Client removed")

    def _edit_client(self, client: Client):
        self._services.update_client(client)
        print("Client edited")

    def _list_clients(self, l):
        tt = Texttable()
        tt.add_row(["No.", "Client ID", "Name"])
        i = 0
        for client in l:
            i += 1
            tt.add_row([i, client.id, client.name])

        print(tt.draw())

    def _list_all_clients(self):
        self._list_clients(self._services.get_clients())

    def _list_clients_id(self, clients_id: int):
        self._list_clients(self._services.search_client_id(clients_id))

    def _list_clients_name(self, name: str):
        self._list_clients(self._services.search_client_name(name))

    @staticmethod
    def _get_string(message: str):
        return input(message)

    @staticmethod
    def _get_int(message: str):
        s = input(message).strip()
        if not s.isdigit():
            raise ValueError("Invalid input")
        return int(s)

    def _get_book(self):
        book_id = self._get_int("Book ID: ")
        title = self._get_string("Title: ")
        author = self._get_string("Author: ")

        return Book(book_id, title, author)

    def _get_client(self):
        clients_id = self._get_int("Client ID: ")
        name = self._get_string("Name: ")

        return Client(clients_id, name)

    def _rent(self):
        book_id = self._get_int("Book ID: ")
        client_id = self._get_int("Client ID: ")
        start_date = self._get_string("Date(YYYY-MM-DD): ")
        rent_id = self._get_int("Rent ID(0 if you do not want to provide one): ")


        self._services.rent_book(book_id, client_id, date.fromisoformat(start_date), rent_id)

        print("Book rented")

    def _return(self):
        rent_id = self._get_int("Rent ID: ")
        end_date = self._get_string("Date(YYYY-MM-DD) or -1 for today: ")

        if end_date.strip() == "-1":
            self._services.return_book(rent_id)
        else:
            self._services.return_book(rent_id, date.fromisoformat(end_date))

        print("Book returned")

    def _list_all_rentals(self):
        l = self._services.get_rentals()
        tt = Texttable()
        tt.add_row(["No.", "Rental ID", "Book ID", "Client ID", "Rent Date", "Return Date"])
        i = 0
        for rental in l:
            i += 1
            tt.add_row([i, rental.id, rental.book_id, rental.client_id, rental.rental_date, rental.return_date if rental.return_date != date(1, 1, 1) else "Not returned yet"])

        print(tt.draw())

    @staticmethod
    def _print_invalid():
        print("Invalid input")

    def start(self):
        command_books = {"1": self._add_book, "2": self._remove_book, "3": self._edit_book, "4": self._list_all_books,
                         "5": self._list_books_id, "6": self._list_books_title, "7": self._list_books_author}
        command_clients = {"1": self._add_client, "2":self._remove_client, "3": self._edit_client, "4": self._list_all_clients,
                           "5": self._list_clients_id, "6": self._list_clients_name}
        exited = False
        while not exited:
            self._print_main_menu()
            op = self._get_string("Option: ")
            try:
                if op == "1":
                    self._print_books_menu()
                    op = self._get_string("Option: ")
                    if op in ["1", "2", "3"]:
                        book = self._get_book()
                        command_books[op](book)
                    elif op == "4":
                        command_books[op]()
                    elif op == "5":
                        id = self._get_int("Book ID: ")
                        command_books[op](id)
                    elif op == "6":
                        title = self._get_string("Title: ")
                        command_books[op](title)
                    elif op == "7":
                        author = self._get_string("Author: ")
                        command_books[op](author)
                    elif op != "0":
                        self._print_invalid()
                elif op == "2":
                    self._print_client_menu()
                    op = self._get_string("Option: ")
                    if op in ["1", "2", "3"]:
                        client = self._get_client()
                        command_clients[op](client)
                    elif op == "4":
                        command_clients[op]()
                    elif op == "5":
                        id = self._get_int("Client ID: ")
                        command_clients[op](id)
                    elif op == "6":
                        name = self._get_string("Name: ")
                        command_clients[op](name)
                    elif op != "0":
                        self._print_invalid()
                elif op == "3":
                    self._print_rental_menu()
                    op = self._get_string("Option: ")
                    if op == "1":
                        self._rent()
                    elif op == "2":
                        self._return()
                    elif op == "3":
                        self._list_all_rentals()
                    elif op != "0":
                        self._print_invalid()
                elif op == "0":
                    exited = True
                else:
                    self._print_invalid()
            except Exception as e:
                print(e)