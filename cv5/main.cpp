#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "tree.h"
#include <stack>
#include <tuple>
#include "hanoi.h"


int binary_search(const std::vector<double> & arr, double value, int l, int r, int i)
{
    if(l > r) return - 1;
    //std::cout << i << std::endl;

    int mid = (l + r) / 2;
    if(arr[mid] == value) return mid;
    else if(arr[mid] > value) return binary_search(arr, value, l, mid - 1, i + 1);
    else return binary_search(arr, value, mid + 1, r, i + 1);
}

int binary_search_iterative(const std::vector<double> & arr, double value)
{
    int l = 0, r = arr.size() - 1, mid;
    while(arr[mid] != value && l <= r)
    {
        mid = (l+r)/2;
        if(arr[mid] == value) return mid;
        else if(arr[mid] > value) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

void build_perfect_tree(tree & t, const std::vector<int> & arr, int l, int r)
{
    if(l > r)
        return;

    int mid = (l+r) / 2;
    t.insert(arr[mid]);
    build_perfect_tree(t, arr, l, mid - 1);
    build_perfect_tree(t, arr, mid + 1, r);
}

#include <queue>

void build_perfect_tree_stack(tree & t, const std::vector<int> & arr)
{
    int mid;
    //std::stack<std::pair<int, int>> z;
    std::queue<std::pair<int, int>> z;
    z.emplace(0, arr.size()-1);

    while(!z.empty())
    {
        auto [l, r] = z.front();
        z.pop();
        if(l > r) continue;
        mid = (l + r) / 2;
        t.insert(arr[mid]);
        z.emplace(mid + 1, r);
        z.emplace(l, mid - 1);
    }
}


int main() {
    hanoi h(35);
    h.solve();



    const int N = 1'000'000;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist(0.0, 1000.0);
    std::vector<double> arr(N);
    std::vector<int> pole(31);
    for(int i = 0; i < 31; i++)
        pole[i] = i;

    tree t;
    build_perfect_tree(t, pole, 0, 30);
    t.wide_print();

    tree t2;
    build_perfect_tree_stack(t2, pole);
    t2.wide_print();

    for(int i = 0; i < N; i++)
        arr[i] = dist(rng);

    std::sort(arr.begin(), arr.end());

    std::cout << binary_search(arr, arr[789'235], 0, N-1, 1) << std::endl;
    std::cout << binary_search_iterative(arr, arr[789'235]) << std::endl;
    return 0;
}
