#include <iostream>
#include "Board.hpp"


int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Need ’A’-’C’ in parameters" << std::endl;
        return -1;
    }

    char type = *argv[1];
    std::string prompt;
    Board *game;
    int numRows = 3;
    int** arr;

    if (type == 'A') {
        prompt = "default constructor,";
        game = new Board;
    }
    else if (type == 'B') {
        prompt = "Board game(3, 5);";
        game = new Board(3, 5);
    }
    else if (type == 'C') {
        prompt = "Board game(arr, 3, 3);";
        const int NUM_COLS = 3;
        int brr[][NUM_COLS] = { {3, 9, 8}, {5, 7, 2}, {1, 6, 4} };
        arr = new int*[numRows];
        for (int row = 0; row < numRows; row++) {
            arr[row] = new int[NUM_COLS];
            for (int col = 0; col < NUM_COLS; col++)
                arr[row][col] = brr[row][col];
        }
        game = new Board(arr, 3, 3);
    }

    std::cout << "After " << prompt
              << " data member numRows is " << game->numRows << std::endl;
    std::cout << "After " << prompt
              << " data member numCols is " << game->numCols << std::endl;
    std::cout << "After " << prompt
              << " data member panel is " << std::endl;

    for (int row = 0; row < game->numRows; row++) {
        for (int col = 0; col < game->numCols; col++) {
            std::cout << game->panel[row][col];
            if (col < game->numCols-1) // Skip the last comma
                std::cout << ",";
        }
        std::cout << std::endl;
    }

    game->~Board();
    std::cout << "After calling destructor, data member panel is " << game->panel << std::endl;

    if (type == 'C') {
        for (int row = 0; row < numRows; row++) {
            delete[] arr[row];
            arr[row] = nullptr;
        }
        delete[] arr;
        arr = nullptr;
    }

    return 0;
}
