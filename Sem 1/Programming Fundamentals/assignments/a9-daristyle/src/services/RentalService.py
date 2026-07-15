from src.domain.Rental import Rental
from src.repository.MemoryRepository import MemoryRepository
from datetime import date

from src.services.BaseService import BaseService


class RentalServiceException(Exception):
    pass

class RentalService:
    def __init__(self, repo: MemoryRepository):
        self._repo = repo
        self._current_id = 1

    def rent_book(self, book_id: int, client_id: int, date_rent = date.today(), rent_id = -1) -> None:
        if rent_id == -1:
            while self._repo.get(self._current_id) is not None:
                self._current_id += 1

            rent_id = self._current_id

        self._repo.add(Rental(rent_id, book_id, client_id, date_rent))

    def return_book(self, rent_id: int, date_returned = date.today()) -> None:
        rental = self._repo.get(rent_id)
        if rental is None:
            raise RentalServiceException("Rental ID not found")

        self._repo.remove_id(rental.id)
        rental.return_date = date_returned
        self._repo.add(rental)

    def is_rented(self, book_id: int) -> bool:
        for rent in self._repo:
            if rent.book_id == book_id and rent.return_date == date(1, 1, 1):
                return True
        return False

    def get_all(self):
        l = []
        for obj in self._repo:
            l.append(obj)

        return l.copy()

    def __len__(self) -> int:
        return len(self._repo)