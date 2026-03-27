# CMPE 202 Assignment 6 — Rock-Paper-Scissors Implementation Plan

**Due:** Friday, March 27, 2026 at 11:59 PM | **Team assignment, 200 points**

---

## Overview

Build a C++ Rock-Paper-Scissors game (human vs. computer, 20 rounds) demonstrating iterative development, good class design, and design patterns.

- Algorithm selection via **command-line argument** (`--random` / `--smart`)
- Game rounds use a **configurable variable** (default `20`) shared by both modes
- Smart algorithm sequence length **N is configurable** (default N=5)
- Use **both** Strategy and Template Method design patterns (full credit)

---

## Architecture

### Design Pattern 1 — Strategy (Algorithm selection)

The `ComputerPlayer` holds a `Strategy*`. The game engine calls `strategy->getChoice()` without knowing which concrete strategy is active — satisfying the "game engine must not depend on which algorithm is used" requirement.

```
<<abstract>>
Strategy
+ getChoice(history) : Choice
+ updateHistory(humanChoice, computerChoice) : void
+ load() : void
+ save() : void
        |
   +-----------+
   |           |
RandomStrategy  SmartStrategy
```

### Design Pattern 2 — Template Method (Game round skeleton)

`GameEngine` is abstract and defines the fixed skeleton of the game. `ConsoleGameEngine` overrides the display hooks without changing the core logic.

```
<<abstract>>
GameEngine
+ playGame()              // runs 20 rounds — final
# playRound()             // template method
# displayRoundResult()    // hook — override for custom display
# displayFinalScore()     // hook
```

---

## Class Responsibilities

| Class | Responsibility |
|---|---|
| `Choice` | Enum: ROCK, PAPER, SCISSORS + helper functions (beats, toString) |
| `RoundResult` | Struct: human choice, computer choice, winner |
| `Strategy` | Abstract base: interface for both algorithms |
| `RandomStrategy` | Picks randomly using `rand()` |
| `SmartStrategy` | N-gram frequency prediction; delegates storage to `FrequencyStore` |
| `FrequencyStore` | Owns the `map<string,int>` frequency table + file I/O (`frequencies.dat`) |
| `HumanPlayer` | Reads and validates R/P/S input from stdin |
| `ComputerPlayer` | Holds `Strategy*`; delegates `getChoice()` to it |
| `GameEngine` | Abstract; template method controls 20-round game flow |
| `ConsoleGameEngine` | Concrete subclass; implements display hooks |
| `main.cpp` | Parses CLI args; constructs and wires all objects; starts game |

---

## Smart Algorithm Details

- Tracks the last **N** choices (human + computer interleaved) as a string key
- `FrequencyStore` maps each length-N sequence to how many times it has occurred
- On `getChoice()`:
  1. Take the last N-1 choices from history
  2. Try appending R, P, S — look up each candidate sequence in the frequency map
  3. The candidate with the highest frequency predicts the human's next choice
  4. Return the choice that **beats** that prediction
  5. If no data found: fall back to random
- After each round: update frequency for the completed sequence
- After each game: write `frequencies.dat` to disk
- At game start: read `frequencies.dat` if it exists (computer improves over time)

---

## File Structure

```
Assignment06/
├── main.cpp
├── Choice.h
├── Strategy.h
├── RandomStrategy.h / RandomStrategy.cpp
├── SmartStrategy.h  / SmartStrategy.cpp
├── FrequencyStore.h / FrequencyStore.cpp
├── HumanPlayer.h    / HumanPlayer.cpp
├── ComputerPlayer.h / ComputerPlayer.cpp
├── GameEngine.h     / GameEngine.cpp
├── ConsoleGameEngine.h / ConsoleGameEngine.cpp
├── Makefile
├── frequencies.dat      (generated at runtime)
└── report/
    ├── report.pdf
    └── uml_diagram.png
```

---

## Iterative Development Plan

### Iteration 1 — Basic game skeleton
- Implement `Choice`, `HumanPlayer`, hardcoded random `ComputerPlayer`
- Flat `GameEngine` loop: 20 rounds, prompt, display result, track score
- **Goal:** Working playable game end-to-end (no abstraction yet)

### Iteration 2 — Strategy Pattern
- Extract `Strategy` abstract class; implement `RandomStrategy`
- Refactor `ComputerPlayer` to hold `Strategy*`
- `GameEngine` requires no changes — validates loose coupling
- **Goal:** Strategy pattern in place; random algorithm works cleanly

### Iteration 3 — Template Method Pattern
- Refactor `GameEngine` into abstract base + `ConsoleGameEngine` subclass
- Move all display/output logic into overridable hooks
- **Goal:** Template method pattern in place; engine is display-agnostic

### Iteration 4 — Smart Algorithm
- Implement `FrequencyStore` (map + `frequencies.dat` read/write)
- Implement `SmartStrategy` using frequency lookup + random fallback
- Test across multiple games; verify `frequencies.dat` grows and computer improves
- **Goal:** Both algorithms fully functional; persistence working

### Iteration 5 — CLI, polish, and report
- Parse `--random`, `--smart`, `--n=<value>` in `main.cpp`
- Handle edge cases: invalid input, missing data file, first-time run
- Write report and draw UML class diagram
- **Goal:** Submission-ready package

---

## Design Principles to Highlight in Report

| Principle | Where Applied |
|---|---|
| **Single Responsibility** | `FrequencyStore` only manages the map + file I/O; `HumanPlayer` only handles input |
| **Loose Coupling** | `GameEngine` depends only on `Strategy*`, never on `RandomStrategy` or `SmartStrategy` |
| **Hidden Implementation** | Internal frequency map is private inside `FrequencyStore` |
| **Coding to the Interface** | `ComputerPlayer` and `GameEngine` reference `Strategy*`, not concrete types |
| **Encapsulate What Varies** | Algorithm differences are isolated inside Strategy subclasses |
| **Open/Closed** | A new strategy (e.g., `NeuralStrategy`) can be added with zero changes to `GameEngine` |

---

## Build & Run

```bash
make

./rps --random            # play against random computer
./rps --smart             # play against smart computer (N=5)
./rps --smart --n=7       # play against smart computer with N=7
```

Play multiple `--smart` games and watch the computer improve as `frequencies.dat` accumulates data.

---

## Submission Checklist

- [x] All `.h` / `.cpp` files compile cleanly with `make`
- [x] `--random` mode: 20-round game works correctly
- [ ] Both `--random` and `--smart` use the same configurable rounds variable (default `20`)
- [x] Each round displays human win / computer win / tie result
- [x] Final score is displayed after configured rounds (default `20`)
- [x] Human input accepts only `R` / `P` / `S` and reprompts on invalid input
- [x] `GameEngine` has no `#include` of `RandomStrategy` or `SmartStrategy`
- [ ] Template Method is verifiable: fixed game flow in `playGame()` with output only via overridable hooks
- [ ] `--smart` mode: `frequencies.dat` written after each game, read at start
- [ ] Computer visibly improves over multiple `--smart` games
- [ ] CLI invalid-argument handling works (`--random`/`--smart` misuse, invalid `--n`)
- [ ] `--smart` default uses `N=5`, and `--smart --n=<value>` correctly overrides N
- [ ] Report explicitly states major iterations and whether significant backtracking occurred
- [ ] UML/report clearly explains class relationships (dependency/aggregation/inheritance) and naming choices
- [ ] Report covers: iterations, UML diagram, design principles, design patterns
- [ ] Zip file named after team
- [ ] Team zip includes all C++ source files and the short report
