#include <iostream>

#include "board.h"

int main() {
    board b(101);
    //b.print_board();
    //b.print_whole_board();

    //std::cout << b.n_queens() << std::endl;

    b.knights_tour(0,0);
    return 0;
}
