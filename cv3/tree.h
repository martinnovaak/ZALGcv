#ifndef TREE_H
#define TREE_H

using T = int;

class tree
{
private:
    struct vertex;  // Dopredna deklarace vrcholu stromu
public:
    // Verejne metody - lze je volat uzivatelem
    tree();     // Konstruktor binarniho stromu
    ~tree();    // Destruktor binarniho stromu

    bool empty(); // metoda vracejici informaci, zda-li je strom prazdny
    bool insert(T key); // metoda na vkladani hodnoty do stromu
    bool remove(T key); // metoda na odstraneni vrcholu s hodnotou data ze stromu

    void print();
    void print_with_stack();
    void print_iteratively();

    unsigned int height();
    void wide_print();
private:
    // Pomocne funkce (nelze je volat uzivatelem)
    vertex* find(T key);    // pomocna metoda na nalezeni prvku s hodnotou key ve strome
    void clear(vertex * branch); // pomocna rekurzivni metoda na odstraneni vrcholu z podstromu branch
    bool insert_recursively(vertex * branch, T key); // pomocna rekurzivni metoda na vlozeni prvku do podstromu branch
    vertex * find_recursively(vertex * branch, T key); // pomocna rekurzivni metoda na nalezeni prvku v podstrome branch
    void print_recursively(vertex * branch);

    void remove_leaf(vertex * pom); // pomocna metoda na odstraneni listu
    void remove_with_one(vertex * pom); // pomocna metoda na odstraneni vrcholu s jednim potomkem
    void remove_with_two(vertex * pom); // pomocna metoda na odstraneni vrcholu se dvema potomky

    static vertex * max(vertex * branch);  // pomocna metoda na nalezeni nejvetsiho (nejpravejsiho) prvku v podstrome branch
    static vertex * min(vertex * branch);

    vertex * root;  // Koren stromu
};

// Vrchol stromu
struct tree::vertex
{
    T key; // klicova hodnota prvku - key value
    vertex * left;  // ukazatel na leveho syna (left child)
    vertex * right; // ukazatel na praveho syna (right child)
    vertex * parent; // ukazatel na otce (rodicovsky prvek) (parent node)

    // konstruktor vrcholu vertex -> nastavi klic a rodice na argumenty konstruktoru (d, par) a leveho a praveho syna na nullptr
    vertex(T d, vertex * par) : key(d), left(nullptr), right(nullptr), parent(par) {}
};

#endif //TREE_H