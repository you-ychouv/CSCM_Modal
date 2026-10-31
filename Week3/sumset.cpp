#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// recursive code, takes as input:
//  @param num_list - the list with all the numbers to consider
//  @param target_k - the number we want (on this step!) to compose
//  @param current_index - the index i such that we only allow take numbers with index >= i
//  @param chosen_elements - vector containing the elements chosen by the preceeding recursive calls
//  @returns true/false depending on whether it is possible to get a subset equal to the target
bool subset_sum_backtrack(const std::vector<int>& num_list,int target_k, int current_index, std::vector<int>& chosen_elements) {
    int current_sum = 0;
    size_t n = num_list.size();

    for (int x : chosen_elements) {
        current_sum += x;
    }

    if (current_sum == target_k) {
        return true;
    }

    //if (current_index == num_list.size()) return false;

    // Maybe extra prunning rules here
    if (current_sum > target_k || current_index == (int)num_list.size()) {
        return false;
    }

    int remaining_sum = 0;
    for (size_t i = current_index; i < num_list.size(); i++) {
        remaining_sum += num_list[i];
    }

    if (current_sum + remaining_sum < target_k) {
        return false;
    }

    if (current_index < (int)num_list.size() &&
        current_sum + num_list[current_index] > target_k) {
        return subset_sum_backtrack(num_list, target_k, current_index + 1, chosen_elements);
    }

    chosen_elements.push_back(num_list[current_index]);

    if (subset_sum_backtrack(num_list, target_k, current_index + 1, chosen_elements)) {
        return true;
    }

    chosen_elements.pop_back();

    if (subset_sum_backtrack(num_list, target_k, current_index + 1, chosen_elements)) {
        return true;
    }

    return false;
}

// wrapper for the recursive call
std::vector<int> find_subset(std::vector<int> num_list, int target_k) {
    // You may want to uncomment this line (why?)
    std::sort(num_list.rbegin(), num_list.rend());

    if (target_k <= 0) {
        return {};
    }
    std::vector<int> chosen_elements;

    if (subset_sum_backtrack(num_list, target_k, 0, chosen_elements)) {
        return chosen_elements;
    }
    
    return {};
}

int main() {
    int n;
    int K;
    std::cin >> n;
    std::cin >> K;
    std::vector<int> v(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    std::vector<int> res = find_subset(v, K);
    std::sort(res.begin(), res.end());
    if (res.size() == 0) {
        std::cout << "None" << std::endl;
    } else {
        for (auto it = res.begin(); it != res.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
