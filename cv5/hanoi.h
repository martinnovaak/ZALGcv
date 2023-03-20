#ifndef HANOI_H
#define HANOI_H

#include <vector>
#include <iostream>

class hanoi
{
private:
    std::vector<int> tower[3];
    unsigned int discs;

    void move_disc(int source, int destination){
        tower[destination].push_back(tower[source].back());
        tower[source].pop_back();
       // print_towers();
    }

    void move_discs(int n, int source, int auxilary, int destination)
    {
        if(n == 1)
        {
            move_disc(source, destination);
        }
        else
        {
            move_discs(n-1, source, destination , auxilary);
            move_disc(source, destination);
            move_discs(n-1, auxilary, source, destination);
        }
    }

    void print_towers()
    {
        std::cout << std::endl;
        std::cout << "A: ";
        for(int i : tower[0])
            std::cout << i << ", ";
        std::cout << std::endl;

        std::cout << "B: ";
        for(int i : tower[1])
            std::cout << i << " ";
        std::cout << std::endl;

        std::cout << "C: ";
        for(int i : tower[2])
            std::cout << i << " ";
        std::cout << std::endl;
    }
public:
    hanoi(unsigned int N = 1) : discs(N)
    {
        //tower[0] = std::vector<int>(N);
        tower[2].clear();
        for(unsigned int i = N; i >=1; i--)
            tower[0].push_back(i);
    }

    void solve() {
        print_towers();
        move_discs(discs, 0, 1 ,2);
    }
};


#endif //HANOI_H
