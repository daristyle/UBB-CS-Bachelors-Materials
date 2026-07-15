from src.repository.Repository import Repository
from src.domain.Board import Board, Mill
from src.services.DumbComputer import DumbComputer
from src.services.SmartComputer import SmartComputer

class GameException(Exception):
    pass

class Game:
    def __init__(self, human_status, mode):
        self._repo = Repository()

        self._human_status = human_status
        self._computer_status = Board.Status.BLACK
        if human_status == Board.Status.BLACK:
            self._computer_status = Board.Status.WHITE

        if mode == "EASY":
            self._computer = DumbComputer(self._human_status, self._computer_status)
        else:
            self._computer = SmartComputer(self._human_status, self._computer_status)

        self._human_soldiers = 0
        self._computer_soldiers = 0
        self._human_remaining_soldiers = 9
        self._computer_remaining_soldiers = 9

    def human_place(self, pos):
        """
        Places a soldier of the color of the human player on the board at position pos
        raises GameException if all the soldiers have been placed
        raises Mill if there is a mill after the move
        """
        if self._human_remaining_soldiers == 0:
            raise GameException("Soldiers already placed")

        mill = False
        try:
            self._repo.place(pos, self._human_status)
        except Mill:
            mill = True

        self._human_soldiers += 1
        self._human_remaining_soldiers -= 1

        if mill:
            raise Mill

    def computer_place(self):
        """
        Places a soldier of the color of the computer player on the board
        raises Mill if there is a mill after the move
        """
        pos = self._computer.get_place(self._repo.board, self._computer_remaining_soldiers, self._human_remaining_soldiers)

        mill = False
        try:
            self._repo.place(pos, self._computer_status)
        except Mill:
            mill = True

        self._computer_soldiers += 1
        self._computer_remaining_soldiers -= 1

        if mill:
            raise Mill

    def human_move(self, pos_from, pos_to):
        """
        Makes a move of a soldier from pos_from to pos_to
        raises GameException if:
            - there are soldiers that have not been placed yet
            - the status of the soldier is not the color of the human player
            - the move is not legal
        raises Mill if there is a mill after the move
        """
        if self._human_remaining_soldiers != 0:
            raise GameException("Place all the soldiers first")

        node = self._repo.board.board[pos_from]
        if node.status != self._human_status:
            raise GameException("Move your own soldiers")
        if pos_to not in [node.up, node.down, node.left, node.right] and self._human_soldiers > 3:
            raise GameException("Soldiers must move one tile at a time in this phase of the game")

        self._repo.move(pos_from, pos_to)

    def computer_move(self):
        """
        Makes a computer move
        raises GameException if there are soldiers that have not been placed yet
        raises Mill if there is a mill after the move
        """
        if self._computer_remaining_soldiers:
            raise GameException("Place all the soldiers first ccc")

        if self._computer_soldiers >= 3:
            pos_from, pos_to = self._computer.get_move(self._repo.board)
        else:
            pos_from, pos_to = self._computer.get_any_move(self._repo.board)

        self._repo.move(pos_from, pos_to)

    def human_remove(self, pos):
        """
        Makes a human remove of a soldier
        raises GameException if the move is not legal
        """
        if self._repo.check_mill(pos):
            brd = self._repo.board.board
            valid_move = True
            for idx, node in brd.items():
                if node.status == self._computer_status:
                    if not self._repo.check_mill(idx):
                        valid_move = False

            if not valid_move:
                raise GameException("Remove the soldiers that are not part of a mill first")

        self._repo.remove(pos, self._computer_status)

        self._computer_soldiers -= 1

    def computer_remove(self):
        """
        Makes a computer remove of a soldier
        """
        pos = self._computer.get_remove(self._repo.board)

        self._repo.remove(pos, self._human_status)

        self._human_soldiers -= 1

    def is_won(self):
        """
        Returns True iff the game is won
        """
        return (self._human_remaining_soldiers == 0 and self._computer_remaining_soldiers == 0 and
                (self._human_soldiers <= 2 or self._computer_soldiers <= 2 or not self._repo.moves_left_for_both()))

    def board(self):
        return self._repo.board