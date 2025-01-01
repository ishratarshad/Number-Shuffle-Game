#include "Board.hpp"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <iomanip>
#include <ctime>   
using namespace std;


// 2 Task A: Define constructors and destructors in Board.cpp


 Board::Board() {
    numRows = 3;
    numCols = 3;

    panel = new int*[numRows];
    for (int i = 0; i < numRows; ++i) {
        panel[i] = new int[numCols];
    }
    randomize(); 
}

//2.2 A nondefault constructor Board(int m, int n)
Board::Board(int m, int n) {
    if (m >= 2 && n >= 2) {
        numRows = m;
        numCols = n;
    } else {
        numRows = 3;
        numCols = 3;
    }

    panel = new int*[numRows];
    for (int i = 0; i < numRows; ++i) {
        panel[i] = new int[numCols];
    }

    randomize();
}

// 2.3 A nondefault constructor Board(int** arr, int m, int n)

Board::Board(int** arr, int m, int n) : Board(m, n) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            panel[row][col] = arr[row][col];
        }
    }

    getInfo();
}

// 2.4 The destructor
Board::~Board() {
    for (int i = 0; i < numRows; ++i) {
        delete[] panel[i];
    }
    delete[] panel;
    panel = nullptr;
}


// Task B: define randomize, getInfo, display, and valueCorrect methods


// 2.31 Method randomize 

void Board::randomize() {
    int totalElements = numRows * numCols;
    std::vector<int> temp(totalElements);
    
    for (int i = 0; i < totalElements; ++i) {
        temp[i] = i + 1;
    }
    std::srand(2);

    int currLastIdx = totalElements - 1;
    while (currLastIdx > 0) {
        int k = std::rand() % (currLastIdx + 1);  
        std::swap(temp[k], temp[currLastIdx]);   
        --currLastIdx;                           
    }

    int index = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            panel[row][col] = temp[index++];
        }
    }
    getInfo();  
}

// 3.2 Define method display

void printSeparateLine(int numCols) {
    std::cout << "+";
    for (int col = 0; col < numCols; col++) {
        std::cout << "-----+";
    }
    std::cout << std::endl;
}

void Board::display() const {
    printSeparateLine(numCols);
    for (int row = 0; row < numRows; ++row) {
        std::cout << "|";
                for (int col = 0; col < numCols; ++col) {
                    if (panel[row][col] == numRows * numCols) {
                        std::cout << "     |";
                } else {
                    std::cout << "  " << panel[row][col] << "  |";
            }
        }
        std::cout << std::endl;
        printSeparateLine(numCols);
    }
}

// 3.3 Define method valueCorrect

bool Board::valueCorrect(int row, int col) const {
    int correctValue = row * numCols + col + 1;
    if (panel[row][col] == correctValue && panel[row][col] >= 1 && panel[row][col] <= numRows * numCols - 1) {
        return true;
    }
    return false;
}

// 3.4 Define method getInfo
void Board::getInfo() {
    numCorrect = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (panel[row][col] == numRows * numCols) {
                emptyCellRow = row;
                emptyCellCol = col;
            } else if (valueCorrect(row, col)) {
                numCorrect++;
            }
        }
    }
}


// Task C: define slideUp, slideDown, slideLeft, and slideRight methods


// 4.1 Define method slideUp

void Board::slideUp() {

    if (emptyCellRow + 1 >= numRows) {
        return; 
    }

    int downRow = emptyCellRow + 1;
    int downCol = emptyCellCol;

    if (valueCorrect(downRow, downCol)) {
        numCorrect--; 
    }
    int temp = panel[emptyCellRow][emptyCellCol];
    panel[emptyCellRow][emptyCellCol] = panel[downRow][downCol];
    panel[downRow][downCol] = temp;

    if (valueCorrect(emptyCellRow, emptyCellCol)) {
        numCorrect++;
    }
    emptyCellRow = downRow;
    display();
}

// 4.2 slideDown
void Board::slideDown() {
    if (emptyCellRow - 1 < 0) {
        return; 
    }
    int upRow = emptyCellRow - 1;
    int upCol = emptyCellCol;

    if (valueCorrect(upRow, upCol)) {
        numCorrect--; 
    }
    int temp = panel[emptyCellRow][emptyCellCol];
    panel[emptyCellRow][emptyCellCol] = panel[upRow][upCol];
    panel[upRow][upCol] = temp;

    if (valueCorrect(emptyCellRow, emptyCellCol)) {
        numCorrect++;
    }

    emptyCellRow = upRow; 
    display();
}

// 4.3 slideUp
void Board::slideLeft() {
    if (emptyCellCol + 1 >= numCols) {
        return; 
    }

    int rightCol = emptyCellCol + 1;
    int rightRow = emptyCellRow;

    if (valueCorrect(rightRow, rightCol)) {
        numCorrect--; 
    }

    int temp = panel[emptyCellRow][emptyCellCol];
    panel[emptyCellRow][emptyCellCol] = panel[rightRow][rightCol];
    panel[rightRow][rightCol] = temp;

        if (valueCorrect(emptyCellRow, emptyCellCol)) {
        numCorrect++;
    }

    emptyCellCol = rightCol; 
    display();
}


// 4.3 slideLeft
void Board::slideRight() {
    if (emptyCellCol - 1 < 0) {
        return; 
    }

    int leftCol = emptyCellCol - 1;
    int leftRow = emptyCellRow;

    if (valueCorrect(leftRow, leftCol)) {
        numCorrect--; 
    }

    int temp = panel[emptyCellRow][emptyCellCol];
    panel[emptyCellRow][emptyCellCol] = panel[leftRow][leftCol];
    panel[leftRow][leftCol] = temp;

    if (valueCorrect(emptyCellRow, emptyCellCol)) {
        numCorrect++;
    }

    emptyCellCol = leftCol;
    display();
}


// Task D: Define play method

void Board::play() {
    display();
    int move = 0;
    while (true) { //TODO: fill in condition
        char ch = getchar();
        if (ch == 'S' || ch == 's') //STOP
            break;

        if (ch == '\[') { // if the first value is esc
            getchar(); // skip the [
            switch (getchar()) { // the real value
                case 'A': // Arrow up
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide UP." << std::endl;
                    slideUp();
                    break;
                case 'B': // Arrow down
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide DOWN." << std::endl;
                    slideDown(); // TODO: implement this method in Task C
                    break;
                case 'C': // Arrow right
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide RIGHT." << std::endl;
                    slideRight(); // TODO: implement this method in Task C
                    break;
                case 'D': // Arrow left
                    move++;
                    std::cout << "\nMove " << std::setw(4) << move << ": ";
                    std::cout << "Slide LEFT." << std::endl;
                    slideLeft(); // TODO: implement this method in Task C
                    break;
            }
        }
    }

    std::cout << "\nCongratulations. Total number of moves is " << move << "." << std::endl;
}
