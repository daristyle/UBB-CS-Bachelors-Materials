from unittest import TestCase
from src.repository.MemoryRepository import MemoryRepository
from src.services.ClientService import ClientService
from src.domain.Client import Client

class TestClientService(TestCase):
    def test_book_service_1(self):
        service = ClientService(MemoryRepository(Client))
        client1 = Client(1, "bejan")
        client2 = Client(2, "bischin")
        client3 = Client(3, "raul")

        service.add(client1)
        service.add(client2)
        service.add(client3)

        check = 0
        for book in service.get_all():
            if book == client1:
                check |= 1
            elif book == client2:
                check |= 2
            elif book == client3:
                check |= 4
        self.assertEqual(7, check)

        service.remove(client1)

        check = 0
        for book in service.get_all():
            if book == client1:
                check |= 1
            elif book == client2:
                check |= 2
            elif book == client3:
                check |= 4
        self.assertEqual(6, check)

        client2u = Client(2, "bisky")
        service.update(client2u)

        check = 0
        for book in service.get_all():
            if book == client1:
                check |= 1
            elif book == client2u:
                check |= 2
            elif book == client3:
                check |= 4
        self.assertEqual(6, check)


