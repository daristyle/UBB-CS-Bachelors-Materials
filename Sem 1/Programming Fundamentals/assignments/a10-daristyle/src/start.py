from src.ui.UI import UI
from src.ui.GUI import GUI
from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextFileRepository import TextFileRepository
from src.repository.BinaryFileRepository import BinaryFileRepository
from src.domain.Book import Book
from src.domain.Client import Client
from src.domain.Rental import Rental

def get_repos():
    l = [MemoryRepository(Book), MemoryRepository(Client), MemoryRepository(Rental)]
    pos = {"BOOKS": 0, "CLIENTS": 1, "RENTAL": 2}
    dom = {"BOOKS": Book, "CLIENTS": Client, "RENTAL": Rental}
    with open("settings.properties", "rt", encoding="utf-8") as config:
        for line in config:
            line = line.strip()
            entity, type = line.split("=")
            entity = entity.strip().upper()
            type = type.strip().lower()
            if type[0] == '"':
                filename = type[1:-1]
                if filename.endswith(".bin"):
                    l[pos[entity]] = BinaryFileRepository(dom[entity],filename)
                elif filename.endswith(".txt"):
                    l[pos[entity]] = TextFileRepository(dom[entity],filename)
                else:
                    raise ValueError("Invalid repository type specified in settings.properties")
            elif type == "inmemory":
                l[pos[entity]] = MemoryRepository(dom[entity])
            else:
                raise ValueError("Invalid repository type specified in settings.properties")

    return l

repos = get_repos()
GUI(repos[0], repos[1], repos[2]).start()

