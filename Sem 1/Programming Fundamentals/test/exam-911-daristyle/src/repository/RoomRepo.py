from domain.Room import Room

class RoomRepo:
    def __init__(self, file: str):
        self.__file = file
        self.__data = {}

        self._load()

    def _load(self):
        with open(self.__file, "r") as file:
            for line in file:
                tokens = line.strip().split(" ")
                if len(tokens) != 3 or tokens[2] != "room" or (tokens[1] not in ["single", "double", "family"]) or not tokens[0].isdigit():
                    raise Exception("Invalid room file format")

                tokens[0] = int(tokens[0])
                self.__data[tokens[0]] = Room(tokens[0], tokens[1] + " " + tokens[2])

    def _save(self):
        with open(self.__file, "w") as file:
            for room in self.__data.values():
                file.write(str(room.number) + " " + room.type + "\n")

    @property
    def get_room(self, number: int):
        if number not in self.__data:
            raise Exception("Invalid room number")
        return self.__data[number]

    def get_rooms(self):
        return self.__data.values()