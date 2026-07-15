from enum import Enum

class BoardException(Exception):
    pass

class Mill(Exception):
    pass

class Board:
    class Node:
        def __init__(self, status, left, right, up, down):
            self.status = status
            self.left = left
            self.right = right
            self.up = up
            self.down = down

    class Status(Enum):
        FREE = 0
        WHITE = 1
        BLACK = -1
        NULL = 10

    def __init__(self):
        """
        The board will be represented by a bidirectional graph, each node being identified by its coordinates on the 
        board, and all its information will be kept in a dictionary
        """
        self._board = {
            "null": self.Node(self.Status.NULL, "null", "null", "null", "null"),#sentinel
            "7a": self.Node(self.Status.FREE, "null", "7d", "null", "4a"),
            "7d": self.Node(self.Status.FREE, "7a", "7g", "null", "6d"),
            "7g": self.Node(self.Status.FREE, "7d", "null", "null", "4g"),
            "6b": self.Node(self.Status.FREE, "null", "6d", "null", "4b"),
            "6d": self.Node(self.Status.FREE, "6b", "6f", "7d", "5d"),
            "6f": self.Node(self.Status.FREE, "6d", "null", "null", "4f"),
            "5c": self.Node(self.Status.FREE, "null", "5d", "null", "4c"),
            "5d": self.Node(self.Status.FREE, "5c", "5e", "6d", "null"),
            "5e": self.Node(self.Status.FREE, "5d", "null", "null", "4e"),
            "4a": self.Node(self.Status.FREE, "null", "4b", "7a", "1a"),
            "4b": self.Node(self.Status.FREE, "4a", "4c", "6b", "2b"),
            "4c": self.Node(self.Status.FREE, "4b", "null", "5c", "3c"),
            "4e": self.Node(self.Status.FREE, "null", "4f", "5e", "3e"),
            "4f": self.Node(self.Status.FREE, "4e", "4g", "6f", "2f"),
            "4g": self.Node(self.Status.FREE, "4f", "null", "7g", "1g"),
            "3c": self.Node(self.Status.FREE, "null", "3d", "4c", "null"),
            "3d": self.Node(self.Status.FREE, "3c", "3e", "null", "2d"),
            "3e": self.Node(self.Status.FREE, "3d", "null", "4e", "null"),
            "2b": self.Node(self.Status.FREE, "null", "2d", "4b", "null"),
            "2d": self.Node(self.Status.FREE, "2b", "2f", "3d", "1d"),
            "2f": self.Node(self.Status.FREE, "2d", "null", "4f", "null"),
            "1a": self.Node(self.Status.FREE, "null", "1d", "4a", "null"),
            "1d": self.Node(self.Status.FREE, "1a", "1g", "2d", "null"),
            "1g": self.Node(self.Status.FREE, "1d", "null", "4g", "null")
        }
    
    def check_vertical_mill_centered(self, pos):
        """
        Return true iff there is a vertical mill centered at pos
        """
        node = self._board[pos]
        if node.status == self._board[node.up].status == self._board[node.down].status:
            if node.status == self.Status.WHITE or node.status == self.Status.BLACK:
                return True
        
        return False
    
    def check_horizontal_mill_centered(self, pos):
        """
        Return true iff there is an horizontal mill centered at pos
        """
        node = self._board[pos]
        if node.status == self._board[node.left].status == self._board[node.right].status:
            if node.status == self.Status.WHITE or node.status == self.Status.BLACK:
                return True
        
        return False
    
    def check_vertical_mill(self, pos):
        """
        Return true iff there is a vertical mill which contains pos
        """
        
        return self.check_vertical_mill_centered(pos) or self.check_vertical_mill_centered(self._board[pos].up) or self.check_vertical_mill_centered(self._board[pos].down)
    
    def check_horizontal_mill(self, pos):
        """
        Return true iff there is a horizontal mill which contains pos
        """
        return self.check_horizontal_mill_centered(pos) or self.check_horizontal_mill_centered(self._board[pos].left) or self.check_horizontal_mill_centered(self._board[pos].right)
    
    def check_mill(self, pos):
        """
        Return true iff there is a mill which contains pos
        """
        return self.check_vertical_mill(pos) or self.check_horizontal_mill(pos)
        

    def place(self, pos, status: Board.Status):
        """
        Places a soldier of type status on position pos
        Raises Mill if there is a mill
        Raises BoardException if the position is invalid
        """
        if pos not in self._board or pos == "null":
            raise BoardException("Invalid position")
        if self._board[pos].status != self.Status.FREE:
            raise BoardException("Position already occupied")

        self._board[pos].status = status

        if self.check_mill(pos):
            raise Mill

    def move(self, pos_from, pos_to):
        """
        Moves the soldier from pos_from to pos_to
        Raises Mill if there is a mill
        Raises BoardException if either position is invalid
        """
        if pos_from not in self._board or pos_from == "null":
            raise BoardException("Invalid first position")
        if pos_to not in self._board or pos_to == "null":
            raise BoardException("Invalid second position")
        if self._board[pos_from].status == self.Status.FREE:
            raise BoardException("Position free")
        if self._board[pos_to].status != self.Status.FREE:
            raise BoardException("Position already occupied")

        self._board[pos_to].status = self._board[pos_from].status
        self._board[pos_from].status = self.Status.FREE

        if self.check_mill(pos_to):
            raise Mill

    def remove(self, pos, status):
        """
        Removes a soldier from position pos
        Raises BoardException if the position is invalid or if it is free or if the soldier does not have the right status
        """
        if pos not in self._board or pos == "null":
            raise BoardException("Invalid position")
        if self._board[pos].status == self.Status.FREE:
            raise BoardException("Position free")
        if self._board[pos].status != status:
            raise BoardException("Remove an enemy soldier")

        self._board[pos].status = self.Status.FREE

    def moves_left(self, status):
        """
        Return true iff there is at least one move left for the player that plays with the color status
        """
        for pos, node in self._board.items():
            if node.status == status:
                for neighbor in [node.left, node.right, node.up, node.down]:
                    if self._board[neighbor].status == self.Status.FREE:
                        return True
        return False

    def moves_left_for_both(self):
        """
        Return true iff there is at least one move left for both players
        """
        return self.moves_left(self.Status.WHITE) and self.moves_left(self.Status.BLACK)


    @property
    def board(self):
        brd = self._board.copy()

        return brd