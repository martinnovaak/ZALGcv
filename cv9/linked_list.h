#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class linkedlist {
private:
    struct node {
        T data;
        node * next;
        node * prev;
    };

    node * head;
    node * tail;
    unsigned int length;

    void push_behind(node * pom, const T &data) {
        if(pom == nullptr) {
            return;
        }

        if(pom == tail) {
            push_back(data);
            return;
        }

        node *new_node = new node{data, pom->next, pom};
        pom->next = new_node;
        new_node->next->prev = new_node;
        ++length;
    }

    void remove(node * pom) {
        if(pom == nullptr) {
            return;
        }

        if(pom == head) {
            pop_front();
        } else if(pom == tail) {
            pop_back();
        } else {
            pom->prev->next = pom->next;
            pom->next->prev = pom->prev;
            delete pom;
            length--;
        }
    }
public:
    linkedlist() : head(nullptr), tail(nullptr), length(0) {}
    linkedlist(linkedlist & list) : linkedlist() {
        node * pom = list.head;
        while(pom != nullptr) {
            push_back(pom->data);
            pom = pom->next;
        }
    }
    linkedlist(std::initializer_list<T> list) : linkedlist() {
        for(const T & item : list)
            push_back(item);
    }
    linkedlist(std::vector<T> vec) :linkedlist() {
        for(const T & item : vec)
            push_back(item);
    }
    ~linkedlist() {
        clear();
    }
    bool empty() const {return head == nullptr;}

    void clear() {
        while(!empty()) {
            pop_front();
        }
    }

    void push_front(const T & data) {
        node * pom = new node{data, head, nullptr};

        if(!empty()) {
            head->prev = pom;
        }

        head = pom;

        if(tail == nullptr) {
            tail = head;
        }

        length++;
    }

    void push_back(const T & data) {
        if(empty()) {
            push_front(data);
            return;
        }

        node * pom = new node{data, nullptr, tail};
        tail->next = pom;
        tail = pom;
        length++;
    }

    void pop_front() {
        if(empty()) {
           return;
        }

        node * pom = head;
        if(head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete pom;
        length--;
    }

    void pop_back() {
        if(empty()) {
            return;
        }

        node * pom = tail;
        if(head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete pom;
        length--;
    }

    void print() {
        for(node * pom = head; pom != nullptr; pom = pom->next) {
            std::cout << pom->data << " ";
        }
        std::cout << "\n";
    }

    void compare(const std::vector<T> & vec) {
        if(length != vec.size()) {
            std::cout << "NOT EQUAL " << length << " " << vec.size() << "\n";
            return;
        }

        node * pom = head;
        for(auto i : vec) {
            if(i != pom->data) {
                std::cout << "NOT EQUAL " << i << " " << pom->data << "\n";
                return;
            }
            pom = pom->next;
        }
        std::cout << "EQUAL\n";
    }

    void selection_sort_naive(std::vector<int> & array) {
        for(int min = 0; min < array.size() - 1; min++) {
            for(int j = min + 1; j < array.size(); j++) {
                if(array[min] > array[j]) {
                    std::swap(array[min], array[j]);
                }
            }
        }
    }

    void selection_sort1() {
        for(node * min = head; min != tail; min = min->next) {
            for(node * pom = min->next; pom != nullptr; pom = pom->next) {
                if(min->data > pom->data) {
                    std::swap(min->data, pom->data);
                }
            }
        }
    }

    void selection_sort2() {
        for(node * min = head; min != tail; min = min->next) {
            node * smallest = min;
            for(node * pom = min->next; pom != nullptr; pom = pom->next) {
                if(smallest->data > pom->data) {
                    smallest = pom;
                }
            }
            if(smallest != min) {
                std::swap(smallest->data, min->data);
            }
        }
    }

    void selection_sort(bool (* compare)(T, T)) {
        for(node * min = head; min != tail; min = min->next) {
            node * smallest = min;
            for(node * pom = min->next; pom != nullptr; pom = pom->next) {
                if(compare(smallest->data, pom->data)) {
                    smallest = pom;
                }
            }
            if(smallest != min) {
                std::swap(smallest->data, min->data);
            }
        }
    }

    void insertion_sort() {
        if(length < 2)
            return;

        for(node * pom = head->next; pom != nullptr; pom = pom->next) {
            node * first_bigger = head;

            if(pom->data > pom->prev->data) {
                continue;
            }

            while(first_bigger->data < pom->data) {
                first_bigger = first_bigger->next;
            }

            if(first_bigger == head) {
                push_front(pom->data);
            } else {
                push_behind(first_bigger->prev, pom->data);
            }
            pom = pom->prev;
            remove(pom->next);
        }
    }

    void bubble_sort1(std::vector<int>& array) {
        for (int i = 0; i < array.size() - 1; i++) {
            for (int j = 0; j < array.size() - 1; j++) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }

    void bubble_sort1() {
        for(int i = 0; i < length - 1; i++) {
            for(node * pom = head; pom != tail; pom = pom->next) {
                if(pom->next->data < pom->data) {
                    std::swap(pom->next->data, pom->data);
                }
            }
        }
    }

    void bubble_sort2() {
        for(int i = 0; i < length - 1; i++) {
            bool swapped = false;
            for(node * pom = head; pom != tail; pom = pom->next) {
                if(pom->next->data < pom->data) {
                    std::swap(pom->next->data, pom->data);
                    swapped = true;
                }
            }
            if(!swapped) return;
        }
    }

    void bubble_sort3() {
        node * last_swap = tail;
        for(unsigned int i = 0; i < length - 1; i++) {
            node * last_swap_help;
            for(node * pom = head; pom != last_swap; pom = pom->next) {
                if(pom->data > pom->next->data) {
                    std::swap(pom->data, pom->next->data);
                    last_swap_help = pom;
                }
            }
            if(last_swap == last_swap_help)
                return;
            last_swap = last_swap_help;
        }
    }

    void shaker_sort() {
        if(length < 2) return;

        node * left = head;
        node * right = tail;
        node * last_swap = tail;

        while(left != right) {
            for(node * pom = left; pom != right; pom = pom->next) {
                if(pom->next->data < pom->data) {
                    std::swap(pom->next->data, pom->data);
                    last_swap = pom;
                }
            }
            right = last_swap;
            for(node * pom = right; pom != left; pom = pom->prev) {
                if(pom->prev->data > pom->data) {
                    std::swap(pom->prev->data, pom->data);
                    last_swap = pom;
                }
            }
            left = last_swap;
        }
    }
};

#endif //LINKED_LIST_H