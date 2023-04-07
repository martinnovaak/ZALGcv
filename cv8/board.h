#ifndef BACKTRACK_BOARD_H
#define BACKTRACK_BOARD_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>

class board{
private:
    std::vector<int> mailbox;
    std::vector<int> knight_moves;
    std::vector<int> queen_moves;
    int n; // n x n

    bool knights_tour(int square) {
        mailbox[square] = 1;
        std::stack<std::tuple<int, int>> z; // zasobnik, v kterem je ulozena prochazka (policko, index tahu z knight_moves)
        z.emplace(square, -1);

        while(!z.empty())
        {
            auto& [prev_square, move] = z.top();

            if(n*n == mailbox[prev_square]) {
                return true;
            }

            if(move != -1) {
                mailbox[prev_square + knight_moves[move]] = 0;
            }

            move += 1;


            while(move < knight_moves.size() && mailbox[prev_square + knight_moves[move]] != 0) {
                move++; // pokud pod indexem move neni legalni tah prejdi na dalsi tah
            }

            if(move != knight_moves.size()) { // pokud je move v mezich
                int new_square = prev_square + knight_moves[move];
                mailbox[new_square] = mailbox[prev_square] + 1;
                z.emplace(new_square, -1);
            } else { // jinak BACKTRACKING
                z.pop(); // odstran policko z prochazky
            }
        }
        // pokud jsme nenalezli zadnou prochazku -> prochazka neexistuje (pro male sachovnice 2x2, 3x3, 4x4)
        return false;
    }

    // Funkce, ktera vypocte stupen policka square (pocet legalnich tahu z daneho policka)
    int degree(int square) {
        int deg = 0;
        for (auto move : knight_moves) {
            int new_square = square + move;
            if (mailbox[new_square] == 0) {
                deg++;
            }
        }
        return deg;
    }

    // Funkce, ktera najde vsechny legalni tahy a jejich stupne, dane tahy usporada tak, aby tahy s nejmensim stupnem byly prvni
    // funkce vraci vektor usporadany vektor stupnu a tahu
    std::vector<std::pair<int, int>> find_legal_moves(int square) { // WARNSDORFF
        std::vector<std::pair<int, int>> legal_moves;
        for(int i = 0; i < knight_moves.size(); i++) {
            int new_square = square + knight_moves[i];
            if(mailbox[new_square] == 0) {
                legal_moves.emplace_back(degree(new_square), i);
            }
        }
        std::sort(legal_moves.begin(), legal_moves.end());
        return legal_moves; // ve skutecnosti by nam stacil vratit vektor pouze usporadanych tahu
        // stupne uz nas dale nezajimaji (moznost dalsiho vylepseni)
    }

    // Prochazka konem pres backtracking pouzivajici warnsdorffovu heuristiku
    // Rekurze je nahrazena pres zasobnik
    bool knights_walk_warnsdorff(int square) {
        mailbox[square] = 1;
        std::stack<std::tuple<int,int, std::vector<std::pair<int, int>>>> z; // zasobnik pro nahrazeni rekurze
        z.emplace(square, -1, find_legal_moves(square)); // vlozeni prvniho tahu do zasobniku

        while(!z.empty())
        {
            // ze zasobniku si vytahneme (ale nevyjmeme) posledni navstivene policko
            auto& [prev_square, move, legal_moves] = z.top();

            if(n*n == mailbox[prev_square]) { // pokud je prochazka kompletni
                return true;
            }

            if(move != -1) { // pokud nastal backtracking
                mailbox[prev_square + knight_moves[legal_moves[move].second]] = 0; // clear
            }

            move += 1; // prejdi na dalsi index tahu

            if(move < legal_moves.size()) { // pokud stale jeste zbyvaji nejake legalni tahy
                int new_square = prev_square + knight_moves[legal_moves[move].second];
                mailbox[new_square] = mailbox[prev_square] + 1;
                z.emplace(new_square, -1, find_legal_moves(new_square)); // pridej nove policko do prochazky
            } else { // pokud uz zadne legalni tahy nezbyvaji -> BACKTRACKING
                z.pop(); // odstran policko z prochazky
            }
        }
        return false;
    }

    // Nahrazeni rekurze pres metodu s GOTO viz skripta
    bool knights_tour_goto(int square) {
        std::stack<std::tuple<int, int, int>> stack;
        stack.emplace(square, 1, 0);

        L_0:
        auto & [old_square, visited, move] = stack.top();
        mailbox[old_square] = visited;
        if(visited < n*n) {
            int new_square;
            while(move < 8){
                new_square = old_square + knight_moves[move];
                move++;

                if(mailbox[new_square] != 0)
                    continue;

                stack.emplace(new_square, visited+1, 0);
                goto L_0;
            }

            // backtrack
            if(stack.empty())
                return false;

            mailbox[old_square] = 0;
            stack.pop();
            goto L_0;
        }
        return true;
    }
public:
    board(int n)
    : mailbox((n + 4) * (n + 2), -1), n(n) {
        for(int i = 0; i < n; i++) {
            int k = (2 + i) * (n + 2) + 1;
            for(int j = 0; j < n; j++) {
                mailbox[k] = 0;
                k += 1;
            }
        }

        knight_moves = {-2*n - 5, -2*n - 3, -n - 4, -n, n, n + 4, 2*n +3, 2*n + 5};
        queen_moves = {-n - 3, -1, n + 1};
    }

    void print_whole_board() {
        for(int i = n + 3; i >= 0; i--) {
            for(int j = 0; j < n + 2; j++) {
                std::cout << std::setw(3) << mailbox[i * (n + 2) + j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    void print_board() {
        for(int i = n - 1; i >= 0; i--) {
            int k = (2 + i) * (n + 2) + 1;
            for(int j = 0; j < n; j++, k++) {
                std::cout << std::setw(3) <<mailbox[k] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    // vypis sachovnice do souboru (vhodne pro velke sachovnice)
    void print_board_to_file() {
        std::ofstream outfile("board.txt");
        for (int i = n - 1; i >= 0; i--) {
            int k = (2 + i) * (n + 2) + 1;
            for (int j = 0; j < n; j++, k++) {
                outfile << std::setw(5) << mailbox[k] << " ";
            }
            outfile << "\n";
        }
        outfile.close();
    }

    bool knights_tour_warnsdorff(int x, int y) {
        int square = (2+x) * (n+2) + y + 1;
        if(knights_walk_warnsdorff(square))
            std::cout << "FOUND\n";
        else
            std::cout << "NOT FOUND\n";
    }

    void knights_tour(int x, int y) {
        int square = (2+x) * (n+2) + y + 1;
        if(knights_tour(square))
            std::cout << "FOUND\n";
        else
            std::cout << "NOT FOUND\n";

    }
};

#endif //BACKTRACK_BOARD_H
