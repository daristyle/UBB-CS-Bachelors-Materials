"""
The game's user interface
    - The only place where we have print and input statements!
"""

import board as b
import game as g

"""
How the UI should work:
    1. Show the (initially empty) game board
        -> we do this by calling to_str() from the board module
    2. Read the human player's move
        -> catch any ValueError and print out its message
        -> repeat reading the move until the move is valid :)
    3. Calculate and make the computer's move
    4. Show the board again
    5. Go back to step 2.
        -> After each move (human or computer) check for the win
        -> The player who moved last won
        -> If the board is full AND the game was not won, it's a draw.
    6. When the game ends, display the final state of the board and print a corresponding
    message
"""

def print_board(board: list) -> None:
    print(b.to_str(board))

def print_winner(winner: str) -> None:
    print(winner + " won!")

def start_game() -> None:
    ended = False
    board = b.create_board()
    while not ended:
        print_board(board)

        human_made_a_move = False
        while not human_made_a_move:
            try:
                move = input("Enter your move: ").split(' ')
                move = list(map(int, move))
                g.move_human(board, move[0], move[1])
                human_made_a_move = True
            except ValueError as ve:
                print(ve)

        if b.is_board_won(board):
            print_board(board)
            print_winner("Human")
            ended = True
            continue

        if b.is_full_board(board):
            print_board(board)
            print("Draw!")
            ended = True
            continue

        g.move_computer(board)

        if b.is_board_won(board):
            print_board(board)
            print_winner("Computer")
            ended = True
            continue
        if b.is_full_board(board):
            print_board(board)
            print("Draw!")
            ended = True

start_game()
