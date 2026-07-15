from domain.Reservation import Reservation
from repository.RoomRepo import RoomRepo
from repository.ReservationRepo import ReservationRepo
from texttable import Texttable

class Service:
    def __init__(self, room_file: str, reservation_file: str):
        self.__room_repo = RoomRepo(room_file)
        self.__reservation_repo = ReservationRepo(reservation_file)
        self.__offset_month = [3, 6, 6, 2, 4, 0, 2, 5, 1, 3, 6, 1]
        self.__days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    def get_available_rooms(self, day1, month1, day2, month2):
        if month2 < month1 or (month1 == month2 and day2 < day1):
            raise ValueError("Invalid interval")
        rooms = []
        for room in self.__room_repo.get_rooms():
            if self.__reservation_repo.is_room_free(room.number, month1, day1, month2, day2):
                rooms.append(room)

        return rooms[:]

    def reserve(self, room_number, name, guests, day1, month1, day2, month2):
        if name == "":
            raise ValueError("Invalid name")
        if not self.__reservation_repo.is_room_free(room_number, day1, month1, day2, month2):
            raise ValueError("Invalid room number")

        room = self.__room_repo.get_room(room_number)
        if room.capacity < guests:
            raise ValueError("Too many guests for this room")

        self.__reservation_repo.add(room_number, name, guests, day1, month1, day2, month2)

    def delete(self, id):
        self.__reservation_repo.delete(id)

    def get_reservations_between(self, day1, month1, day2, month2):
        reservations = self.__reservation_repo.get_reservations_between(day1, month1, day2, month2)

        reservations.sort(key=lambda reservation: reservation.arrival_month * 100 + reservation.arrival_day)

        tt = Texttable()
        tt.header(["Date", "Name", "Guests"])
        for reservation in reservations:
            date = str(reservation.arrival_day) + "." + str(reservation.arrival_month) + " - " + str(reservation.departure_day) + "." + str(reservation.departure_month)
            guests = str(reservation.guests) + " person"
            if reservation.guests > 1:
                guests += "s"
            tt.add_row([date, reservation.name, guests])

        return tt.draw()

    def get_reservations_by_month(self):
        l = self.__reservation_repo.get_reservations_by_month()
        months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
        i = 0
        ret = []

        for reserve in l:
            tt = Texttable()
            tt.header([months[i], "Name", "Guests"])
            i += 1

            reservations = reserve.copy()
            reservations.sort(key=lambda reservation: reservation.arrival_month * 100 + reservation.arrival_day)

            for reservation in reservations:
                date = str(reservation.arrival_day) + "." + str(reservation.arrival_month) + " - " + str(
                    reservation.departure_day) + "." + str(reservation.departure_month)
                guests = str(reservation.guests) + " person"
                if reservation.guests > 1:
                    guests += "s"
                tt.add_row([date, reservation.name, guests])

            ret.append(tt.draw())

        return ret[:]

    def get_monthly_report(self, month):
        rooms = self.__room_repo.get_rooms()
        tt = Texttable()
        tt.header(["M", "T", "W", "T", "F", "S", "S"])
        free_rooms = []
        for day in range(self.__days[month - 1]):
            cnt = 0
            for room in rooms:
                if self.__reservation_repo.is_room_free(room.number, month, day + 1, month, day + 1):
                    cnt += 1

            free_rooms.append(cnt)

        day = 0
        row = []
        for _ in range(self.__offset_month[month - 1]):
            row.append(" ")
        while day < self.__days[month - 1]:
            row.append(str(day + 1) + "/" + str(free_rooms[day]))
            day += 1
            if len(row) == 7:
                tt.add_row(row)
                row = []

        return tt.draw()