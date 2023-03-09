#include <iostream>
#include <tuple>
#include "hashmap.h"
#include <random>
#include <string>

std::size_t random_length()
{
    static std::mt19937 rng;
    static std::uniform_int_distribution dist = std::uniform_int_distribution{5, 10};
    return dist(rng);
}

std::string generate_random_alphanumeric_string()
{
    std::size_t len = random_length();
    static const std::string alphabet("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    static std::mt19937 rng;
    static std::uniform_int_distribution dist = std::uniform_int_distribution{0, (int)alphabet.length() - 1};
    std::string result = "";
    for(unsigned int i = 0; i < len; i++)
        result += alphabet[dist(rng)];
    return result;
}

#include <unordered_map>
#include <string>
#include <vector>

int main()
{
    unsigned int len = 10000; // pocet dvojic slov
    std::string s1, s2;

    hashmap map; // nase hashmapa
    std::unordered_map<std::string, std::string> stlmap; // stl hashmapa
    std::vector<std::string> v; // vektor pro ukladani klicu

    // testovani operatoru []
    for (unsigned int i = 0; i < len; i++)
    {
        s1 = generate_random_alphanumeric_string();
        s2 = generate_random_alphanumeric_string();

        map[s1] = s2;
        stlmap[s1] = s2;
        v.push_back(s1);
    }

    // test zda-li nase hashmapa dobre funguje
    for (unsigned int i = 0; i < len; i++)
    {
        if(map[v[i]] != stlmap[v[i]])
            std::cout << " Chyba";
    }

    // vypis poctu prvku v jednolivych kyblicich
    map.print_sizes();

    // pouziti operatoru [] s R-hodnotou
    std::cout << map[v[50]];
    return 0;
}
