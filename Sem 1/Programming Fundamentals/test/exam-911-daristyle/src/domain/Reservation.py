
class Reservation:
    def __init__(self, id:int, room_number: int, name: str, guests: int, arrival_day: int, arrival_month, departure_day: int, departure_month: int) -> None:
        self.__id = id
        self.__room_number = room_number
        self.__name = name
        self.__guests = guests
        self.__arrival_month = arrival_month
        self.__arrival_day = arrival_day
        self.__departure_month = departure_month
        self.__departure_day = departure_day

    @property
    def id(self):
        return self.__id
    @property
    def room_number(self):
        return self.__room_number
    @property
    def name(self):
        return self.__name
    @property
    def guests(self):
        return self.__guests
    @property
    def arrival_month(self):
        return self.__arrival_month
    @property
    def arrival_day(self):
        return self.__arrival_day
    @property
    def departure_month(self):
        return self.__departure_month
    @property
    def departure_day(self):
        return self.__departure_day