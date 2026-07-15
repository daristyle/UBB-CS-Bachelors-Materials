"""
This is where we add the logic to make moves on the board
"""
import random

import board as b

def move_human(board: list, row: int, col: int):
    """
    Record the human player's move on the board
    :param board:
    :param row:
    :param col:
    """
    b.move_board(board, 'X', row, col)


def move_computer(board: list) -> tuple:
    """
    Calculate the computer's move and make it. The computer makes random, but valid moves on
    the board.
    :param board: the board

    There should be no exceptions here, because the computer should validate the validity
    of its moves.
    """

    pos = []
    for row in range(3):
        for col in range(3):
            if b.get_value_on_board(board, row, col) == 0:
                pos.append((row, col))

    i = random.randint(0, len(pos) - 1)

    b.move_board(board, 'O', pos[i][0], pos[i][1])

