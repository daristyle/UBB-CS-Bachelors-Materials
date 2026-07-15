from typing import List
from src.domain.IDObject import IDObject
from src.repository.MemoryRepository import MemoryRepository


class BaseService:
    """
    Base class for all basic services.
    """
    def __init__(self, repo: MemoryRepository):
        self._repo = repo

    def add(self, obj: IDObject):
        """
        Adds an object to the repository.
        :param obj: the object to be added.
        :return: None
        """
        self._repo.add(obj)

    def remove(self, obj: IDObject):
        """
        Removes an object from the repository.
        :param obj: object to be removed.
        :return: None
        """
        repo_obj = self._repo.get(obj.id)
        if repo_obj is not None and repo_obj == obj:
            self._repo.remove_id(obj.id)

    def update(self, obj: IDObject):
        """
        Updates an object from the repository.
        :param obj: the new object
        :return: None
        """
        if self._repo.get(obj.id) is not None:
            self._repo.remove_id(obj.id)
            self._repo.add(obj)

    def get_all(self) -> List[IDObject]:
        """
        Returns all objects from the repository.
        :return: a list of objects
        """
        l = []
        for obj in self._repo:
            l.append(obj)

        return l.copy()

    def search_id(self, id: int):
        """
        Returns a list of all objects whose ID start with `id`.
        """
        l = []
        for obj in self._repo:
            if str(obj.id).startswith(str(id)):
                l.append(obj)

        return l.copy()

    def __len__(self) -> int:
        return len(self._repo)