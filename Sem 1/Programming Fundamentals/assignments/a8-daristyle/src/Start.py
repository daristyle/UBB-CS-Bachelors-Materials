from src.ui.UI import UI
from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextRepository import TextRepository
from src.repository.BinaryRepository import BinaryRepository
from src.repository.JSONRepository import JSONRepository
from src.repository.SQLRepository import SQLRepository

def get_repository():
    with open("settings.properties", "rt") as config:
        line = config.readline()
        _, type = line.split("=")
        type = type.strip().upper()
        if type == "MEMORY":
            return MemoryRepository()
        elif type == "TEXT":
            return TextRepository()
        elif type == "BINARY":
            return BinaryRepository()
        elif type == "JSON":
            return JSONRepository()
        elif type == "SQL":
            return SQLRepository()
        else:
            raise ValueError("Invalid repository type specified in settings.properties: " + type)


UI(get_repository()).start()