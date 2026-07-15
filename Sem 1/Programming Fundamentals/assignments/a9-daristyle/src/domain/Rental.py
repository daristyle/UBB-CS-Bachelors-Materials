from datetime import date
from src.domain.IDObject import IDObject, IDObjectException

class RentalException(Exception):
    pass

class Rental(IDObject):
    def __init__(self, id: int, book_id: int, client_id: int, rental_date: date, return_date = date(1, 1, 1)):
        super().__init__(id)

        if not book_id.is_integer() or book_id < 0:
            raise IDObjectException("Book ID must be a positive integer")
        if not client_id.is_integer() or client_id < 0:
            raise IDObjectException("Client ID must be a positive integer")

        self._book_id = book_id
        self._client_id = client_id
        self._rental_date = rental_date
        self._return_date = return_date

    @property
    def book_id(self) -> int:
        return self._book_id

    @property
    def client_id(self) -> int:
        return self._client_id

    @property
    def rental_date(self) -> date:
        return self._rental_date

    @property
    def return_date(self) -> date:
        return self._return_date

    @return_date.setter
    def return_date(self, value: date):
        self._return_date = value

    def __str__(self):
        return (str(self.id) + " - " + str(self.book_id) + " - " + str(self.client_id) + " - " +
                self.rental_date.isoformat() + " - " + self.return_date.isoformat())

    @staticmethod
    def from_str(s: str) -> "Rental":
        tokens = s.split(" - ")
        if len(tokens) != 5 or not tokens[0].isdigit() or not tokens[1].isdigit() or not tokens[2].isdigit():
            raise RentalException("Invalid string format for a Rental")

        try:
            ren = date.fromisoformat(tokens[3])
            ret = date.fromisoformat(tokens[4])
            return Rental(int(tokens[0]), int(tokens[1]), int(tokens[2]), ren, ret)
        except ValueError:
            raise RentalException("Invalid string format for a Rental")