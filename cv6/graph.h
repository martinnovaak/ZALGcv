#ifndef GRAPH_GRAF_H
#define GRAPH_GRAF_H

#include <vector>
#include <stdexcept>
#include <queue>
#include <tuple>
#include <limits>
#include <iostream>

class graph
{
protected:
    std::vector<std::vector<double>> adjacency_matrix;
public:
    graph(int n) // konstruktor vytvori  n x n matici, kde vsechny prvky budou mit hodnoty -1.0
    : adjacency_matrix(n, std::vector<double>(n, -1.0)){}

    graph(const std::vector<std::vector<double>> & adj_mat) // konstruktor se zadanou adjacencni matici
    : adjacency_matrix(adj_mat) {} // zavolame kopirovaci konstruktor std::vectoru

    // pomocna metoda, kontrolujici zda-li vrcholy i a j se v grafu nachazeji
    bool is_out_of_bounds(unsigned int i, unsigned int j) const {
        return i >= adjacency_matrix.size() || j >= adjacency_matrix.size();
    }

    // setter nastavujici ohodnoceni hrany (i,j)
    void set_weight(unsigned int i, unsigned int j, double weight) {
        if(is_out_of_bounds(i, j))
            throw std::out_of_range("Index out of range.");

        adjacency_matrix[i][j] = adjacency_matrix[j][i] = weight;
    }

    // getter vracejici ohodnoceni hrany (i,j)
    double get_weight(unsigned int i, unsigned int j) const {
        if(is_out_of_bounds(i, j))
            throw std::out_of_range("Index out of range.");

        return adjacency_matrix[i][j];
    }

    // pomocna metoda vracejici pocet vrcholu grafu
    unsigned int number_of_vertices() {
        return adjacency_matrix.size(); // pocet vrcholu == pocet radku adjacencni matice
    }

    // hladovy algoritmus na hledani nejkratsi cesty v grafu
    // vracime dvojici vektoru delky n
    // prvni vektor ma na i-tem indexu hodnotu vzdalenosti nejkratsi cesty z vrcholu start vertex
    // druhy vektor ma na i-tem indexu index predchudce vrcholu na nejkratsi ceste
    std::pair<std::vector<double>, std::vector<int>> dijkstra(int start_vertex) {
        // na pocatku nastav vzdalenost do vsech vrcholu na "nekonecno"
        std::vector<double> distance(number_of_vertices(), std::numeric_limits<double>::max());
        distance[start_vertex] = 0.0; // vzdalenost do pocatku nastav na 0

        std::vector<int> predecessor(number_of_vertices(), -1); // nastav predchudce kazdeho vrcholu na -1 (tedy na zadny)

        // hranice - pres prioritni frontu
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> frontier;
        // info k std::priority_queue a jejim argumentum:
        // 1. argument std::pair<double, int> - do fronty budeme ukladat dvojice double-int (vzdalenost-predchudce)
        // 2. argument prioritni fronta bude reprezentovana pres std::vector - bude se jednat o binarni haldu - haldu lze efektivne reprezentovat polem
        // 3. argument std::greater<> - rika ze se jedna o tzv. min-heap tedy nejvyssi prioritu bude mit prvek s nejmensi hodnotou
        // Dalsi poznamka datova struktura std::pair je tak sikovne implementovana ze se to automaticky srovnava pres std::pair.first parametr
        // protoze std::pair obecne reprezentuje jednu dvojici klic-hodnota (struktura tedy automaticky predpoklada, ze usporadavame podle klice - coz taky delame)
        // std::greater<> : The element with the highest priority is the smallest element in the queue.
        frontier.emplace(0.0, start_vertex); // vloz do hranice pocatecni vrchol

        std::vector<bool> explored(number_of_vertices(), false); // vektor jiz prozkoumanych vrcholu (do prozkoumanych vrcholu
        // jiz zname nejkratsi cestu)

        while(!frontier.empty())
        {
            int u = frontier.top().second;
            frontier.pop();

            if(explored[u]) // zname-li jiz do vrcholu nejkratsi cestu (v hranici se nam muze stat, ze se nachazi vrcholu vickrat s ruznou vzdalenosti)
                continue;

            explored[u] = true; // ma-li nenavstiveny vrchol v hranici nejmensi vzdalenost => tak jiz kratsi cesta do nej neexistuje

            for (int v = 0; v < number_of_vertices(); v++) // relaxuj pres vsechny existujici hrany (u, v)
            {
                if(explored[v]) // zname-li jiz nejkratsi cestu do vrcholu v => skip
                    continue;

                // jinak proved relaxaci
                double weight = get_weight(u, v);
                if(weight > 0.0 && distance[u] + weight < distance[v]) // existuje-li hrana a zaroven je-li cesta z vrcholu u
                {               // rychlejsi nez dosavad nejrychlejsi cesta do vrcholu v
                    // uloz novou cestu
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                    // vloz vrchol s novou vzdalenosti do hranice
                    frontier.emplace(distance[v], v);
                }
            }
        }
        // vrat dvojici vektoru distance a predecessor
        return std::make_pair(distance, predecessor);
    }

    // dynamicky algoritmus na hledani nejkratsi cesty v grafu
    // vracime dvojici vektoru delky n
    // prvni vektor ma na i-tem indexu hodnotu vzdalenosti nejkratsi cesty z vrcholu start vertex
    // druhy vektor ma na i-tem indexu index predchudce vrcholu na nejkratsi ceste
    std::pair<std::vector<double>, std::vector<int>> bellman_ford(int start_vertex) {
        // na pocatku nastav vzdalenost do vsech vrcholu na "nekonecno"
        std::vector<double> distance(number_of_vertices(), std::numeric_limits<double>::max());
        distance[start_vertex] = 0.0; // vzdalenost do pocatku nastav na 0

        std::vector<int> predecessor(number_of_vertices(), -1); // nastav predchudce kazdeho vrcholu na -1 (tedy na zadny)


        // provedeme n-1krat relaxaci pres kazdou hranu v grafu
        for(unsigned i = 0; i < number_of_vertices() - 1; i++) // opakuj (n-1) krat:
        {
            for(unsigned int u = 0; u < number_of_vertices(); u++)
            {
                for(unsigned int v = 0; v < number_of_vertices(); v++)
                {
                    double weight = get_weight(u, v);
                    if(weight > 0.0 && distance[u] + weight < distance[v]) // relaxace
                    {
                        distance[v] = distance[u] + weight;
                        predecessor[v] = u;
                    }
                }
            }
        }

        // nejkratsi cesta v souvislem grafu o n vrcholech jde nejvyse pres n-1 hran
        // tedy po n-1 relaxaci pres kazdou hranu jiz nemuzeme najit kratsi cestu
        // nalezneme-li i v n-te relaxaci kratsi cestu tak mame v grafu zaporny cyklu
        for(unsigned int u = 0; u < number_of_vertices(); u++)
        {
            for(unsigned int v = 0; v < number_of_vertices(); v++)
            {
                double weight = get_weight(u, v);
                if(weight > 0.0 && distance[u] + weight < distance[v]) // relaxace
                {
                    throw std::runtime_error("Graph contains negative cycle.");
                }
            }
        }

        // vrat dvojici vektoru distance a predecessor
        return std::make_pair(distance, predecessor);
    }
};

class oriented_graph : public graph
{
public:
    oriented_graph(int n) : graph(n) {}
    oriented_graph(std::vector<std::vector<double>> adj_mat) : graph(adj_mat) {}

    void set_weight(unsigned int i, unsigned int j, double weight) {
        if(is_out_of_bounds(i, j))
            throw std::out_of_range("Index out of range.");

        adjacency_matrix[i][j] = weight;
    }
};

void print_graph(graph & g)
{
    std::cout << "Adjacency matrix: \n";
    std::cout << "j: ";
    for (int i = 0; i < g.number_of_vertices(); i++)
        std::cout << i << " ";
    std::cout << std::endl;
    for(int i = 0; i < g.number_of_vertices(); i++)
    {
        std::cout << i << " ";
        for(int j = 0; j < g.number_of_vertices(); j++)
        {
            double weight = g.get_weight(i, j);
            if (weight < 0.0)
                std::cout << "x" << " ";
            else std::cout << weight << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif //GRAPH_GRAF_H
