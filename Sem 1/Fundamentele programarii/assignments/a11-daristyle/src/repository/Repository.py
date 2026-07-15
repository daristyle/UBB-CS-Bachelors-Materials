from src.domain.Board import Board

class Repository:
    def __init__(self):
        self._board = Board()

    @property
    def board(self):
        return self._board

    def place(self, pos, status: Board.Status):
        """
        Places a soldier of type status on position pos
        Raises Mill if there is a mill
        Raises BoardException if the position is invalid
        """
        self._board.place(pos, status)

    def move(self, pos_from, pos_to):
        """
        Moves the soldier from pos_from to pos_to
        Raises Mill if there is a mill
        Raises BoardException if either position is invalid
        """
        self._board.move(pos_from, pos_to)

    def remove(self, pos, status):
        """
        Removes a soldier from position pos
        Raises BoardException if the position is invalid or if it is free or id the soldier does not have the right status
        """
        self._board.remove(pos, status)

    def moves_left_for_both(self):
        """
        Return true iff there is at least one move left for both players
        """
        return self._board.moves_left_for_both()

    def check_mill(self, pos):
        """
        Return true iff there is at least one mill that contains pos
        """
        return self._board.check_mill(pos)