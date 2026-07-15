from datetime import date

from src.domain.Book import Book
from src.domain.Client import Client
from src.domain.Rental import Rental
from src.ui.UI import UI
from src.services.Services import Services
from src.repository.MemoryRepository import MemoryRepository
import customtkinter as ctk
from CTkTable import *

class GUI(UI, ctk.CTk):
    def __init__(self, book_repo: MemoryRepository, client_repo: MemoryRepository, rental_repo: MemoryRepository):
        UI.__init__(self, book_repo, client_repo, rental_repo)
        ctk.CTk.__init__(self, fg_color="#530000")

        self.content_frame = ctk.CTkFrame(self, fg_color="transparent")
        self.content_frame.pack(fill="both", expand=True)

        self.title("Library")
        self.geometry("600x300")
        self._main_menu()

    def clear_frame(self):
        for widget in self.content_frame.winfo_children():
            widget.destroy()

    def _main_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Main Menu", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx = 300, pady = 70)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Book Menu", font =("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._book_menu)
        self.btn1.grid(row = 1, column=0)

        self.btn2 = ctk.CTkButton(self.content_frame, text="Client Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._client_menu)
        self.btn2.grid(row=2, column=0, pady=50)

        self.btn3 = ctk.CTkButton(self.content_frame, text="Rental Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._rental_menu)
        self.btn3.grid(row=3, column=0)

        self.btn4 = ctk.CTkButton(self.content_frame, text="Statisitcs", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._statistics_menu)
        self.btn4.grid(row=4, column=0, pady=50)

        self.btn5 = ctk.CTkButton(self.content_frame, text="Undo", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._undo)
        self.btn5.grid(row=5, column=0)

        self.btn6 = ctk.CTkButton(self.content_frame, text="Redo", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._redo)
        self.btn6.grid(row=6, column=0, pady=50)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Exit", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self.close)
        self.btn0.grid(row=7, column=0)

    def _command_finished_menu(self, str):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text=str, font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=4, column=0)

    def _book_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Book Menu", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Add book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._add_book_menu)
        self.btn1.grid(row=1, column=0)

        self.btn2 = ctk.CTkButton(self.content_frame, text="Delete book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._delete_book_menu)
        self.btn2.grid(row=2, column=0, pady=30)

        self.btn3 = ctk.CTkButton(self.content_frame, text="Edit book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._edit_book_menu)
        self.btn3.grid(row=3, column=0)

        self.btn4 = ctk.CTkButton(self.content_frame, text="List all books", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_all_books)
        self.btn4.grid(row=4, column=0, pady=30)

        self.btn5 = ctk.CTkButton(self.content_frame, text="Search by ID", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_books_id_menu)
        self.btn5.grid(row=5, column=0)

        self.btn6 = ctk.CTkButton(self.content_frame, text="Search by Title", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_books_title_menu)
        self.btn6.grid(row=6, column=0, pady=30)

        self.btn7 = ctk.CTkButton(self.content_frame, text="Search by Author", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_books_author_menu)
        self.btn7.grid(row=7, column=0)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Back", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=8, column=0, pady=30)

    def _add_book_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Add book", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                        font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)


        self.entry_title = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text= "Title",
                                        font=("Arial", 40))
        self.entry_title.grid(row=2, column=0, pady = 30)


        self.entry_author = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Author",
                                        font=("Arial", 40))
        self.entry_author.grid(row=3, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Add book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._add_book)
        self.btn1.grid(row=4, column=0, pady = 30)

    def _add_book(self):
        id = self.entry_id.get()
        title = self.entry_title.get()
        author = self.entry_author.get()

        if not id or not title or not author or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        try:
            book = Book(id, title, author)

            self._services.add_book(book)

            self._command_finished_menu("Book added successfully")
        except Exception:
            self._command_finished_menu("Duplicate ID")

    def _delete_book_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Delete book", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                        font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)


        self.entry_title = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text= "Title",
                                        font=("Arial", 40))
        self.entry_title.grid(row=2, column=0, pady = 30)


        self.entry_author = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Author",
                                        font=("Arial", 40))
        self.entry_author.grid(row=3, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Add book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._delete_book)
        self.btn1.grid(row=4, column=0, pady = 30)

    def _delete_book(self):
        id = self.entry_id.get()
        title = self.entry_title.get()
        author = self.entry_author.get()

        if not id or not title or not author or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        try:
            book = Book(id, title, author)

            self._services.remove_book(book)

            self._command_finished_menu("Book disappeared")
        except Exception:
            self._command_finished_menu("Error")

    def _edit_book_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Edit book", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                        font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)


        self.entry_title = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text= "Title",
                                        font=("Arial", 40))
        self.entry_title.grid(row=2, column=0, pady = 30)


        self.entry_author = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Author",
                                        font=("Arial", 40))
        self.entry_author.grid(row=3, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Edit book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._edit_book)
        self.btn1.grid(row=4, column=0, pady = 30)

    def _edit_book(self):
        id = self.entry_id.get()
        title = self.entry_title.get()
        author = self.entry_author.get()

        if not id or not title or not author or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        try:
            book = Book(id, title, author)

            self._services.update_book(book)

            self._command_finished_menu("Book edited successfully")
        except Exception:
            self._command_finished_menu("Error")

    def _show_books(self, l: list[Book]):
        self.clear_frame()

        value = [["No. crt.", "ID", "Title", "Author"]]
        i = 1
        for book in l:
            value.append([str(i), str(book.id), book.title, book.author])
            i += 1

        self.table = CTkTable(master= self.content_frame, values=value)
        self.table.grid(row=0, column=0, padx = 50, pady=40)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=1, column=0)

    def _list_all_books(self):
        self._show_books(self._services.get_books())

    def _list_books_id_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Search books by ID", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                     font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Search", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_books_id)
        self.btn1.grid(row=2, column=0, pady=30)

    def _list_books_id(self):
        id = self.entry_id.get()

        if not id or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        self._show_books(self._services.search_book_id(id))

    def _list_books_title_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Search books by title", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_title = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Title",
                                     font=("Arial", 40))
        self.entry_title.grid(row=1, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Search", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_books_title)
        self.btn1.grid(row=2, column=0, pady=30)

    def _list_books_title(self):
        title = self.entry_title.get()

        if not title:
            self._command_finished_menu("Invalid input")
            return

        self._show_books(self._services.search_book_title(title))

    def _list_books_author_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Search books by author", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_author = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Author",
                                     font=("Arial", 40))
        self.entry_author.grid(row=1, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Search", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_books_author)
        self.btn1.grid(row=2, column=0, pady=30)

    def _list_books_author(self):
        author = self.entry_author.get()

        if not author:
            self._command_finished_menu("Invalid input")
            return

        self._show_books(self._services.search_book_author(author))
        
    def _client_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Client Menu", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Add client", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._add_client_menu)
        self.btn1.grid(row=1, column=0)

        self.btn2 = ctk.CTkButton(self.content_frame, text="Delete client", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._delete_client_menu)
        self.btn2.grid(row=2, column=0, pady=30)

        self.btn3 = ctk.CTkButton(self.content_frame, text="Edit client", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._edit_client_menu)
        self.btn3.grid(row=3, column=0)

        self.btn4 = ctk.CTkButton(self.content_frame, text="List all clients", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_all_clients)
        self.btn4.grid(row=4, column=0, pady=30)

        self.btn5 = ctk.CTkButton(self.content_frame, text="Search by ID", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_clients_id_menu)
        self.btn5.grid(row=5, column=0)

        self.btn6 = ctk.CTkButton(self.content_frame, text="Search by Name", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_clients_name_menu)
        self.btn6.grid(row=6, column=0, pady=30)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Back", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=8, column=0)

    def _add_client_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Add client", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                        font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)


        self.entry_name = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text= "Name",
                                        font=("Arial", 40))
        self.entry_name.grid(row=2, column=0, pady = 30)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Add client", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._add_client)
        self.btn1.grid(row=3, column=0, pady = 30)

    def _add_client(self):
        id = self.entry_id.get()
        name = self.entry_name.get()

        if not id or not name or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        try:
            client = Client(id, name)

            self._services.add_client(client)

            self._command_finished_menu("Client added successfully")
        except Exception:
            self._command_finished_menu("Duplicate ID")

    def _delete_client_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Delete client", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                        font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)


        self.entry_name = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text= "Name",
                                        font=("Arial", 40))
        self.entry_name.grid(row=2, column=0, pady = 30)


        self.btn1 = ctk.CTkButton(self.content_frame, text="Add client", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._delete_client)
        self.btn1.grid(row=3, column=0, pady = 30)

    def _delete_client(self):
        id = self.entry_id.get()
        name = self.entry_name.get()

        if not id or not name or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        try:
            client = Client(id, name)

            self._services.remove_client(client)

            self._command_finished_menu("Client disappeared")
        except Exception:
            self._command_finished_menu("Error")

    def _edit_client_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Edit client", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                        font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)


        self.entry_name = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text= "Name",
                                        font=("Arial", 40))
        self.entry_name.grid(row=2, column=0, pady = 30)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Edit client", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._edit_client)
        self.btn1.grid(row=3, column=0, pady = 30)

    def _edit_client(self):
        id = self.entry_id.get()
        name = self.entry_name.get()

        if not id or not name or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        try:
            client = Client(id, name)

            self._services.update_client(client)

            self._command_finished_menu("Client edited successfully")
        except Exception:
            self._command_finished_menu("Error")

    def _show_clients(self, l: list[Client]):
        self.clear_frame()

        value = [["No. crt.", "ID", "Name"]]
        i = 1
        for client in l:
            value.append([str(i), str(client.id), client.name])
            i += 1

        self.table = CTkTable(master= self.content_frame, values=value)
        self.table.grid(row=0, column=0, padx = 50, pady=40)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=1, column=0)

    def _list_all_clients(self):
        self._show_clients(self._services.get_clients())

    def _list_clients_id_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Search clients by ID", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="ID",
                                     font=("Arial", 40))
        self.entry_id.grid(row=1, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Search", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_clients_id)
        self.btn1.grid(row=2, column=0, pady=30)

    def _list_clients_id(self):
        id = self.entry_id.get()

        if not id or not id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        id = int(id)
        self._show_clients(self._services.search_client_id(id))

    def _list_clients_name_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Search clients by name", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_name = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Name",
                                     font=("Arial", 40))
        self.entry_name.grid(row=1, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Search", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_clients_name)
        self.btn1.grid(row=2, column=0, pady=30)

    def _list_clients_name(self):
        name = self.entry_name.get()

        if not name:
            self._command_finished_menu("Invalid input")
            return

        self._show_clients(self._services.search_client_name(name))

    def _rental_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Rental Menu", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Rent a book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._rent_book_menu)
        self.btn1.grid(row=1, column=0)

        self.btn2 = ctk.CTkButton(self.content_frame, text="Return a book", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._return_book_menu)
        self.btn2.grid(row=2, column=0, pady=30)

        self.btn3 = ctk.CTkButton(self.content_frame, text="List all rentals", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_all_rentals)
        self.btn3.grid(row=3, column=0)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Back", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=8, column=0, pady=30)

    def _rent_book_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Rent", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=400, pady=70)

        self.entry_book_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Book ID",
                                     font=("Arial", 40))
        self.entry_book_id.grid(row=1, column=0)

        self.entry_client_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Client ID",
                                     font=("Arial", 40))
        self.entry_client_id.grid(row=2, column=0, pady=30)

        self.entry_rent_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Date(YYYY-MM-DD)",
                                          font=("Arial", 40))
        self.entry_rent_id.grid(row=3, column=0)

        self.entry_date = ctk.CTkEntry(self.content_frame, width=250, height=70,
                                            placeholder_text="Rent ID(0 if you do not want to provide one)", font=("Arial", 40))
        self.entry_date.grid(row=4, column=0, pady=30)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Rent", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._rent)
        self.btn1.grid(row=5, column=0)

    def _rent(self):
        book_id = self.entry_book_id.get()
        client_id = self.entry_client_id.get()
        rent_id = self.entry_rent_id.get()
        start_date = self.entry_date.get()

        if not book_id or not client_id or not rent_id or not start_date or not book_id.isdigit() or not client_id.isdigit() or not rent_id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        try:
            self._services.rent_book(book_id, client_id, date.fromisoformat(start_date), rent_id)
            self._command_finished_menu("Book Rented")
        except Exception as e:
            self._command_finished_menu("Error")

    def _return_book_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Return", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.entry_rental_id = ctk.CTkEntry(self.content_frame, width=250, height=70, placeholder_text="Rental ID",
                                          font=("Arial", 40))
        self.entry_rental_id.grid(row=1, column=0)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Return", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._return)
        self.btn1.grid(row=2, column=0, pady=30)

    def _return(self):
        rent_id = self.entry_rent_id.get()

        if not rent_id or not rent_id.isdigit():
            self._command_finished_menu("Invalid input")
            return

        try:
            self._services.return_book(rent_id)
            self._command_finished_menu("Book Returned")
        except Exception as e:
            self._command_finished_menu("Error")

    def _show_rentals(self, l: list[Rental]):
        self.clear_frame()

        value =[["No. crt.", "Rental ID", "Book ID", "Client ID", "Rental Date", "Return Date"]]
        i = 1
        for rental in l:
            value.append([str(i), str(rental.id), str(rental.book_id), str(rental.client_id), rental.rental_date.isoformat(),
                          rental.return_date.isoformat() if rental.return_date != date(1, 1, 1) else "Not returned yet"])
            i += 1

        self.table = CTkTable(self.content_frame, values = value)
        self.table.grid(row=0, column=0, padx = 50, pady=40)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=1, column=0)

    def _list_all_rentals(self):
        self._show_rentals(self._services.get_rentals())

    def _statistics_menu(self):
        self.clear_frame()

        self.label = ctk.CTkLabel(self.content_frame, text="Statistics Menu", font=("Arial", 70), text_color="#D2B48C")
        self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn1 = ctk.CTkButton(self.content_frame, text="Most rented books", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_most_rented_books)
        self.btn1.grid(row=1, column=0)

        self.btn2 = ctk.CTkButton(self.content_frame, text="Most active clients", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_most_active_clients)
        self.btn2.grid(row=2, column=0, pady=30)

        self.btn3 = ctk.CTkButton(self.content_frame, text="Most rented authors", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._list_most_rented_authors)
        self.btn3.grid(row=3, column=0)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Back", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=8, column=0, pady=30)

    def _list_most_rented_books(self):
        self._show_books(self._services.most_rented_books())

    def _list_most_active_clients(self):
        self._show_clients(self._services.most_active_clients())

    def _list_most_rented_authors(self):
        self.clear_frame()

        value = [["No. crt.", "Author"]]
        i = 1

        for author in self._services.most_rented_authors():
            value.append([str(i), author])
            i += 1

        self.table = CTkTable(self.content_frame, values = value)
        self.table.grid(row=0, column=0, padx=50, pady=40)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main Menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=1, column=0)

    def _undo(self):
        self.clear_frame()

        try:
            self._services.undo()
            self.label = ctk.CTkLabel(self.content_frame, text="Undone", font=("Arial", 70), text_color="#D2B48C")
            self.label.grid(row=0, column=0, padx=300, pady=70)
        except Exception as e:
            self.label = ctk.CTkLabel(self.content_frame, text="Nothing to undo", font=("Arial", 70),
                                      text_color="#D2B48C")
            self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main menu", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=8, column=0, pady=30)

    def _redo(self):
        self.clear_frame()

        try:
            self._services.redo()
            self.label = ctk.CTkLabel(self.content_frame, text="Redone", font=("Arial", 70), text_color="#D2B48C")
            self.label.grid(row=0, column=0, padx=300, pady=70)
        except Exception as e:
            self.label = ctk.CTkLabel(self.content_frame, text="Nothing to redo", font=("Arial", 70),
                                      text_color="#D2B48C")
            self.label.grid(row=0, column=0, padx=300, pady=70)

        self.btn0 = ctk.CTkButton(self.content_frame, text="Main meni", font=("Arial", 50), fg_color="#5D4037",
                                  hover_color="#3E2723", text_color="#D2B48C", command=self._main_menu)
        self.btn0.grid(row=8, column=0, pady=30)

    def close(self):
        self.destroy()

    def start(self):
        try:
            self.mainloop()
        except Exception as e:
            print(e)
