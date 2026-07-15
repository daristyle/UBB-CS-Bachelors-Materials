from src.services.BaseService import BaseService

class ClientService(BaseService):
    def search_name(self, name: str):
        """
        Returns a list of all objects whose name start with `name`.
        """
        name = name.strip().lower()
        l = []
        for client in self._repo:
            if client.name.strip().lower().startswith(name):
                l.append(client)

        return l.copy()