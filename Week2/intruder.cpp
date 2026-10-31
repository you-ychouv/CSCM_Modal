#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <random>

 // n = length, m = number of intruders
std::vector <int> generate_random_input(int n, int m){
    std::vector <int> array;
    array.reserve(n);

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution <> dis(1, 1e9);

    for (int i = 0; i < m; i++){
        array.push_back(dis(gen));
    }

    for (int i = 0; i < (n-m); i++){
        int r = dis(gen);
        array.push_back(r);
        array.push_back(r); // for pair
    }
    // shuffle 
    // for (int j = 0; j <n; j++){
    //     std::swap(array[j], array[j+1]);
    // }
    return array;
}

/**
 * @brief Finds the unique element in a vector where all others appear exactly twice,
 *        using sorting.
 *
 * @param nums Vector of integers where every element appears twice except one.
 * @return The unique element.
 */
int find_unique_sort(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i + 1 < (int)nums.size(); i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back(); // unique element is the last one
}

/**
 * @brief Finds the unique element in a vector where all others appear exactly twice,
 *        using XOR.
 *
 * @param nums Vector of integers where every element appears twice except one.
 * @return The unique element.
 */
//unique intruder
int find_unique_xor(const std::vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
        int v = nums[i];
        res = res ^ v;
    }

    return res;
}

/**
 * @brief Finds the smallest of the two unique elements in a vector where all
 *        others appear exactly twice, using sorting.
 *
 * @param nums Vector of integers where every element appears twice except two.
 * @return The smallest of the two unique elements.
 */
int find_smallest_unique_sort(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i + 1 < nums.size(); i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back();
}

/**
 * @brief Finds the smallest of the two unique elements in a vector where all
 *        others appear exactly twice, using XOR.
 *
 * @param nums Vector of integers where every element appears twice except two.
 * @return The smallest of the two unique elements.
 */
int find_smallest_unique_xor(const std::vector<int>& nums) {
    // for (int i = 0; i < nums.size(); i++){
    //     if (nums[i] !=  nums[i+1] && nums[i+1] != nums[i+2]){
    //         return nums[i+1];
    //     }
    // }
    int x = 0;

    for (int i = 0; i < nums.size(); i++) {
        int v = nums[i];
        x = x ^ v;
    }

    int diff = x & (-x);

    int a = 0;
    int b = 0;

    for (int i = 0; i < nums.size(); i++) {
        int v = nums[i];

        if (v & diff)
            a = a ^ v;
        else
            b = b ^ v;
    }

    return std::min(a, b);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res_sort = find_unique_sort(data);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Sorting-based solution. Result: " << res_sort << ". Runtime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microsec" << std::endl;

    begin = std::chrono::steady_clock::now();
    int res_xor = find_unique_xor(data);
    end = std::chrono::steady_clock::now();

    std::cout << "Linear solution. Result: " << res_xor << ". Runtime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microsec" << std::endl;


    return 0;
}
