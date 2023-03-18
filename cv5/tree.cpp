#include "tree.h"
#include <iostream>
#include <iomanip> // std::setw, std::right
#include <queue>   // height() a wide_print()
#include <stack>   // print_with_stack()

tree::tree()
{
    root = nullptr;
}

tree::~tree()
{
    clear(root);
}

void tree::clear(vertex * branch)
{
    std::stack<vertex*> s;
    vertex* current = root;

    while (current || !s.empty()) {
        if (current) {
            s.push(current);
            current = current->left;
        } else {
            current = s.top();
            s.pop();
            vertex* temp = current->right;
            delete current;
            current = temp;
        }
    }

    root = nullptr;
}

bool tree::empty()
{
    return root == nullptr;
}

bool tree::insert(T key)
{
    if (empty())
    {
        root = new vertex(key, nullptr);
        return true;
    }

    vertex * curr = root;
    while(true)
    {
        if(key == curr->key) return false;
        else if(key < curr->key)
        {
            if(curr->left == nullptr) {
                curr->left = new vertex(key, curr);
                return true;
            }
            curr = curr->left;
        }
        else
        {
            if(curr->right == nullptr) {
                curr->right = new vertex(key, curr);
                return true;
            }
            curr = curr->right;
        }
    }
}

tree::vertex * tree::find(T key)
{
    vertex * curr = root;

    while(curr != nullptr)
    {
        if(key == curr->key) break;
        else if(key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return curr;
}


bool tree::remove(T key)
{
    vertex * pom = find(key);
    if(pom == nullptr)
        return false;

    if(pom->left != nullptr && pom->right != nullptr)
    {
        remove_with_two(pom);
    }
    else if(pom->left != nullptr || pom->right != nullptr)
    {
        remove_with_one(pom);
    }
    else
    {
        remove_leaf(pom);
    }
    return true;
}

void tree::remove_leaf(vertex *leaf)
{
    if(leaf->parent == nullptr)
        root = nullptr;
    else
    {
        vertex* father = leaf->parent;
        if(leaf == father->left)
            father->left = nullptr;
        else
            father->right = nullptr;
    }

    delete leaf;
}

void tree::remove_with_one(vertex *pom)
{
    vertex * father = pom->parent;
    vertex * child = (pom->left == nullptr) ? pom->right : pom->left;

    if(father == nullptr)
    {
        root = child;
    }
    else
    {
        if(father->left == pom)
            father->left = child;
        else
            father->right = child;
    }

    child->parent = father;
    delete pom;
}

void tree::remove_with_two(vertex *pom)
{
    vertex * swap_vertex = max(pom->left);
    pom->key = swap_vertex->key;

    if(swap_vertex->left != nullptr)
        remove_with_one(swap_vertex);
    else
        remove_leaf(swap_vertex);
}

tree::vertex * tree::max(vertex * branch)
{
    vertex * pom = branch;

    while(pom->right != nullptr)
        pom = pom->right;

    return pom;
}

tree::vertex * tree::min(vertex * branch)
{
    vertex * pom = branch;

    while(pom->left != nullptr)
        pom = pom->left;

    return pom;
}

void tree::print()
{
    print_recursively(root);
    std::cout << std::endl;
}

void tree::print_recursively(vertex * branch)
{
    if(branch == nullptr)
        return;

    print_recursively(branch->left);
    std::cout << branch->key << ", ";
    print_recursively(branch->right);
}

void tree::print_with_stack()
{
    std::stack<vertex *> s;
    vertex * curr = root;

    while(curr != nullptr || !s.empty())
    {
        while (curr != nullptr)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top(); s.pop();
        std::cout << curr->key << ", ";
        curr = curr->right;
    }
    std::cout << std::endl;
}

void tree::print_iteratively()
{
    if(empty())
        return;

    vertex* curr = min(root);

    while(curr)
    {
        std::cout << curr->key << ", ";
        if(curr->right) {
            curr = min(curr->right);
        } else {
            vertex * father = curr->parent;
            while(father != nullptr && curr == father->right)
            {
                curr = father;
                father = curr->parent;
            }
            curr = father;
        }
    }
    std::cout << std::endl;
}

unsigned int tree::height()
{
    if(empty())
        return 0;

    vertex * curr;
    std::queue<vertex *> q;
    unsigned int h = 0;

    q.push(root);

    while(!q.empty())
    {
        int level_size = q.size();
        for(int i = 0; i < level_size; i++)
        {
            curr = q.front();
            q.pop();
            if(curr->left)
                q.push(curr->left);
            if(curr->right)
                q.push(curr->right);
        }
        h++;
    }
    return h;
}


void tree::wide_print()
{
    unsigned int h = height();
    unsigned int space = (1 << (h - 1));
    std::queue<vertex *> q;
    q.push(root);
    vertex * curr;

    for(unsigned int i = 1; i <= h; i++)
    {
        unsigned int level_size = q.size();
        for(unsigned int j = 0; j < level_size; j++)
        {
            curr = q.front();
            q.pop();
            std::cout << std::setw(space * 2) << std::right;
            if(curr) {
                q.push(curr->left);
                q.push(curr->right);
                std::cout << curr->key;
            } else {
                q.push(nullptr);
                q.push(nullptr);
                std::cout << "  ";
            }
            std::cout << std::setw(space * 2) << " ";
        }
        space /= 2;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//__________________________________________________________________

tree::const_iterator tree::begin()
{
    return const_iterator(min(root));
}

tree::const_iterator tree::end()
{
    return const_iterator(nullptr);
}

tree::const_iterator tree::rbegin() {
    return tree::const_iterator(max(root));
}

tree::const_iterator tree::rend() {
    return tree::const_iterator(nullptr);
}