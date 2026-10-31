#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

// ─── Search functions ────────────────────────────────────────────────────────

/**
 * @brief  Search for key in a sorted array of distinct integers using a
 *         linear scan.  O(n) time, O(1) space.
 * @param  arr  Pointer to a C-style array sorted in strictly ascending order.
 * @param  n    Number of elements in arr; must be >= 0.
 * @param  key  Value to search for.
 * @return Index i such that arr[i] == key, or -1 if key is not in arr.
 */
int search_linear(const int* arr, int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == key) return i;
        if (arr[i] >  key) return -1;   // passed where key would be
    }
    return -1;
}

/**
 * @brief  Search for key in a sorted array of distinct integers using
 *         exponential search.  O(log i) time, O(1) space, where i is the
 *         index of key in arr (or the index of the first element > key).
 *
 * @param  arr  Pointer to a C-style array sorted in strictly ascending order.
 * @param  n    Number of elements in arr; must be >= 0.
 * @param  key  Value to search for.
 * @return Index i such that arr[i] == key, or -1 if key is not in arr.
 */
int search_exponential(const int* arr, int n, int key) {
    int i = 1;
    while(i < n and arr[i] < key)
        i *= 2;

    int left = i/2;
    int right = std:: min(i, n-1);
    while(left <= right){
        int mid = (left + right)/2;
        if(arr[mid] == key) return mid;
        else if(arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

void run_on_external_input() {
    int n, target;
    std::cin >> n >> target;
    assert(n > 0);
    int* data = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::cout << search_linear(data, n, target) << std::endl;

    delete[] data;
}

void test_bigdata() {
    constexpr int N = 2000000;
    constexpr int target = 1000000;
    int bigdata[N];
    for (int i = 0; i < N; ++i) {
        bigdata[i] = i;
    }

    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    int res1 = search_linear(bigdata, N, target);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    int res2 = search_exponential(bigdata, N, target);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << "[ns]" << std::endl;
    std::cout << "Result = " << res1 << std::endl;

    std::cout << "Runtime for expo. = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << "[ns]" << std::endl;
    std::cout << "Result = " << res2 << std::endl;



}

int main() {
    run_on_external_input();
    test_bigdata();

    return 0;
}
