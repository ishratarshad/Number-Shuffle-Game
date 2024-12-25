#include "Board.hpp"
#include <iostream>
using namespace std;

// 2.1 The default constructor Board()
Board::Board() {
    numRows = 3;
    numCols = 3;

    panel = new int*[numRows];
    for (int i = 0; i < numRows; ++i) {
        panel[i] = new int[numCols];
    }

    int value = 1;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            panel[row][col] = value++;
        }
    }

    emptyCellRow = numRows - 1;
    emptyCellCol = numCols - 1;
    numCorrect = 0;
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

    int value = 1;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            panel[row][col] = value++;
        }
    }

    emptyCellRow = numRows - 1;
    emptyCellCol = numCols - 1;
    numCorrect = 0;
}

// 2.3 A nondefault constructor Board(int** arr, int m, int n)

Board::Board(int** arr, int m, int n) : Board(m, n) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            panel[row][col] = arr[row][col];
        }
    }

    emptyCellRow = numRows - 1;
    emptyCellCol = numCols - 1;
    numCorrect = 0;
}

// 2.4 The destructor

Board::~Board() {
    for (int i = 0; i < numRows; ++i) {
        delete[] panel[i];
    }
    delete[] panel;
}

