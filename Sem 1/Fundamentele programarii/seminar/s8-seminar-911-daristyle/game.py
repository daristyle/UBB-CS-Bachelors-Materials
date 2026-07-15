from board import Board
import random


class Game:
    def __init__(self):
        self._board = Board()

    def get_board(self):
        """
        Return the board. Will be called from the UI in order to display the board
        on the screen
        :return:
        """
        return self._board

    def move_human(self, row: int, col: int):
        """
        Record the human player's move on the board
        :param board:
        :param row:
        :param col:
        """
        self._board.move('X', row, col)
        pass

    def move_computer(self):
        """
        Calculate the computer's move and make it. The computer makes random, but valid moves on
        the board.
        :param board: the board

        There should be no exceptions here, because the computer should validate the validity
        of its moves.
        """
        l = []
        for row in range(3):
            for col in range(3):
                if self._board.get_value(row, col) == 0:
                    l.append([row, col])

        pos = random.randint(0, len(l) - 1)

        self._board.move('O', l[pos][0], l[pos][1])
