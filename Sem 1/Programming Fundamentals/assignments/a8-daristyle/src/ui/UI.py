from src.services.Services import Services
from src.repository.MemoryRepository import MemoryRepository
from src.domain.Book import Book

class UI:
    def __init__(self, repository = MemoryRepository()):
        self._services = Services(repository)

    def _print_menu(self):
        print("MENU")
        print("1.Add book")
        print("2.Display all books")
        print("3.Filter by excluding books starting with")
        print("4.Undo")
        print("0.Exit")

    def _add_book(self):
        title = input("Title: ")
        author = input("Author: ")
        isbn = input("ISBN: ")

        self._services.add(Book(isbn, title, author))
        print("Book added")

    def _display_all_books(self):
        i = 1
        for book in self._services.get_all():
            print(str(i) + ". " + str(book))
            i += 1

    def _filter(self):
        word = input("Exclude the books starting with the word: ")
        word = word.strip()
        if " " in word:
            raise ValueError("Enter only one word")

        self._services.filter_starting_with(word)
        print("List filtered")

    def _undo(self):
        self._services.undo()
        print("Undone")

    def start(self):
        exited = False
        command = {"1": self._add_book, "2": self._display_all_books, "3": self._filter, "4": self._undo}
        while not exited:
            self._print_menu()
            choice = input("Enter your choice: ").strip()
            if choice in command:
                try:
                    command[choice]()
                except Exception as e:
                    print(e)
            elif choice == "0":
                exited = True
            else:
                print("Invalid choice")

