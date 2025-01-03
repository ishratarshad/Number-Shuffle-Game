#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    Board();                  // 3 * 3 board
    Board(int m, int n);      // m * n board
    Board(int** arr, int m, int n); // m * n board with data from a 2-dimensional array
    ~Board();                 // Destructor

    void randomize();
    void getInfo();           // Find emptyCellRow, emptyCellCol, and numCorrect from panel
    bool valueCorrect(int row, int col) const;
    void display() const;

    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
    void play();

private:
    int numRows;
    int numCols;
    int** panel;
    int emptyCellRow;
    int emptyCellCol;
    int numCorrect;           // Tracks cells in the correct position
};

#endif