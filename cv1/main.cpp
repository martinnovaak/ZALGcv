#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
#include "stack.h"
#include "queue.h"
#include <stack>

int main()
{
    std::stack<int> stlst;
    vec::stack<int> vecst;
    ll::stack<int> llst;
    std::vector<int> vec;

    // nasleduje porovnani rychlosti zasobniku:
    // do kazdeho zasobniku nejprve vlozime 10 000 000 hodnot (prvku)
    // a nasledne je zas vsechny odstranime

    // 1) std::stack  - zasobnik ze standardni knihovny
    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < 10'000'000; i++)
        stlst.push(i);
    while(!stlst.empty())
        stlst.pop();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Operace zabrala: " << duration.count() << " milisekund" << std::endl;

    // 2) vec::stack  - zasobnik implementovany pres chytre dynamicke pole
    start = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < 10'000'000; i++)
        vecst.push(i);
    while(!vecst.empty())
        vecst.pop();

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Operace zabrala: " << duration.count() << " milisekund" << std::endl;
    // 3) ll::stack  - zasobnik implementovany pomoci jednosmerne zretezeneho spojoveho seznamu
    start = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < 10'000'000; i++)
        llst.push(i);
    while(!llst.empty())
        llst.pop();

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Operace zabrala: " << duration.count() << " milisekund" << std::endl;

    return 0;
}
