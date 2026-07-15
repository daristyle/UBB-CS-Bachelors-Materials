from src.domain.IDObject import IDObject

class ClientException(Exception):
    pass

class Client(IDObject):
    def __init__(self, id: int, name: str):
        super().__init__(id)

        self._name = name.strip()

    @property
    def name(self) -> str:
        return self._name

    def __str__(self):
        return str(self.id) + " - " + self.name

    @staticmethod
    def from_str(s: str) -> "Client":
        tokens = s.split(" - ")

        if len(tokens) != 2 or not tokens[0].isdigit():
            raise ClientException("Invalid string format for a Client")

        return Client(int(tokens[0]), tokens[1])

    def __eq__(self, other: "Client") -> bool:
        return self.id == other.id and self.name.strip().lower() == other.name.strip().lower()