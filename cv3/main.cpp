#include <iostream>
#include "tree.h"


int main() {
    tree tree1;
    //std::cout << tree1.empty() <<std::endl;

    tree1.insert(7);
    tree1.insert(3);
    tree1.insert(1);
    tree1.insert(2);
    tree1.insert(6);
    tree1.insert(10);
    tree1.insert(9);
    tree1.insert(11);
    tree1.insert(4);
    tree1.insert(5);
    tree1.print();
    tree1.print_with_stack();
    tree1.print_iteratively();
    tree1.wide_print();
    std::cout << "  ";

    tree1.remove(1);
    tree1.wide_print();
    tree1.remove(3);
    tree1.wide_print();
    tree1.remove(6);
    tree1.wide_print();
    tree1.remove(7);
    tree1.wide_print();
    tree1.remove(2);

    tree1.wide_print();
}
