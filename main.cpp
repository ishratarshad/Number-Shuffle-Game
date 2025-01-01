#include <iostream>
#include "Board.hpp"
#include <cstdlib> //srand

int main() {
    srand(2);
    Board game(2, 3);
    game.play();
    return 0;
 }
