#include <iostream>
#include "graph.h"

void print_result(std::pair<std::vector<double>, std::vector<int>> actual)
{
    std::cout << std::endl;
    for (int i = 0; i < actual.first.size(); i++)
    {
        std::cout << i << " " << actual.first[i] << " " << actual.second[i] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    graph g(4);
    g.set_weight(0, 1, 2.0);
    g.set_weight(0, 2, 4.0);
    g.set_weight(1, 2, 1.0);
    g.set_weight(1, 3, 7.0);
    g.set_weight(2, 3, 3.0);

    print_graph(g);

    print_result(g.dijkstra(0));
    print_result(g.bellman_ford(0));

    std::vector<std::vector<double>> adjacency_m{
            {0, 7, 9, 0, 0, 14},
            {7, 0, 10, 15, 0, 0},
            {9, 10, 0, 11, 0, 2},
            {0, 15, 11, 0, 6, 0},
            {0, 0, 0, 6,  0,  9},
            {14, 0, 2, 0, 9, 0},
    };
    oriented_graph g2(adjacency_m);
    print_result(g2.dijkstra(0));

    print_result(g2.bellman_ford(0));

    return 0;
}
