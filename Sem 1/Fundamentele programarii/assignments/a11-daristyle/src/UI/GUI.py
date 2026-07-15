from tabnanny import check

import pygame
from src.domain.Board import Board, BoardException, Mill
from src.services.Game import Game, GameException


class GUI:
    def __init__(self):
        self._game_manager = None
        pygame.init()
        self.width = 1000
        self.height = 1000
        self.screen = pygame.display.set_mode((self.width, self.height))

        pygame.display.set_caption("Nine Men's Morris")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont("Arial", 40, bold=True)
        self.error_font = pygame.font.SysFont("Arial", 20, bold=True)

        self.small_radius = 15
        self.big_radius = 30
        self.click_radius = 31
        self.outline = 2
        self.line_width = 4
        self.colors = {
            "bg": (230, 210, 180),  # Wood-like background
            "lines": (50, 30, 10),  # Dark Brown lines
            "white_p": (240, 240, 240),  # White Piece
            "black_p": (40, 40, 40),  # Black Piece
            "highlight": (0, 255, 0),  # Green selection ring
            "text": (0, 0, 0),
            "btn_idle": (100, 100, 100),
            "btn_hover": (140, 140, 140),
            "btn_text": (255, 255, 255),
            "error": (180, 0, 0)
        }


        cx, cy = self.width // 2, self.height // 2
        btn_w, btn_h = 440, 120

        self.btn_easy = pygame.Rect(0, 0, btn_w, btn_h)
        self.btn_easy.center = (cx, cy - 160)

        self.btn_hard = pygame.Rect(0, 0, btn_w, btn_h)
        self.btn_hard.center = (cx, cy)

        self.btn_exit = pygame.Rect(0, 0, btn_w, btn_h)
        self.btn_exit.center = (cx, cy + 160)

        self.btn_play_again = pygame.Rect(0, 0, btn_w, btn_h)
        self.btn_play_again.center = (cx, cy + 400)

        self.button_border_radius = 12


        self.border = 350
        self.offsetx = 0
        self.offsety = -50

        self.coords = {}
        self.__generate_coords()

    def __generate_coords(self):
        """
        Generates the coordinates of each point on the board
        """
        cx, cy = self.width // 2, self.height // 2
        step = (min(self.width, self.height) - self.border) // 6

        rings = {
            3: ["7a", "7d", "7g", "4g", "1g", "1d", "1a", "4a"],
            2: ["6b", "6d", "6f", "4f", "2f", "2d", "2b", "4b"],
            1: ["5c", "5d", "5e", "4e", "3e", "3d", "3c", "4c"]
        }
        directions = [(-1, -1), (0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0)]

        for ring, nodes in rings.items():
            for i in range(len(nodes)):
                node = nodes[i]
                dir = directions[i]
                self.coords[node] = (cx + dir[0] * step * ring + self.offsetx, cy + dir[1] * step * ring + self.offsety)

    def _draw_lines(self):
        """
        Draws all the lines of the board
        """
        squares = [
            ["7a", "7g", "1g", "1a"],
            ["6b", "6f", "2f", "2b"],
            ["5c", "5e", "3e", "3c"],
        ]

        for sq in squares:
            pts = [self.coords[i] for i in sq]
            pygame.draw.lines(self.screen, self.colors["lines"], True, pts, self.line_width)

        crosses = [
            ["7d", "5d"],
            ["4g", "4e"],
            ["1d", "3d"],
            ["4a", "4c"]
        ]
        for a, b in crosses:
            pygame.draw.line(self.screen, self.colors["lines"], self.coords[a], self.coords[b], self.line_width)

    def draw_game(self, board, selected_node = None, message = "", error_message = ""):
        """
        Draws the game screen, showing the message and error message and highlighting the selected node
        """
        self.screen.fill(self.colors["bg"])

        self._draw_lines()

        for pos, node in board.items():
            if pos == "null":
                continue
            x, y = self.coords[pos]

            if node.status == Board.Status.FREE:
                pygame.draw.circle(self.screen, self.colors["lines"], (x, y), self.small_radius)
            elif node.status == Board.Status.WHITE:
                pygame.draw.circle(self.screen, self.colors["white_p"], (x, y), self.big_radius)
                pygame.draw.circle(self.screen, (0, 0, 0), (x, y), self.big_radius, self.outline)
            elif node.status == Board.Status.BLACK:
                pygame.draw.circle(self.screen, self.colors["black_p"], (x, y), self.big_radius)
            else:
                raise Exception("null node")

            if pos == selected_node:
                pygame.draw.circle(self.screen, self.colors["highlight"], (x, y),
                                   self.big_radius if node.status != Board.Status.FREE else self.small_radius, self.outline)

        if message != "":
            text_surface = self.font.render(message, True, self.colors["text"])

            text_rect = text_surface.get_rect()
            text_rect.center = (self.width//2, (self.border // 2 + self.offsety)//2 - 30)

            self.screen.blit(text_surface, text_rect)

        if error_message != "":
            text_surface = self.error_font.render(error_message, True, self.colors["error"])

            text_rect = text_surface.get_rect()
            text_rect.center = (self.width//2, (self.border // 2 + self.offsety)//2 + 5)

            self.screen.blit(text_surface, text_rect)

        pygame.display.flip()

    def get_node_at_mouse(self):
        """
        Returns the node that is at the position of the mouse or "null"
        """
        mx, my = pygame.mouse.get_pos()
        for id, (px, py) in self.coords.items():
            dx = mx - px
            dy = my - py
            if dx ** 2 + dy ** 2 < self.click_radius ** 2:
                return id

        return "null"

    def _draw_button(self, rect, text, mouse_pos):
        """
        Draws a button at the position of rect with the text over the button, highlights the button if the position of
        the mouse is over it
        """
        color = self.colors["btn_hover"] if rect.collidepoint(mouse_pos) else self.colors["btn_idle"]

        pygame.draw.rect(self.screen, color, rect, border_radius=self.button_border_radius)
        pygame.draw.rect(self.screen, (0, 0, 0), rect, self.line_width, border_radius=self.button_border_radius)

        text_surf = self.font.render(text, True, self.colors["btn_text"])
        text_rect = text_surf.get_rect()
        text_rect.center = rect.center
        self.screen.blit(text_surf, text_rect)

    def draw_main_menu(self):
        """
        Draws the main menu screen
        """
        self.screen.fill(self.colors["bg"])

        title_surf = self.font.render("Nine men's morris", True, self.colors["lines"])
        title_rect = title_surf.get_rect(center=(self.width//2, 120))
        self.screen.blit(title_surf, title_rect)

        mp = pygame.mouse.get_pos()
        self._draw_button(self.btn_easy, "Easy Mode", mp)
        self._draw_button(self.btn_hard, "Hard Mode", mp)
        self._draw_button(self.btn_exit, "Exit", mp)

        pygame.display.flip()

    def check_menu_click(self):
        """
        Returns the text of the button that is at the position of the mouse or None
        """
        mouse_pos = pygame.mouse.get_pos()

        if self.btn_easy.collidepoint(mouse_pos):
            return "EASY"
        if self.btn_hard.collidepoint(mouse_pos):
            return "HARD"
        if self.btn_exit.collidepoint(mouse_pos):
            return "EXIT"

        return None

    def draw_end_screen(self, msg):
        """
        Draws the end screen with the message msg
        """
        self.draw_game(self._game_manager.board().board, message=msg)
        self._draw_button(self.btn_play_again, "Play Again", pygame.mouse.get_pos())
        pygame.display.flip()

    def wait_frame(self):
        """
        Waits for a frame
        """
        self.clock.tick(10)

    def end_screen(self, msg):
        """
        Manages the end screen
        """
        self.draw_end_screen(msg)

        exited = False
        restarted = False
        while not exited and not restarted:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    exited = True
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if self.btn_play_again.collidepoint(pygame.mouse.get_pos()):
                        restarted = True
            self.wait_frame()

        if exited:
            pygame.quit()
        else:
            self.start()

    def game(self, mode):
        """
        Manages the game logic
        """
        self._game_manager = Game(Board.Status.WHITE, mode)

        exited = finished = False
        turn = 0
        human_soldiers = computer_soldiers = 9
        error = ""
        pos_from = pos_to = "null"
        human_mill = computer_mill = False
        while not exited and not finished:
            if human_mill:
                turn = 0
            if computer_mill:
                turn = 1
            if turn == 0:
                if human_mill:
                    self.draw_game(self._game_manager.board().board, self.get_node_at_mouse(), "Remove a soldier", error)
                    pos = "null"
                    for event in pygame.event.get():
                        if event.type == pygame.QUIT:
                            exited = True
                        elif event.type == pygame.MOUSEBUTTONDOWN:
                            pos = self.get_node_at_mouse()

                    if pos == "null":
                        continue

                    try:
                        self._game_manager.human_remove(pos)
                        human_mill = False
                        error = ""
                    except (BoardException, GameException) as e:
                        error = str(e)
                elif human_soldiers > 0:
                    self.draw_game(self._game_manager.board().board, self.get_node_at_mouse(), "Place a soldier", error)
                    pos = "null"
                    for event in pygame.event.get():
                        if event.type == pygame.QUIT:
                            exited = True
                        elif event.type == pygame.MOUSEBUTTONDOWN:
                            pos = self.get_node_at_mouse()

                    if pos == "null":
                        continue
                    try:
                        self._game_manager.human_place(pos)
                        human_soldiers -= 1
                        error = ""
                    except Mill:
                        human_soldiers -= 1
                        human_mill = True
                    except (BoardException, GameException) as e:
                        error = str(e)
                        continue
                else:
                    if pos_from == "null":
                        self.draw_game(self._game_manager.board().board, self.get_node_at_mouse(), "Select a soldier to move", error)
                        for event in pygame.event.get():
                            if event.type == pygame.QUIT:
                                exited = True
                            elif event.type == pygame.MOUSEBUTTONDOWN:
                                pos_from = self.get_node_at_mouse()
                        continue
                    elif pos_to == "null":
                        self.draw_game(self._game_manager.board().board, self.get_node_at_mouse(),
                                   "Select a position to move the soldier to", error)
                        for event in pygame.event.get():
                            if event.type == pygame.QUIT:
                                exited = True
                            elif event.type == pygame.MOUSEBUTTONDOWN:
                                pos_to = self.get_node_at_mouse()
                        continue
                    else:
                        try:
                            self._game_manager.human_move(pos_from, pos_to)
                            pos_from = pos_to = "null"
                            error = ""
                        except Mill:
                            human_mill = True
                        except (BoardException, GameException) as e:
                            error = str(e)
                            pos_from = pos_to = "null"
                            continue
            else:
                if computer_mill:
                    self._game_manager.computer_remove()
                    computer_mill = False
                elif computer_soldiers > 0:
                    try:
                        self._game_manager.computer_place()
                    except Mill:
                        computer_mill = True
                    computer_soldiers -= 1
                else:
                    try:
                        self._game_manager.computer_move()
                    except Mill:
                        computer_mill = True

            if self._game_manager.is_won():
                finished = True

            turn = 1 - turn
            self.wait_frame()

        if exited:
            pygame.quit()
        else:
            self.end_screen("You won!" if turn == 1 else "You lost!")

    def start(self):
        """
        Manages the main menu
        """
        self.draw_main_menu()

        btn = None
        while btn is None:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    btn = "EXIT"
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    btn = self.check_menu_click()
            self.wait_frame()

        if btn == "EXIT":
            pygame.quit()
        else:
            self.game(btn)
