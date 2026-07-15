from src.domain.IDObject import IDObject

class RepositoryException(Exception):
    pass

class RepositoryIterator:
    def __init__(self, elements):
        self._data = list(elements)
        self._index = -1

    def __next__(self) -> IDObject:
        if self._index >= len(self._data) - 1:
            raise StopIteration()

        self._index += 1
        return self._data[self._index]

class MemoryRepository:
    def __init__(self, type):
        self._data = {}
        self._type = type

    def add(self, obj: IDObject) -> None:
        """
        Add an object to the repository.
        :param obj: object to be added.
        :return: None
        """
        if obj.id in self._data:
            raise RepositoryException("Duplicate ID")

        self._data[obj.id] = obj

    def remove_id(self, obj_id: int) -> None:
        """
        Remove an object from the repository.
        :param obj_id: the ID of the object to be removed.
        :return: None
        """
        if obj_id in self._data:
            self._data.pop(obj_id)

    def get(self, obj_id) -> IDObject:
        """
        Get an object from the repository.
        :param obj_id: the ID of the object to be found.
        :return: the object with the given ID or None if not found.
        """
        if obj_id not in self._data:
            return None
        return self._data[obj_id]

    def __iter__(self) -> RepositoryIterator:
        return RepositoryIterator(self._data.values())

    def __len__(self) -> int:
        return len(self._data)