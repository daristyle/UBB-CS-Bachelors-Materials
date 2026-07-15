import copy
from src.domain.Board import Board, Mill
from src.services.DumbComputer import DumbComputer

class SmartComputer(DumbComputer):
    def __init__(self, human_status, computer_status):
        super().__init__(human_status, computer_status)
        self.__remove_pos = "null"

        self._depth = 3

    def _opposite_status(self, status):
        """
        Returns Board.Status.BLACK if status is Board.Status.WHITE
        Returns Board.Status.WHITE if status is Board.Status.BLACK
        Returns Board.Status.FREE else
        """
        if status == Board.Status.WHITE:
            return Board.Status.BLACK
        elif status == Board.Status.BLACK:
            return Board.Status.WHITE
        return Board.Status.FREE

    def _boards_remove(self, board: Board, status):
        """
        Returns all the possible boards after removing a soldier of the opposite status
        """
        l = []
        for pos, node in board.board.items():
            if node.status == self._opposite_status(status) and not board.check_mill(pos):
                temp = copy.deepcopy(board)
                temp.remove(pos, self._opposite_status(status))
                l.append([temp, pos])

        if len(l) == 0:
            for pos, node in board.board.items():
                if node.status == self._opposite_status(status):
                    temp = copy.deepcopy(board)
                    temp.remove(pos, self._opposite_status(status))
                    l.append([temp, pos])

        return l

    def _boards_place(self, board: Board, status):
        """
        Returns all the possible boards after placing a soldier of type status
        """
        l = []
        for pos, node in board.board.items():
            if node.status == Board.Status.FREE:
                temp = copy.deepcopy(board)
                try:
                    temp.place(pos, status)
                    l.append([temp, pos])
                except Mill:
                    aux = self._boards_remove(temp, status)
                    for i in range(0, len(aux)):
                        aux[i].append(pos)
                    l.extend(aux)

        return l

    def _boards_move_adjacent(self, board: Board, status):
        """
        Returns all the possible boards after moving a soldier of type status, if the player cannot fly
        """
        l = []
        for pos, node in board.board.items():
            if node.status == status:
                for neighbor in [node.left, node.right, node.up, node.down]:
                    neighbor_node = board.board[neighbor]
                    if neighbor_node.status == Board.Status.FREE:
                        temp = copy.deepcopy(board)
                        try:
                            temp.move(pos, neighbor)
                            l.append([temp, (pos, neighbor)])
                        except Mill:
                            aux = self._boards_remove(temp, status)
                            for i in range(0, len(aux)):
                                aux[i].append((pos, neighbor))
                            l.extend(aux)

        return l

    def _boards_move_any(self, board: Board, status):
        """
        Returns all the possible boards after moving a soldier of type status, if the player can fly
        """
        l = []
        free = []
        for pos, node in board.board.items():
            if node.status == Board.Status.FREE:
                free.append(pos)

        for pos, node in board.board.items():
            if node.status == status:
                for to in free:
                    temp = copy.deepcopy(board)
                    try:
                        temp.move(pos, to)
                        l.append([temp, (pos, to)])
                    except Mill:
                        aux = self._boards_remove(temp, status)
                        for i in range(0, len(aux)):
                            aux[i].append((pos, to))
                        l.extend(aux)

        return l

    def _check_winner(self, board: Board, computer_remaining, human_remaining):
        """
        Returns the winner of the game or None if the game is not won yet
        """
        if computer_remaining > 0 or human_remaining > 0:
            return None

        black = white = 0
        for pos, node in board.board.items():
            if node.status == Board.Status.WHITE:
                white += 1
            elif node.status == Board.Status.BLACK:
                black += 1

        if black < 3 or not board.moves_left(Board.Status.BLACK):
            return Board.Status.WHITE
        if white < 3 or not board.moves_left(Board.Status.WHITE):
            return Board.Status.BLACK

        return None

    def _evaluate_board(self, board: Board, winner):
        """
        Returns the score of the board, given the winner
        """
        if winner == self._computer_status:
            return 10 ** 9
        if winner == self._human_status:
            return -10 ** 9

        score = 0
        for pos, node in board.board.items():
            if node.status == self._computer_status or node.status == self._human_status:
                sign = -1 if node.status == self._human_status else 1

                score += sign * 15

                if board.check_mill(pos):
                    score += sign * 70 + (sign + 1) * 10

                for neighbor in [node.left, node.right, node.up, node.down]:
                    if board.board[neighbor].status == Board.Status.FREE:
                        score += sign * 3

                if self._almost_mill(pos, board.board):
                    score += sign * 23

        return score

    def _minimax(self, board: Board, computer_remaining, human_remaining, alpha, beta, depth, maximizing):
        """
        Returns the maximum score that can be achieved in depth moves
        """
        winner = self._check_winner(board, computer_remaining, human_remaining)
        if depth == 0 or winner is not None:
            return self._evaluate_board(board, winner)

        if maximizing:
            boards = []
            if computer_remaining > 0:
                boards = self._boards_place(board, self._computer_status)
            else:
                soldiers = 0
                for pos, node in board.board.items():
                    if node.status == self._computer_status:
                        soldiers += 1
                if soldiers > 3:
                    boards = self._boards_move_adjacent(board, self._computer_status)
                else:
                    boards = self._boards_move_any(board, self._computer_status)

            max_value = -10 ** 9
            for l in boards:
                brd = l[0]
                value = self._minimax(brd, computer_remaining, human_remaining, alpha, beta, depth - 1, False)
                max_value = max(max_value, value)
                alpha = max(alpha, value)

                if alpha >= beta:
                    break

            return max_value
        else:
            boards = []
            if human_remaining > 0:
                boards = self._boards_place(board, self._human_status)
            else:
                soldiers = 0
                for pos, node in board.board.items():
                    if node.status == self._human_status:
                        soldiers += 1

                if soldiers > 3:
                    boards = self._boards_move_adjacent(board, self._human_status)
                else:
                    boards = self._boards_move_any(board, self._human_status)

            min_value = 10 ** 9
            for l in boards:
                brd = l[0]
                value = self._minimax(brd, computer_remaining, human_remaining, alpha, beta, depth - 1, True)
                min_value = min(min_value, value)
                beta = min(beta, value)

                if alpha >= beta:
                    break

            return min_value

    def get_place(self, board: Board, computer_remaining, human_remaining):
        """
        Returns the position where the computer wants to place a solider on the Board board, knowing that he has computer_remaining
        soldiers remaining and the other player has human_remaining soliders remaining
        """
        self._depth = 3

        best_score = -10 ** 9 - 1
        best_pos = "null"

        boards = self._boards_place(board, self._computer_status)
        for l in boards:
            brd = l[0]
            score = self._minimax(brd, computer_remaining - 1, human_remaining, -10**9 - 1, 10 ** 9 + 1, self._depth - 1, False)

            if score > best_score:
                best_score = score
                best_pos = l[-1]
                if len(l) > 2:
                    print(l)
                    self.__remove_pos = l[1]
                else:
                    self.__remove_pos = "null"

        return best_pos

    def get_move(self, board: Board):
        """
        Returns a tuple (from, to) with the move he wants to make if he only cant fly
        """
        self._depth = 4

        best_score = -10 ** 9 - 1
        best_mov = "null"

        boards = self._boards_move_adjacent(board, self._computer_status)
        for l in boards:
            brd = l[0]
            score = self._minimax(brd, 0, 0, -10**9 - 1, 10 ** 9 + 1, self._depth - 1, False)

            if score > best_score:
                best_score = score
                best_mov = l[-1]
                if len(l) > 2:
                    print(l)
                    self.__remove_pos = l[1]
                else:
                    self.__remove_pos = "null"

        return best_mov

    def get_any_move(self, board: Board):
        """
        Returns a tuple (from, to) with the move he wants to make if he can fly
        """
        self._depth = 4

        best_score = -10 ** 9 - 1
        best_mov = "null"

        boards = self._boards_move_any(board, self._computer_status)
        for l in boards:
            brd = l[0]
            score = self._minimax(brd, 0, 0, -10 ** 9 - 1, 10 ** 9 + 1, self._depth - 1, False)

            if score > best_score:
                best_score = score
                best_mov = l[-1]
                if len(l) > 2:
                    self.__remove_pos = l[1]
                else:
                    self.__remove_pos = "null"

        return best_mov

    def get_remove(self, board: Board):
        """
        Returns the position he wants to remove a soldier from
        """
        if self.__remove_pos == "null":
            raise Exception("Bad Remove")
        best_remove = self.__remove_pos
        print(best_remove)
        self.__remove_pos = "null"

        return best_remove