class Room:
    def __init__(self, number: int, type: str):
        self.__number = number
        self.__type = type

    @property
    def number(self) -> int:
        return self.__number
    @property
    def type(self) -> str:
        return self.__type
    @property
    def capacity(self):
        if self.__type == "single room":
            return 1
        elif self.__type == "double room":
            return 2
        elif self.__type == "family room":
            return 4
        else:
            raise Exception("Unknown room type")
            return 0

    def __str__(self):
        return str(self.number) + " " + str(self.type)