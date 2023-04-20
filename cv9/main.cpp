#include <random>
#include <algorithm>
#include <chrono>
#include <list>
#include <fstream>
#include "linked_list.h"

void selection_sort_naive(std::vector<int> & array) {
    for(int min = 0; min < array.size() - 1; min++) {
        for(int j = min + 1; j < array.size(); j++) {
            if(array[min] > array[j]) {
                std::swap(array[min], array[j]);
            }
        }
    }
}

void selection_sort(std::vector<int> & array) {
    for(int min = 0; min < array.size() - 1; min++) {
        int smallest = min;
        for(int j = min + 1; j < array.size(); j++) {
            if(array[min] > array[j]) {
                smallest = j;
            }
        }
        if(smallest != min) {
            std::swap(array[smallest], array[min]);
        }
    }
}

void insertion_sort(std::vector<int> & array) {
    for (int i = 1; i < array.size(); i++) {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}

void binary_insertion_sort(std::vector<int>& array) {
    for (int i = 1; i < array.size(); ++i) {
        int key = array[i];
        int left = 0, right = i;

        // binary search
        while (left < right) {
            int mid = (left + right) / 2;
            if (array[mid] < key) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        for (int j = i; j > left; --j) {
            array[j] = array[j - 1];
        }
        array[left] = key;
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

void bubble_sort2(std::vector<int>& array) {
    bool swapped;
    for (int i = 0; i < array.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < array.size(); j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void bubble_sort3(std::vector<int>& array) {
    bool swapped;
    for (int i = 0; i < array.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < array.size() - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void bubble_sort4(std::vector<int>& array) {
    int last_swap;
    for (int i = 0; i < array.size() - 1; i++) {
        last_swap = array.size() - i - 1;
        for (int j = 0; j < array.size() - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                last_swap = j;
            }
        }
        if (last_swap == array.size() - i - 1) break;
    }
}

void shaker_sort(std::vector<int>& array) {
    int n = array.size();
    int left = 0, right = n - 1, k = 0;

    while (left < right) {
        for (int i = left; i < right; i++) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                k = i;
            }
        }
        right = k;
        for (int i = right; i > left; i--) {
            if (array[i] < array[i - 1]) {
                std::swap(array[i], array[i - 1]);
                k = i;
            }
        }
        left = k;
    }
}


void compare_sorts() {
    unsigned int len = 30'000;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0.0, 100000.0);
    std::vector<int> vec_ran(len);
    for(auto & a : vec_ran)
        a = dist(rng);

    std::list<int> l;
    for(int i = 0; i < len; i++)
        l.push_back(vec_ran[i]);

    linkedlist<int> l1(vec_ran);
    linkedlist<int> l2(vec_ran);
    linkedlist<int> l3(vec_ran);
    linkedlist<int> l4(vec_ran);
    linkedlist<int> l5(vec_ran);
    linkedlist<int> l6(vec_ran);
    linkedlist<int> l7(vec_ran);
    linkedlist<int> l8(vec_ran);

    auto start = std::chrono::high_resolution_clock::now();
    l.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time quicksort: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l1.selection_sort1();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time selection1: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l2.selection_sort2();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time selection2: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l3.insertion_sort();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time insertion: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l4.bubble_sort1();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time bubble1: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l5.bubble_sort2();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time bubble2: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l6.bubble_sort3();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time bubble3: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    l8.shaker_sort();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time shaker: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

}


template <typename T>
void load_data_from_file(linkedlist<T> & l, const std::string & filename)
{
    std::ifstream input(filename);
    T value;
    if(input.is_open()) {
        while (input >> value) {
            l.push_back(value);
        }
        input.close();
    }
}

struct employee {
    std::string name;
    int wage;
};

bool compare1(employee z1, employee z2) {
    return z1.wage < z2.wage;
}

int main() {
    linkedlist<employee> l({
        {"Martin", 50}, {"Jan", 20},
    });

    std::vector<employee> list({{"Martin", 50}, {"Jan", 20}, });
    std::sort(list.begin(), list.end(), compare1);

    l.selection_sort(compare1);


    compare_sorts();
    //linkedlist<int> l;
    //load_data_from_file<int>(l, "data.txt");
    //l.print();
    return 0;
}
