# NMK Solver for Tic-Tac-Toe

A C++ command-line solver for the generalised **NMK** variant of Tic-Tac-Toe, where the board is **N columns × M rows** and a player must place **K** pieces in a row (horizontally, vertically, or diagonally) to win.

---

## Tech stack

| Layer | Technology |
|---|---|
| Language | C++ (standard I/O, no external libraries) |
| Build system | Visual Studio solution (`.sln` / `.vcxproj`) |
| Target platform | Windows x64 (MSVC); any C++11-capable compiler works |

---

## Architecture

The entire program lives in a single source file, `TicTacToe_NMK_Solver.cpp`, with the following key components:

| Component | Description |
|---|---|
| `Gra` struct | Holds the board (`char**`), dimensions (x, y), win-length (k), and the active player |
| `StworzPlansze` / `UsunPlansze` | Allocate and free the 2-D board on the heap |
| `CzyWygral` | Checks rows, columns, and both diagonals for a K-in-a-row win |
| `GenerujKolejneRuchy` | Generates all next possible board states; optionally cuts off after the first winning move |
| `NaIleSposobowWygrana` | Counts in how many ways a player can win in one move (used as a heuristic pruning hint) |
| `Minimax` | Recursive Minimax search with two pruning optimisations: immediate win/loss short-circuit and "double-threat" heuristic |
| `main` | Read-eval-print loop — parses commands from `stdin` until `q` is entered |

---

## Commands

The program reads commands from `stdin`. Each command is followed by the board parameters and current state on the same line.

### Input format

```
<COMMAND> <N> <M> <K> <ACTIVE_PLAYER> <board cells row by row…>
```

- `N` – number of columns  
- `M` – number of rows  
- `K` – pieces in a row required to win  
- `ACTIVE_PLAYER` – `1` (first player) or `2` (second player)  
- Board cells: `1` = player 1, `2` = player 2, `0` = empty

### Available commands

| Command | Output |
|---|---|
| `GEN_ALL_POS_MOV` | Prints the count of empty cells, then every possible next board state |
| `GEN_ALL_POS_MOV_CUT_IF_GAME_OVER` | Prints `1` and the first winning board if one exists; otherwise falls back to `GEN_ALL_POS_MOV` |
| `SOLVE_GAME_STATE` | Runs Minimax and prints `FIRST_PLAYER_WINS`, `SECOND_PLAYER_WINS`, or `BOTH_PLAYERS_TIE` |
| `q` | Exits the program |

### Example

```
GEN_ALL_POS_MOV 4 4 3 1 1 2 0 1 0 1 0 2 0 2 0 1 0 0 2 0
```

This solves a 4 × 4 board where 3 in a row wins, player 1 is active, and the board is:

```
1 2 0 1
0 1 0 2
0 2 0 1
0 0 2 0
```

```
SOLVE_GAME_STATE 4 4 3 1 1 2 0 1 0 1 0 2 0 2 0 1 0 0 2 0
```

Returns who wins the above position with optimal play from both sides.

---

## How to build

**Visual Studio (Windows)**

1. Open `TicTacToe_NMK_Solver.sln`.
2. Select the **x64 Release** configuration.
3. Press **Ctrl+Shift+B** to build.
4. The executable is placed in `x64/Release/`.

**Command line (any platform with g++)**

```bash
g++ -O2 -o nmk_solver TicTacToe_NMK_Solver.cpp
```

---

## How to run

```bash
./nmk_solver
```

Then type commands interactively or pipe an input file:

```bash
echo "SOLVE_GAME_STATE 3 3 3 1 0 0 0 0 0 0 0 0 0" | ./nmk_solver
```

