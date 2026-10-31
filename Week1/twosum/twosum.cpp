#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

// ─── Search functions ────────────────────────────────────────────────────────

/**
 * @brief  Find an index i such that there exists j >= i with
 *         arr[i] + arr[j] == target, using a naive quadratic scan.
 * @param  arr     Pointer to a C-style array sorted in strictly ascending order.
 * @param  n       Number of elements in arr; must be >= 0.
 * @param  target  The desired sum.
 * @return An index i for which a valid j exists, or -1 if no such pair exists.
 */
int two_sum_quadratic(const int* arr, int n, int target) {
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
            if (arr[i] + arr[j] == target) return i;
            if (arr[i] + arr[j] >  target) break;
        }
    return -1;
}

/**
 * @brief  Find an index i such that there exists j >= i with
 *         arr[i] + arr[j] == target, with complexity O(n log n).
 *
 * @param  arr     Pointer to a C-style array sorted in strictly ascending order.
 * @param  n       Number of elements in arr; must be >= 0.
 * @param  target  The desired sum.
 * @return An index i for which a valid j exists, or -1 if no such pair exists.
 */

int two_sum_loglinear(const int* arr, int n, int target) {    
    for (int i = 0; i < n; i++) {
        int c = target - arr[i];

        auto binary = std::lower_bound(arr + i, arr + n, c);

        if (binary != arr + n && *binary == c)
            return i;   
    }
    return -1;
}

/**
 * @brief  Find an index i such that there exists j >= i with
 *         arr[i] + arr[j] == target, in linear time.
 *
 * @param  arr     Pointer to a C-style array sorted in strictly ascending order.
 * @param  n       Number of elements in arr; must be >= 0.
 * @param  target  The desired sum.
 * @return An index i for which a valid j exists, or -1 if no such pair exists.
 */
int two_sum_linear(const int* arr, int n, int target) {
    int i = 0, j = n - 1;
    while (i < j) {
        int s = arr[i] + arr[j];
        if (s == target){
            return i;}
        if (s < target){
            ++i;
        }  
        else{
            --j;
        }             
    }
    return -1;
}

int main() {
    int n, target;
    std::cin >> n >> target;
    int* arr = new int[n]; // to allocate n numbers 

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }


    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    int res1 = two_sum_quadratic(arr, n, target);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    int res2 = two_sum_loglinear(arr, n, target);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
    int res3 = two_sum_linear(arr, n, target);
    std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();

    

    std::cout << "Answer is " << res1 << std::endl;
    std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[microsec]" << std::endl;
    std::cout << "The answer from binary search is " << res2 << std::endl;
    std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[microsec]" << std::endl;
    std::cout << "The answer (linear) " << res3 << std::endl;
    std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << "[microsec]" << std::endl;

    // const int random_value = std::rand();

    delete[] arr;
}
