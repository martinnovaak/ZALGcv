#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>
#include <set>
#include <array>

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

void shell_sort(std::vector<int> & array) {
    int n = array.size();
    for(int gap = pow(2, int(log2(n))) - 1; gap > 0; gap /= 2)
    {
        for (int i = gap; i < array.size(); i++) {
            int key = array[i];
            int j = i - gap;

            while (j >= 0 && array[j] > key) {
                array[j + gap] = array[j];
                j -= gap;
            }

            array[j + gap] = key;
        }
    }
}

void tree_sort(std::vector<int> & array) {
    std::multiset<int> tree;
    for(int a: array)
        tree.insert(a);
    std::copy(tree.begin(), tree.end(), array.begin());
}

void merge(std::vector<int> & array, int l1, int r1, int l2, int r2) {
    int i = l1, j = l2, k = 0;
    int n1 = r1 - l1 + 1;
    int n2 = r2 - l2 + 1;
    std::vector<int> pom(n1 + n2);

    while(i <= r1 && j <= r2) {
        if(array[i] <= array[j]) {
            pom[k] = array[i];
            i++;
        } else {
            pom[k] = array[j];
            j++;
        }
        k++;
    }

    while(i <= r1) {
        pom[k] = array[i];
        i++;
        k++;
    }

    //for(i = l1, j = 0; j < k; i++, j++)
    //    array[i] = pom[j];
    memcpy(&array[l1], &pom[0], k* sizeof(int));
}

void merge_sort_rec(std::vector<int> & array, int l, int r) {
    if(l == r)
        return;

    int middle = (l+r)/2;

    merge_sort_rec(array, l, middle);
    merge_sort_rec(array, middle + 1, r);

    merge(array, l, middle, middle + 1, r);
}

void merge_sort(std::vector<int> & array) {
    enum signature {
        SPLIT, MERGE
    };
    std::stack<std::tuple<signature, int, int, int>> stack1;
    stack1.emplace(SPLIT, 0, array.size() / 2, array.size() - 1);

    while(!stack1.empty()) {
        auto [sign, l, m, r] = stack1.top();
        stack1.pop();
        if(sign == SPLIT) {
            stack1.emplace(MERGE, l, m, r);
            if(l < m) {
                stack1.emplace(SPLIT, l, (l+m)/2, m);
            }
            if(m + 1 < r) {
                stack1.emplace(SPLIT, m+1, (m + 1 + r) / 2, r);
            }
        } else {
            merge(array, l, m, m + 1, r);
        }
    }
}

void heapify(std::vector<int> & array, int left, int right) {
    int i = left;
    int j = i * 2 + 1;
    int temp = array[left];
    while(j <= right) {
        if(j < right && array[j] < array[j + 1]) {
            j++;
        }
        if(temp >= array[j]){
            break;
        }
        array[i] = array[j];
        i = j;
        j = 2 * i + 1;
    }
    array[i] = temp;
}

void heap_sort(std::vector<int> & array) {
    int l = array.size() / 2;
    int r = array.size() - 1;

    while(l) {
        l--;
        heapify(array, l, r);
    }

    while(r) {
        std::swap(array[0], array[r]);
        r--;
        heapify(array, 0, r);
    }
}

int partition3(std::vector<int> & arr, int left, int right) {
    int pivot = arr[left];
    int i = left + 1;
    int j = right + 1;

    while(i < j) {
        if(arr[i] < pivot) {
            i++;
        } else {
            j--;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[left], arr[j - 1]);
    return j - 1;
}

std::pair<int, int> partition2(std::vector<int> & arr, int left, int right) {
    int pivot = arr[(left + right)/2];
    while(left < right) {
        while(arr[left] < pivot) {
            left++;
        }
        while(arr[right] > pivot) {
            right--;
        }
        if(left <= right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
    return {right, left};
}

void quicksort(std::vector<int> & arr, int l, int r) {
    if(l >= r)
        return;

    int mid = partition3(arr, l, r);

    quicksort(arr, l, mid - 1);
    quicksort(arr, mid + 1, r);
}

void quicksort(std::vector<int> & arr) {
    std::stack<std::pair<int, int>> stack1;
    stack1.emplace(0, arr.size() - 1);

    while(!stack1.empty()) {
        auto[left, right] = stack1.top();
        stack1.pop();

        if(left >= right)
            continue;

        auto [r, l] = partition2(arr, left, right);

        stack1.emplace(l, right);
        stack1.emplace(left, r);
    }
}

int hoare(std::vector<int> & arr, int pos) {
    int l = 0, r = arr.size() - 1;
    while(l < r) {
        int mid = partition3(arr, l, r);
        if(mid == pos) {
            return arr[pos];
        } else if (mid > pos) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}

void radix_sort(std::vector<int> & arr, int digits) {
    std::array<std::vector<int>, 10> fronty;

    int z = 10;
    int d = 1;

    while(digits) {
        for (int i : arr) {
            int j = (i / d) % z;
            fronty[j].push_back(i);
        }
        d *= z;

        int pom = 0;
        for (auto & q : fronty) { // zde na hodine chybel &
            for (int number : q) {
                arr[pom] = number;
                pom++;
            }
            q.clear();
        }
        digits--;
    }
}

int main() {
    std::vector<int> arr = { 12, 11, 13, 17, 4, 87, 95, 16, 49, 31, 1, 2, 4, 64, 834, 328, 46, 71, 4, 4, 4, 4 };
    int n = arr.size();
    // radix_sort(arr, 3);

    //quicksort(arr, 0, n - 1);
    //std::cout << hoare(arr, 10) << std::endl;
    //heap_sort(arr);
    //shell_sort(arr);
    //tree_sort(arr);
    //merge_sort(arr);
    //quicksort(arr, 0, n - 1);
    //quicksort(arr);
    hoare(arr, 10);
    std::cout << arr[10] << std::endl;

    //radix_sort(arr, 3);

    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    /*
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100000);
    const auto m = 10'000'000;
    std::vector<int> v1(m);
    std::generate(v1.begin(), v1.end(), [&](){ return dis(gen); });
    std::vector<int> v2 = v1, v3 = v1, v4 = v1, v5 = v1;



    auto start = std::chrono::high_resolution_clock::now();
    heap_sort(v1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds\n";

    start = std::chrono::high_resolution_clock::now();
    //shell_sort(v2);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds\n";

    start = std::chrono::high_resolution_clock::now();
    merge_sort_rec(v3, 0, m - 1);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds\n";

    start = std::chrono::high_resolution_clock::now();
    std::sort(v4.begin(), v4.end());
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds\n";

    start = std::chrono::high_resolution_clock::now();
    tree_sort(v5);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds\n";
*/


    return 0;
}
