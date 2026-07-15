# Nine Men's Morris

A classic strategy board game for two players where the goal is to form "mills" to eliminate the opponent's pieces.

## Game Objective
To win the game, you must achieve one of the following:
1. Reduce the opponent to only **two pieces** (making them unable to form a mill).
2. Block the opponent so they have **no legal moves** remaining.

## How to Play

The game is played on a grid of 24 points. It proceeds in three distinct phases:

### Phase 1: Placing Pieces
- Each player starts with **9 pieces**.
- Players take turns placing one piece at a time on any empty point on the board.
- If placing a piece forms a **Mill** (three pieces in a horizontal or vertical line), the player removes one of the opponent's pieces from the board.
- *Note: You cannot remove an opponent's piece that is currently part of a mill unless there are no other pieces available to take.*

### Phase 2: Moving Pieces
- Once all 18 pieces have been placed, players take turns sliding one of their pieces to an adjacent open point along the lines.
- If a move creates a **Mill**, the player removes an opponent's piece.

### Phase 3: Flying (Endgame)
- When a player is reduced to exactly **three pieces**, they may "fly."
- A flying piece can move to **any** empty point on the board, not just adjacent ones.
- This rule gives the losing player a slight advantage to recover.