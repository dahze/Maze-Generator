#include <iostream>
#include <algorithm>  // For std::shuffle
#include <random>     // For std::default_random_engine
#include <chrono>     // For std::chrono::system_clock
#include <tuple>      // For std::tie

using namespace std;

// *** Initialization ***

// Constants to define the maze dimensions and cell size
const int rows = 4;
const int cols = 4;
const float cellSize = 20.0f;

// Constants for indicating cell states
const int not_visited = 0; // Cell has not been visited
const int visited = -1;    // Cell has been visited
const int wall = 0;        // Wall present in a direction
const int open = 1;        // Path open in a direction
const int not_explored = 0;// Cell has not been explored
const int explored = -1;   // Cell has been explored

// Direction constants
const int North = 0;
const int South = 1;
const int West = 2;
const int East = 3;

// Class representing a single cell in the maze
class Cell {
private:
    int v, ex, n, s, w, e; // Variables to indicate cell state and walls

public:
    // Default constructor initializing the cell
    Cell() {
        v = not_visited;     // Cell is initially not visited
        ex = not_explored;   // Cell is initially not explored
        n = s = w = e = wall;// All walls are initially closed
    }

    // Functions to set and get visited state of the cell
    void setVisited() {
        v = visited;
    }

    int getVisited() const {
        return v;
    }

    // Functions to set and get explored state of the cell
    void setExplored() {
        ex = explored;
    }

    int getExplored() const {
        return ex;
    }

    // Functions to set and get state of walls in each direction

    // North wall
    void setNorth() {
        n = open;
    }

    int getNorth() const {
        return n;
    }

    // South wall
    void setSouth() {
        s = open;
    }

    int getSouth() const {
        return s;
    }

    // West wall
    void setWest() {
        w = open;
    }

    int getWest() const {
        return w;
    }

    // East wall
    void setEast() {
        e = open;
    }

    int getEast() const {
        return e;
    }
};

// Array of cells representing the maze
Cell maze[rows][cols];

// *** Generating Maze ***

// Stack class to support depth-first search algorithm
class Stack {
private:
    pair<int, int> cell[rows * cols]; // Array to store cell coordinates
    int top;                          // Top index of the stack

public:
    // Constructor to initialize an empty stack
    Stack() {
        top = -1;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return (top == -1);
    }

    // Push a cell onto the stack
    void push(pair<int, int> c) {
        if (top == ((rows * cols) - 1)) {
            cout << "Stack Overflow\n"; // Print error message if stack is full
            return;
        }
        cell[++top] = c; // Increment top and store cell in stack
    }

    // Pop a cell from the stack
    pair<int, int> pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n"; // Print error message if stack is empty
            return { 0, 0 };
        }
        return cell[top--]; // Return top cell and decrement top
    }
};

// Function to check if a cell index is out of bounds
bool outOfBounds(int checkRow, int checkColumn) {
    return (checkRow < 0 || checkColumn < 0 || checkRow >= rows || checkColumn >= cols);
}

// Randomized depth-first search algorithm to generate the maze
void generateMaze() {
    Stack stack; // Stack to keep track of visited cells
    int choices[] = { 0, 1, 2, 3 }; // Array to shuffle direction choices

    int chosenRow = 0;
    int chosenColumn = 0;

    // Starting point for maze generation
    int currentRow = 0;
    int currentColumn = 0;

    maze[currentRow][currentColumn].setVisited(); // Mark starting cell as visited
    stack.push({ currentRow, currentColumn });    // Push starting cell onto stack

    while (!stack.isEmpty()) {
        tie(currentRow, currentColumn) = stack.pop(); // Pop current cell from stack

        chosenRow = currentRow;
        chosenColumn = currentColumn;

        // Shuffle direction choices
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(begin(choices), end(choices), default_random_engine(seed));

        // Explore each direction in random order
        for (int i = 0; i < 4; i++) {
            switch (choices[i]) {
                // North
            case 0:
                if (!outOfBounds(currentRow - 1, currentColumn) && maze[currentRow - 1][currentColumn].getVisited() == not_visited) {
                    chosenRow -= 1;
                    maze[currentRow][currentColumn].setNorth(); // Open north wall of current cell
                    maze[chosenRow][chosenColumn].setSouth();   // Open south wall of chosen cell
                }
                break;

                // South
            case 1:
                if (!outOfBounds(currentRow + 1, currentColumn) && maze[currentRow + 1][currentColumn].getVisited() == not_visited) {
                    chosenRow += 1;
                    maze[currentRow][currentColumn].setSouth(); // Open south wall of current cell
                    maze[chosenRow][chosenColumn].setNorth();   // Open north wall of chosen cell
                }
                break;

                // West
            case 2:
                if (!outOfBounds(currentRow, currentColumn - 1) && maze[currentRow][currentColumn - 1].getVisited() == not_visited) {
                    chosenColumn -= 1;
                    maze[currentRow][currentColumn].setWest(); // Open west wall of current cell
                    maze[chosenRow][chosenColumn].setEast();   // Open east wall of chosen cell
                }
                break;

                // East
            case 3:
                if (!outOfBounds(currentRow, currentColumn + 1) && maze[currentRow][currentColumn + 1].getVisited() == not_visited) {
                    chosenColumn += 1;
                    maze[currentRow][currentColumn].setEast(); // Open east wall of current cell
                    maze[chosenRow][chosenColumn].setWest();   // Open west wall of chosen cell
                }
                break;
            }

            // If a new cell was chosen, mark it as visited and push both cells onto stack
            if (currentRow != chosenRow || currentColumn != chosenColumn) {
                stack.push({ currentRow, currentColumn }); // Push current cell back onto stack

                maze[chosenRow][chosenColumn].setVisited(); // Mark chosen cell as visited
                stack.push({ chosenRow, chosenColumn });    // Push chosen cell onto stack
                break;
            }
        }
    }
}

// *** Main Function ***

// Function to test maze generation by printing wall information
void testGeneration() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Element [" << i << "][" << j << "] => ";
            if (maze[i][j].getNorth() == wall) { cout << "N "; }
            if (maze[i][j].getSouth() == wall) { cout << "S "; }
            if (maze[i][j].getWest() == wall) { cout << "W "; }
            if (maze[i][j].getEast() == wall) { cout << "E "; }
            cout << endl;
        }
    }
}

// Main function to execute maze generation and testing
int main() {
    generateMaze(); // Generate the maze
    testGeneration(); // Test and display the maze
    return 0; // Exit program
}