from datetime import date
from domain.Reservation import Reservation


class ReservationRepo:
    def __init__(self, file):
        self.__file = file
        self.__data = {}

        self._load()

    def _load(self):
        with open(self.__file, "r") as file:
            for line in file:
                tokens = line.strip().split(" ")
                if len(tokens) < 6 or not tokens[0].isdigit() or not tokens[1].isdigit() or not tokens[-3].isdigit() or tokens[2] == "":
                    raise Exception("Invalid reservation file format")
                id = int(tokens[0])
                room = int(tokens[1])
                name = " ".join(tokens[2:-3])
                guests = int(tokens[-3])
                arrival = tokens[-2].split(".")
                if len(arrival) != 2 or not arrival[0].isdigit() or not arrival[1].isdigit():
                    raise Exception("Invalid reservation file format")
                arrival_day = int(arrival[0])
                arrival_month = int(arrival[1])
                departure = tokens[-1].split(".")
                if len(departure) != 2 or not departure[0].isdigit() or not departure[1].isdigit():
                    raise Exception("Invalid reservation file format")
                departure_day = int(departure[0])
                departure_month = int(departure[1])

                self.__data[id] = Reservation(id, room, name, guests, arrival_day, arrival_month, departure_day, departure_month)

    def _save(self):
        with open(self.__file, "w") as file:
            for reservation in self.__data.values():
                file.write(str(reservation.id) + " " + str(reservation.room_number) + " " + reservation.name + " " +
                           str(reservation.guests) + " " + str(reservation.arrival_day) + "." + str(reservation.arrival_month) +
                           " " + str(reservation.departure_day) + "." + str(reservation.departure_month) + "\n")

    def _are_overlapping(self, day1b, month1b, day1e, month1e, day2b, month2b, day2e, month2e):
        begin1 = date(2026, month1b, day1b)
        end1 = date(2026, month1e, day1e)
        begin2 = date(2026, month2b, day2b)
        end2 = date(2026, month2e, day2e)

        return begin1 <= end2 and begin2 <= end1

    def _is_included(self, day1b, month1b, day1e, month1e, day2b, month2b, day2e, month2e):
        begin1 = date(2026, month1b, day1b)
        end1 = date(2026, month1e, day1e)
        begin2 = date(2026, month2b, day2b)
        end2 = date(2026, month2e, day2e)

        return begin1 <= begin2 and end2 <= end1


    def is_room_free(self, number, month1, day1, month2, day2) -> bool:
        for reservation in self.__data.values():
            if reservation.room_number == number:
                if self._are_overlapping(day1, month1, day2, month2, reservation.arrival_day, reservation.arrival_month, reservation.departure_day, reservation.departure_month):
                    return False
        return True

    def add(self, room_number, name, guests, arrival_day, arrival_month, departure_day, departure_month):
        id = 1
        while id in self.__data:
            id += 1

        self.__data[id] = Reservation(id, room_number, name, guests, arrival_day, arrival_month, departure_day, departure_month)

        self._save()

    def delete(self, id):
        if id not in self.__data.keys():
            raise Exception("Reservation not found")
        self.__data.pop(id)

        self._save()

    def get_reservations_between(self, day1, month1, day2, month2):
        l = []
        for reservation in self.__data.values():
            if self._is_included(day1, month1, day2, month2, reservation.arrival_day, reservation.arrival_month, reservation.departure_day, reservation.departure_month):
                l.append(reservation)

        return l[:]

    def get_reservations_by_month(self):
        l = [[], [], [], [], [], [], [], [], [], [], [], []]
        for reservation in self.__data.values():
            l[reservation.arrival_month - 1].append(reservation)

        return l[:]