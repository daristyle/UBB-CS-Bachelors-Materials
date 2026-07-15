from datetime import date
from time import strftime
from domain.car import Car
from domain.id_entity import IDEntity
from repository.car_repo import CarRepository


class Rental(IDEntity):
    _date_format = "%d/%m/%y"
    def __init__(self, rental_id: int, car: Car, start: date, end: date):
        super().__init__(rental_id)
        self._car = car
        self._start = start
        self._end = end

    @property
    def car(self) -> Car:
        return self._car

    @property
    def start(self) -> date:
        return self._start

    @property
    def end(self) -> date:
        return self._end

    def __str__(self):
        return (str(self.id) + " - " + str(self.car.id) + " - " + strftime(Rental._date_format, self.start)
                + " - " + strftime(Rental._date_format, self.end))
