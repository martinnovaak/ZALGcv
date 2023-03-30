#ifndef BACKTRACK_BOARD_H
#define BACKTRACK_BOARD_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>

class board{
    std::vector<int> mailbox;
    std::vector<int> knight_moves;
    std::vector<int> queen_moves;
    int n; // n x n

    bool is_safe(int square) {
        for(auto move: queen_moves) {
            int new_square = square + move;
            while(mailbox[new_square] == 0) {
                new_square += move;
            }
            if(mailbox[new_square] == 1)
                return false;
        }
        return true;
    }


    int n_queens_rec(int square, int file) {
        mailbox[square] = 1;
        int results = 0;
        if(file == n) {
            //print_board();
            results = 1;
        } else {
            for(int rank = 0; rank < n; rank++) {
                int new_square = (rank + 2) * (n + 2) + 1 + file;
                if(is_safe(new_square))
                    results += n_queens_rec(new_square, file + 1);

            }
        }
        mailbox[square] = 0;
        return results;
    }

    bool knights_tour_rec(int square, int visited) {
        mailbox[square] = visited;
        if(visited == n*n) {
            //print_board();
            print_whole_board();
            return true;
        } else {
            int new_square;
            for (auto move : knight_moves) {
                new_square = square + move;
                if(mailbox[new_square] != 0)
                    continue;

                if(knights_tour_rec(new_square, visited + 1))
                    return true;
            }
        }
        mailbox[square] = 0;
        return false;
    }

    bool knights_walk_warnsdorff(int square, int visited) {
        mailbox[square] = visited;

        if(visited == n * n) {
            //print_board();
            return true;
        } else {
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> next_moves;
            for (int move: knight_moves) {
                int attacked_square = square + move;
                if (mailbox[attacked_square] != 0)
                    continue;

                int degree = 0;
                for (int next_move : knight_moves) {
                    int next_square = attacked_square + next_move;
                    if (mailbox[next_square] == 0) {
                        degree++;
                    }
                }
                next_moves.emplace(degree, attacked_square);
            }

            while (!next_moves.empty()) {
                int attacked_square = next_moves.top().second;
                next_moves.pop();

                if(knights_walk_warnsdorff(attacked_square, visited + 1))
                    return true;
            }
        }
        mailbox[square] = 0;
        return false;
    }

public:
    board(int n) : mailbox((n + 4) * (n + 2), -1), n(n) {
        for(int i = 0; i < n; i++) {
            int k = (2 + i) * (n + 2) + 1;
            for(int j = 0; j < n; j++) {
                mailbox[k++] = 0;
            }
        }

        knight_moves = {-2*n - 5, -2*n - 3, -n - 4, -n, n, n + 4, 2*n +3, 2*n + 5};
        queen_moves = {-n - 3, -1, n + 1};
    }

    void print_whole_board() {
        for(int i = n + 3; i >= 0; i--) {
            for(int j = 0; j < n + 2; j++) {
                std::cout << std::setw(2) << mailbox[i * (n + 2) + j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    void print_board() {
        for(int i = n - 1; i >= 0; i--) {
            int k = (2 + i) * (n + 2) + 1;
            for(int j = 0; j < n; j++, k++) {
                std::cout << std::setw(2) <<mailbox[k] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    int n_queens() {
        int results = 0;
        for(int i = 0; i < n; i++) {
            int square = (2+i)*(n+2) + 1;
            results += n_queens_rec(square, 1);
        }
        return results;
    }

    void knights_tour(int x, int y) {
        int square = (2+x) * (n+2) + y + 1;
        if(knights_walk_warnsdorff(square, 1))
            std::cout << "NALEZENO\n";
    }
};

#endif //BACKTRACK_BOARD_H
