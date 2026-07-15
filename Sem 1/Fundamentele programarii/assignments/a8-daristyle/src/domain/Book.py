class Book:
    def __init__(self, isbn: str, title: str, author: str) -> None:
        self._isbn = isbn.strip().lower()
        self._title = title
        self._author = author

    @property
    def isbn(self):
        return self._isbn

    @property
    def title(self):
        return self._title

    @property
    def author(self):
        return self._author

    def __str__(self):
        return self.isbn + " - " + self.title + " - " + self.author

    def to_dict(self):
        return {"isbn": self.isbn, "title": self.title, "author": self.author}

    @staticmethod
    def from_dict(data):
        return Book(data["isbn"], data["title"], data["author"])
