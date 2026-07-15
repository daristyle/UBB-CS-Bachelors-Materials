from pathlib import Path
from domain.car import Car
from repository.car_repo import CarRepository, TextFileCarRepository, CarColors
from domain.rental import Rental
from time import strptime, strftime
from datetime import date

class DuplicateRentalError(Exception):
    pass

class TextFileRentalRepository:
    def __init__(self, car_repo: CarRepository, file_name: str = "rentals.txt"):
        self._car_repo = car_repo
        self._data = {}
        self._file_name = file_name
        Path(self._file_name).touch(exist_ok=True)
        self.__load_file()

    def __load_file(self):
        """
        Load the cars into memory. Reads the input text file and adds
        the cars to self._data
        """
        try:
            with open(self._file_name, "rt") as fin:
                for line in fin:
                    line = line.strip()
                    if not line:
                        continue

                    rental = self.from_str(line)

                    self._data[rental.id] = rental
        except FileNotFoundError:
            pass

    def find(self, rental_id: int) -> Rental:
        if rental_id in self._data:
            return self._data[rental_id]
        return None

    def store(self, object: Rental):
        """
        Implement this method
        """
        if object.id in self._data:
            raise DuplicateRentalError("Rental with the given id already exists")
        self._data[object.id] = object
        self.__save_file()

    def __save_file(self):
        fout = open(self._file_name, "wt")

        for rental in self._data.values():
            output = (str(rental.id) + " - " + str(rental.car.id) + " - " + rental.start.strftime("%d/%m/%y")
             + " - " + rental.end.strftime("%d/%m/%y"))
            fout.write(output)

        fout.close()

    def get_all(self) -> list[Rental]:
        """
        Return a Python list of all the rentals stored
        """
        return list(self._data.values())

    def from_str(self, format: str):
        tokens = format.strip().split(" - ")
        return Rental(int(tokens[0]), self._car_repo.find(int(tokens[1])),
                      strptime(tokens[2], "%d/%m/%y"), strptime(tokens[3], "%d/%m/%y"))

if __name__ == "__main__":
    car_repo = TextFileCarRepository()
    repo = TextFileRentalRepository(car_repo)

    car = Car(120, "SB 28 BIS", "Skoda Octavia", CarColors.RED)
    rental = Rental(17, car, date(2025, 4, 3), date(2026, 2, 10))
    repo.store(rental)
    car = Car(100, "SJ 33 ABC", "Golf 6", CarColors.MAGENTA)
    rental = Rental(12, car, date(2025, 12, 4), date(2025, 12, 10))
    repo.store(rental)

    for rental in repo.get_all():
        print(rental)