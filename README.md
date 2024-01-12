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

#### Note

*The project was developded in a Linux environment on GCC 13.2.1 and CMAKE version 3.28.1 on [ClionIDE](https://www.jetbrains.com/clion/).*
