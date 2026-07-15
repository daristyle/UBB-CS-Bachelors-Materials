import random

from src.domain.Board import Board

class DumbComputer:
    def __init__(self, human_status, computer_status):
        self._human_status = human_status
        self._computer_status = computer_status

    def _almost_vertical_mill_centered(self, pos, brd):
        """
        Returns true iff there is almost a vertical mill centered at position pos on the board brd
        """
        node = brd[pos]
        count = 0
        if node.status == self._human_status:
            count += 1
        if brd[node.up].status == self._human_status:
            count += 1
        if brd[node.down].status == self._human_status:
            count += 1

        return count == 2

    def _almost_horizontal_mill_centered(self, pos, brd):
        """
        Returns true iff there is almost a horizontal mill centered at position pos on the board brd
        """
        node = brd[pos]
        count = 0
        if node.status == self._human_status:
            count += 1
        if brd[node.left].status == self._human_status:
            count += 1
        if brd[node.right].status == self._human_status:
            count += 1

        return count == 2

    def _almost_vertical_mill(self, pos, brd):
        """
        Returns true iff there is almost a vertical mill on the board brd that contains position pos
        """
        node = brd[pos]
        return (self._almost_vertical_mill_centered(pos, brd) or self._almost_vertical_mill_centered(node.up, brd) or
                self._almost_vertical_mill_centered(node.down, brd))

    def _almost_horizontal_mill(self, pos, brd):
        """
        Return true iff there is almost a horizontal mill on the board brd that contains position pos
        """
        node = brd[pos]
        return (self._almost_horizontal_mill_centered(pos, brd) or self._almost_horizontal_mill_centered(node.left, brd)
                or self._almost_horizontal_mill_centered(node.right, brd))

    def _almost_mill(self, pos, brd):
        """
        Return true iff there is almost a mill on the board brd that contains position pos
        """
        return self._almost_vertical_mill(pos, brd) or self._almost_horizontal_mill(pos, brd)

    def get_place(self, board: Board, computer_remaining, human_remaining):
        """
        Returns the position where the computer wants to place a solider on the Board board, knowing that he has computer_remaining
        soldiers remaining and the other player has human_remaining soliders remaining
        """
        locations = []
        for [pos, node] in board.board.items():
            if node.status == Board.Status.FREE:
                if self._almost_mill(pos, board.board):
                    return pos
                locations.append(pos)

        idx = random.randint(0, len(locations) - 1)
        return locations[idx]

    def get_move(self, board: Board):
        """
        Returns a tuple (from, to) with the move he wants to make if he only cant fly
        """
        locations = []
        for [pos, node] in board.board.items():
            if node.status == self._computer_status:
                for neighbour in [node.left, node.right, node.up, node.down]:
                    if board.board[neighbour].status == Board.Status.FREE:
                        if self._almost_mill(neighbour, board.board):
                            return pos, neighbour
                        locations.append((pos, neighbour))

        idx = random.randint(0, len(locations) - 1)
        return locations[idx]

    def get_any_move(self, board: Board):
        """
        Returns a tuple (from, to) with the move he wants to make if he can fly
        """
        locations = []
        pos_to = ""
        for [pos, node] in board.board.items():
            if node.status == Board.Status.FREE:
                if self._almost_mill(pos, board.board):
                    pos_to = pos
                    break
                locations.append(pos)

        idx = random.randint(0, len(locations) - 1)
        if pos_to == "":
            pos_to = locations[idx]

        for [pos, node] in board.board.items():
            if node.status == self._computer_status:
                locations.append(pos)

        idx = random.randint(0, len(locations) - 1)
        pos_from = locations[idx]

        return pos_from, pos_to

    def get_remove(self, board: Board):
        """
        Returns the position he wants to remove a soldier from
        """
        locations = []

        for [pos, node] in board.board.items():
            if node.status == self._human_status:
                if not board.check_mill(pos):
                    locations.append(pos)

        if len(locations) == 0:
            for [pos, node] in board.board:
                if node.status == self._human_status:
                    locations.append(pos)

        idx = random.randint(0, len(locations) - 1)
        return locations[idx]
