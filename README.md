# Maze Generator

## Overview

This C++ program generates a maze using a randomized depth-first search (DFS) algorithm. The maze is represented as a grid of cells, each with walls that can be selectively opened to create paths.

## Components

### Cell Class (`Cell`)

Each cell in the maze grid is represented by the `Cell` class, which encapsulates:
- **Visited and Explored States**: Tracks whether a cell has been visited or explored.
- **Walls**: Maintains the state of walls in each direction (North, South, West, East) within the maze.

### Maze Grid (`maze[][]`)

The maze itself is stored as a 2D array of `Cell` objects (`maze[rows][cols]`), where:
- Each cell is initialized with closed walls.
- Walls are selectively opened during maze generation to create paths.

### Stack Class (`Stack`)

The `Stack` class implements a stack data structure to facilitate depth-first search (DFS) during maze generation:
- **Operations**: Supports push and pop operations for managing the stack of cells during traversal.

## Maze Generation Algorithm

### DFS with Randomization

The maze generation algorithm follows these steps:
1. **Initialization**: Starts from an initial cell, marks it as visited, and pushes it onto the stack.
2. **Randomized Exploration**: Randomly shuffles the order in which adjacent cells are explored.
3. **Path Carving**: Opens walls between cells to carve paths.
4. **Completion**: Continues until all reachable cells have been explored.

## Usage

### Compilation

To compile the program, use a C++ compiler (e.g., g++):
```bash
g++ -o maze_generator maze_generator.cpp
```

### Execution

Run the compiled executable:
```bash
./maze_generator
```

## Example Output

After running the program, the output displays the configuration of walls (N, S, W, E) for each cell in the maze grid.

## Dependencies

The program uses standard C++ libraries:
- `<iostream>`
- `<algorithm>`
- `<random>`
- `<chrono>`

Ensure these libraries are available in your C++ environment.

## Notes

- Adjust maze dimensions (`rows` and `cols`) and cell size (`cellSize`) according to your requirements.
- This implementation focuses on maze generation and does not include features like entrance, exit, or pathfinding algorithms.
