"""
Functions that have to do with the game board
"""
from operator import truediv

from texttable import Texttable


def create_board() -> list:
    """
    Create the (initially empty) game board. We represent the board as a 3x3 matrix (one Python list
    that has 3 sub-lists of length 3 each).

    How to represent things on the board:
         0 -> empty square
         -1 -> 'O'
         1 -> 'X'
    """

    board = []
    row = []
    for i in range(3):
        row.append(0)
    for i in range(3):
        board.append(row.copy())

    return board


def get_value_on_board(board: list, row: int, col: int) -> int:
    """
    Return the value on the board at (row, col) coordinates
    :param board:
    :param row:
    :param col:
    :return: 0 if its an empty square, -1 if it's an 'O' and 1 if it's an 'X'
    """
    if len(board) != 3 or len(board[0]) != 3:
        raise ValueError('Invalid board')
    if row < 0 or row >= len(board) or col < 0 or col >= len(board[row]):
        raise ValueError("Invalid row or column")

    return board[row][col]

def _symbol_to_number(symbol: str):
    if symbol == 'O':
        return -1
    elif symbol == 'X':
        return 1
    else:
        raise ValueError('Invalid symbol conversion')

def _number_to_symbol(num: int):
    if num == -1:
        return 'O'
    elif num == 1:
        return 'X'
    elif num == 0:
        return ' '
    else:
        raise ValueError('Invalid number conversion')

def move_board(board: list, symbol: str, row: int, col: int):
    """
    Record a move on the board
    :param board: the game board
    :param symbol: One of 'X' (human player), or 'O' (computer player)
    :param row: The row, one of 0, 1 or 2
    :param col: The column, one of 0, 1 or 2
    :return: None
    :raises ValueError if:
        - move would be outside of the board
        - symbol is not one of 'X' or 'O'
        - the (row, col) position already has a symbol on it
    """
    if row < 0 or row >= len(board) or col < 0 or col >= len(board[row]):
        raise ValueError("Invalid row or column")
    if symbol != 'X' and symbol != 'O':
        raise ValueError("Invalid symbol")
    if get_value_on_board(board, row, col) != 0:
        raise ValueError("Position is occupied")

    board[row][col] = _symbol_to_number(symbol)


def is_full_board(board: list) -> bool:
    """
    Check whether the game board is full
    :param board: the board
    :return: True if the board is full, False otherwise
    """
    if len(board) != 3 or len(board[0]) != 3:
        raise ValueError('Invalid board')

    full = True
    for row in range(3):
        for col in range(3):
            full &= board[row][col] != 0

    return full


def is_board_won(board: list) -> bool:
    """
    Check whether the game board is won by either player
    :param board: the board
    :return: True if the board is won, False otherwise
    """
    if len(board) != 3 or len(board[0]) != 3:
        raise ValueError('Invalid board')
    row = [0, 0, 0]
    col = [0, 0, 0]
    diag = [0, 0]
    for r in range(3):
        for c in range(3):
            row[r] += board[r][c]
            col[c] += board[r][c]
            if r == c:
                diag[0] += board[r][c]
            elif r + c == 2:
                diag[1] += board[r][c]

    won = False
    for r in range(3):
        won |= abs(row[r]) == 3
    for c in range(3):
        won |= abs(col[c]) == 3
    for d in range(2):
        won |= abs(diag[d]) == 3

    return won


def to_str(board: list) -> str:
    """
    Return the string representation of the board. Use the texttable component to pretty print it
    :param board: The game board
    """
    if len(board) != 3 or len(board[0]) != 3:
        raise ValueError('Invalid board')
    tt = Texttable()
    for r in range(3):
        l = []
        for c in range(3):
            l.append(_number_to_symbol(board[r][c]))
        tt.add_row(l)

    return tt.draw()


if __name__ == "__main__":
    board = create_board()
    move_board(board, 'X', 0, 0)
    move_board(board, 'O', 2, 2)
    print(to_str(board))
