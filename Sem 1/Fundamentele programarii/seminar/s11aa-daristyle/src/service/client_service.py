from domain.client import Client
from service.undo_service import FunctionCall, Operation


class ClientService:
    def __init__(self, undo_service, rental_service, validator, repository):
        self._validator = validator
        self._repository = repository
        self._rental_service = rental_service
        self._undo_service = undo_service

    def create(self, client_id, client_cnp, client_name):
        client = Client(client_id, client_cnp, client_name)
        self._validator.validate(client)
        self._repository.store(client)
        return client

    def delete(self, client_id):
        """
            1. Delete the client
        """

        # First delete the client from the repo to make sure there was no exception raised
        client = self._repository.delete(client_id)

        # 1. We only for undo/redo when we know the operation finished without
        # errors
        undo_function = FunctionCall(self._repository.store, client)
        redo_function = FunctionCall(self._repository.delete, client_id)
        o = Operation(undo_function, redo_function)

        self._undo_service.add_operation(o)

        '''
            2. Delete their rentals
            NB! This implementation is not transactional, i.e. the two delete operations are performed separately
        '''
        rentals = self._rental_service.filter_rentals(client, None)
        for rent in rentals:
            self._rental_service.delete_rental(rent.getId(), False)

        return client

    def get_client_count(self):
        return len(self._repository)

    def update(self, car):
        """
            NB! Undo/redo is also needed here
        """
        pass
