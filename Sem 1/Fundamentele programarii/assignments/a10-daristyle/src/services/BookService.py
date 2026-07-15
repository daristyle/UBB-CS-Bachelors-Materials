from src.services.BaseService import BaseService

class BookService(BaseService):
    def search_title(self, title: str):
        """
        Returns a list of all objects whose title start with `title`.
        """
        title = title.strip().lower()
        l = []
        for book in self._repo:
            if book.title.strip().lower().startswith(title):
                l.append(book)

        return l.copy()

    def search_author(self, author: str):
        """
        Returns a list of all objects whose author start with `author`.
        """
        author = author.strip().lower()
        l = []
        for book in self._repo:
            if book.author.strip().lower().startswith(author):
                l.append(book)

        return l.copy()