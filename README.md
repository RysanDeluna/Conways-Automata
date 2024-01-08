# Conways-Automata

A simple representation of John Horton Conway's Cellular Automata, simply called LIFE.

---

## Installation

In order to run the program, there is a CMakeList file to build and generate the executable. To use it, make sure you have the [cmake](https://cmake.org/download/) program installed and create a folder in which the build will be generated.

On Linux:
```sh
mkdir cmake-build && cd cmake-build
cmake ../
```

This will compile the source code and generate a single executable inside the build folder called LIFE.

---

## Commands

| Command | Description |
|---------|-------------|
| X       | Next generation |
| Z       | Previous State |
| N       | New Board |
| LMB     | Create or Destroy Life |

--- 
