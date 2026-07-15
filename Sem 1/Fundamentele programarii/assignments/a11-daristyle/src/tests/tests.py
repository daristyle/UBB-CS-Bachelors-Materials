import unittest
from src.domain.Board import Board, BoardException, Mill
from src.repository.Repository import Repository
from src.services.Game import Game, GameException
from src.services.DumbComputer import DumbComputer
from src.services.SmartComputer import SmartComputer


class TestBoard(unittest.TestCase):
    def setUp(self):
        self.board = Board()

    def test_initialization(self):
        self.assertEqual(self.board.board["7a"].status, Board.Status.FREE)
        self.assertEqual(self.board.board["7a"].right, "7d")

    def test_place_valid(self):
        self.board.place("7a", Board.Status.WHITE)
        self.assertEqual(self.board.board["7a"].status, Board.Status.WHITE)

    def test_place_invalid(self):
        self.board.place("7a", Board.Status.WHITE)
        with self.assertRaises(BoardException):
            self.board.place("7a", Board.Status.BLACK)
        with self.assertRaises(BoardException):
            self.board.place("9z", Board.Status.WHITE)

    def test_detect_mill_horizontal(self):
        self.board.place("7a", Board.Status.WHITE)
        self.board.place("7d", Board.Status.WHITE)
        with self.assertRaises(Mill):
            self.board.place("7g", Board.Status.WHITE)
        self.assertTrue(self.board.check_mill("7d"))

    def test_detect_mill_vertical(self):
        self.board.place("1a", Board.Status.BLACK)
        self.board.place("4a", Board.Status.BLACK)
        with self.assertRaises(Mill):
            self.board.place("7a", Board.Status.BLACK)
        self.assertTrue(self.board.check_mill("4a"))

    def test_move_valid(self):
        self.board.place("7a", Board.Status.WHITE)
        self.board.move("7a", "7d")
        self.assertEqual(self.board.board["7a"].status, Board.Status.FREE)
        self.assertEqual(self.board.board["7d"].status, Board.Status.WHITE)

    def test_move_invalid(self):
        self.board.place("7a", Board.Status.WHITE)
        self.board.place("7d", Board.Status.BLACK)
        with self.assertRaises(BoardException):
            self.board.move("1a", "1d")
        with self.assertRaises(BoardException):
            self.board.move("7a", "7d")

    def test_remove(self):
        self.board.place("7a", Board.Status.BLACK)
        self.board.remove("7a", Board.Status.BLACK)
        self.assertEqual(self.board.board["7a"].status, Board.Status.FREE)

    def test_remove_invalid(self):
        self.board.place("7a", Board.Status.WHITE)
        with self.assertRaises(BoardException):
            self.board.remove("7d", Board.Status.WHITE)
        with self.assertRaises(BoardException):
            self.board.remove("7a", Board.Status.BLACK)


class TestRepository(unittest.TestCase):
    def setUp(self):
        self.repo = Repository()

    def test_place_and_state(self):
        self.repo.place("7a", Board.Status.WHITE)
        self.assertEqual(self.repo.board.board["7a"].status, Board.Status.WHITE)

    def test_moves_left_for_both(self):
        self.assertFalse(self.repo.moves_left_for_both())
        self.repo.place("7a", Board.Status.WHITE)
        self.repo.place("7d", Board.Status.BLACK)
        self.assertTrue(self.repo.moves_left_for_both())


class TestGame(unittest.TestCase):
    def setUp(self):
        self.game = Game(Board.Status.WHITE, "EASY")

    def test_human_place_phase(self):
        self.game.human_place("7a")
        b = self.game.board().board
        self.assertEqual(b["7a"].status, Board.Status.WHITE)
        self.assertEqual(self.game._human_soldiers, 1)

    def test_human_place_mill(self):
        self.game._repo.place("7a", Board.Status.WHITE)
        self.game._repo.place("7d", Board.Status.WHITE)
        self.game._human_remaining_soldiers = 7
        self.game._human_soldiers = 2
        with self.assertRaises(Mill):
            self.game.human_place("7g")

    def test_human_move_phase_premature(self):
        self.game.human_place("7a")
        with self.assertRaises(GameException):
            self.game.human_move("7a", "7d")

    def test_human_move_phase_valid(self):
        self.game._human_remaining_soldiers = 0
        self.game._repo.place("7a", Board.Status.WHITE)
        self.game.human_move("7a", "7d")
        b = self.game.board().board
        self.assertEqual(b["7a"].status, Board.Status.FREE)
        self.assertEqual(b["7d"].status, Board.Status.WHITE)

    def test_flying_rule(self):
        self.game._human_remaining_soldiers = 0
        self.game._human_soldiers = 3
        self.game._repo.place("7a", Board.Status.WHITE)
        self.game.human_move("7a", "1a")
        self.assertEqual(self.game.board().board["1a"].status, Board.Status.WHITE)

    def test_human_remove_validation(self):
        self.game._computer_status = Board.Status.BLACK
        self.game._repo.place("7a", Board.Status.BLACK)
        self.game._repo.place("7d", Board.Status.BLACK)

        try:
            self.game._repo.place("7g", Board.Status.BLACK)
        except Mill:
            pass

        self.game._repo.place("1a", Board.Status.BLACK)

        with self.assertRaisesRegex(GameException, "Remove the soldiers that are not part of a mill"):
            self.game.human_remove("7a")

        self.game.human_remove("1a")
        self.assertEqual(self.game.board().board["1a"].status, Board.Status.FREE)
    def test_computer_place(self):
        initial_soldiers = self.game._computer_soldiers

        self.game.computer_place()

        self.assertEqual(self.game._computer_soldiers, initial_soldiers + 1)

        black_count = 0
        for _, node in self.game.board().board.items():
            if node.status == Board.Status.BLACK:
                black_count += 1
        self.assertEqual(black_count, initial_soldiers + 1)

    def test_is_won(self):
        self.game._human_remaining_soldiers = 0
        self.game._computer_remaining_soldiers = 0
        self.game._human_soldiers = 2
        self.game._computer_soldiers = 4
        self.assertTrue(self.game.is_won())


class TestDumbComputer(unittest.TestCase):
    def setUp(self):
        self.computer = DumbComputer(Board.Status.WHITE, Board.Status.BLACK)
        self.board = Board()

    def test_get_place_validity(self):
        pos = self.computer.get_place(self.board, 9, 9)
        self.assertIn(pos, self.board.board)
        self.assertEqual(self.board.board[pos].status, Board.Status.FREE)

    def test_detect_almost_mill(self):
        self.board.place("7a", Board.Status.WHITE)
        self.board.place("7d", Board.Status.WHITE)
        self.assertTrue(self.computer._almost_mill("7g", self.board.board))

    def test_get_move_validity(self):
        self.board.place("7a", Board.Status.BLACK)
        pos_from, pos_to = self.computer.get_move(self.board)

        self.assertEqual(pos_from, "7a")
        self.assertIn(pos_to, ["7d", "4a"])
        self.assertEqual(self.board.board[pos_to].status, Board.Status.FREE)


class TestSmartComputer(unittest.TestCase):
    def setUp(self):
        self.computer = SmartComputer(Board.Status.WHITE, Board.Status.BLACK)
        self.board = Board()

    def test_block_opponent_mill(self):
        self.board.place("7a", Board.Status.WHITE)
        self.board.place("7d", Board.Status.WHITE)

        move = self.computer.get_place(self.board, 8, 7)
        self.assertEqual(move, "7g")

    def test_minimax_move_logic(self):
        self.board.place("7a", Board.Status.BLACK)
        pos_from, pos_to = self.computer.get_move(self.board)

        self.assertEqual(pos_from, "7a")
        self.assertIn(pos_to, ["7d", "4a"])


if __name__ == '__main__':
    unittest.main()