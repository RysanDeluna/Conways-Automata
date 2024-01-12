# Conways-Automata

A simple representation of John Horton Conway's Cellular Automata, simply called LIFE. The matrix was inspired by [Akalicki's matrix class](https://github.com/akalicki/matrix.git) with some modifications.

---

## Installation

In order to run the program, there is a CMakeList file to build and make the executable. Be sure to have [Cmake](https://cmake.org/download/) installed and to create the folder where the build will be generated.

On Linux:
```sh
mkdir cmake-build && cd cmake-build
cmake ../
```

This will compile the source code outputting a single executable inside the build folder called LIFE.

---

## Commands

| Command | Description |
|---------|-------------|
| X       | Next generation |
| Z       | Previous State |
| N       | New Board |
| LMB     | Create or Destroy Life |

--- 

## Background

Cellular Automatas were fascinating for the mathematician Conway (and for me) and he wanted to model the simplest configuration in which these automatas could explode into the infinite power of a universal computer. This would reduce the von Neumann's 29 states for a self-reproducing automata to a set of only 2 - i.e. alive or dead, zero or one, on or off.

This model, named LIFE, would have a cumbersome configuration of cells in a grid; but, if were a universal machine, it could eventually mimic the workings of the most powerful supercomputer. It's name came from it's rules, which are representations of *survival*, *birth* and *death* and would generate everything there are in the artificial world; from it's physics to it's meaning. 

Under these considerations, eventually was develped a set of rules that would represent a Universe capable of generating Life:

### LIFE Rules

- **Configuration:** Life occurs on a virtual checker-board. The squares are called cells. They are in one of two states: alive or dead. Each cell has eight possible neighbours, the cells which touches its sides or its corners.
- **Life and Death:** If a cell on the checker-board is alive, it will survive in the next time step (or generation) if there are either two or three neighbours also alive. It will die of overcrowding if there are more than three live neighbours, and it will die of exposure if there are fewer than two.
- **Born Rule**: If a cell on the checker-board is dead, it will remain dead in the next generation unless exactly three of its eight neighbours are alive. In that case, the cell will be born in the next generation.

### The Code

With these rules in mind, the approach for creating the code resolved around implementing these rules in a graphical interface which could be used to understand and experiment the behaviour of it's cells organized in a grid. Which, trivially was implemented as a matrix which would store the information for each cell; which could be alive or dead.

### Quests

For whoever wants to try it out, I have some quests for your :)

Try to find the following stable shapes:

1. Block, ship, longboat, beehive, loaf, canoe and pond;
2. Toads, blinkers, clocks and traffic lights;
3. Gliders, glider cannons and train.

The shapes on item one are stable and do not change if not perturbe, while the shapes on item 2 change each time-step but alternate between a regular set of shapes. On the other hand, shapes on the 3rd item were used to prove that LIFE is a universal computer, and they generate other shapes and can be used in computations within the Universe of LIFE.

#### Note

*The project was developded in a Linux environment on GCC 13.2.1 and CMAKE version 3.28.1 on [ClionIDE](https://www.jetbrains.com/clion/).*

The inspiration for working on this project came by reading:
*Steven Levy. 1993. Artificial life: A report from the frontier where computers meet biology. Random House Inc.*
