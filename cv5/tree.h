#ifndef TREE_H
#define TREE_H

using T = int;

class tree
{
private:
    struct vertex;
public:

    tree();
    ~tree();

    bool empty();
    bool insert(T key);
    bool remove(T key);

    void print();
    void print_with_stack();
    void print_iteratively();

    unsigned int height();
    void wide_print();

    class const_iterator;
    const_iterator begin();
    const_iterator end();
    const_iterator rbegin();
    const_iterator rend();
private:
    void clear(vertex * branch);
    void print_recursively(vertex * branch);

    vertex * find(T key);

    void remove_leaf(vertex * pom);
    void remove_with_one(vertex * pom);
    void remove_with_two(vertex * pom);

    static vertex * max(vertex * branch);
    static vertex * min(vertex * branch);

    vertex * root;
};

struct tree::vertex
{
    T key;
    vertex * left;
    vertex * right;
    vertex * parent;

    vertex(T d, vertex * par) : key(d), left(nullptr), right(nullptr), parent(par) {}

    friend class iterator;
};

class tree::const_iterator{
    vertex * current;
public:
    explicit const_iterator(vertex * start) : current(start) {}
    const T& operator*() { return current->key; }
    const_iterator& operator++() {
        move_to_successor();
        return *this;
    }
    const_iterator& operator--() {
        move_to_predecessor();
        return *this;
    }
    bool operator!=(const const_iterator& sentinel) const { return current != sentinel.current; }
    bool operator==(const const_iterator& sentinel) const { return current == sentinel.current; }
private:
    void move_to_successor() {
        if (current->right != nullptr) {
            current = min(current->right);
        } else {
            vertex * parent = current->parent;
            while (parent != nullptr && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }
            current = parent;
        }
    }
    void move_to_predecessor() {
        if (current->left != nullptr) {
            current = max(current->left);
        } else {
            vertex * parent = current->parent;
            while (parent != nullptr && current == parent->left) {
                current = parent;
                parent = parent->parent;
            }
            current = parent;
        }
    }
};

#endif //TREE_H