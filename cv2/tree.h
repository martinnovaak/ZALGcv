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
    bool insert(T data); // metoda na vkladani hodnoty do stromu
    bool remove(T data); // metoda na odstraneni vrcholu s hodnotou data ze stromu
private:
    // Pomocne funkce (nelze je volat uzivatelem)
    vertex* find(T key);    // pomocna metoda na nalezeni prvku s hodnotou key ve strome
    void clear(vertex * branch); // pomocna rekurzivni metoda na odstraneni vrcholu z podstromu branch
    bool insert_recursively(vertex * branch, T data); // pomocna rekurzivni metoda na vlozeni prvku do podstromu branch
    vertex * find_recursively(vertex * branch, T data); // pomocna rekurzivni metoda na nalezeni prvku v podstrome branch

    void remove_leaf(vertex * pom); // pomocna metoda na odstraneni listu
    void remove_with_one(vertex * pom); // pomocna metoda na odstraneni vrcholu s jednim potomkem
    void remove_with_two(vertex * pom); // pomocna metoda na odstraneni vrcholu se dvema potomky

    vertex * max(vertex * branch);  // pomocna metoda na nalezeni nejvetsiho (nejpravejsiho) prvku v podstrome branch

    vertex * root;  // Koren stromu
};

// Vrchol stromu
struct tree::vertex
{
    T data; // klicova hodnota prvku - key value
    vertex * left;  // ukazatel na leveho syna (left child)
    vertex * right; // ukazatel na praveho syna (right child)
    vertex * parent; // ukazatel na otce (rodicovsky prvek) (parent node)

    // konstruktor vrcholu vertex -> nastavi klic a rodice na argumenty konstruktoru (d, par) a leveho a praveho syna na nullptr
    vertex(T d, vertex * par) : data(d), left(nullptr), right(nullptr), parent(par) {}
};

#endif //TREE_H
