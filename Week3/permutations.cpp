#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdint>

/**
 * @brief Finds the n-th (1-indexed) lexicographic permutation of a C-string.
 *
 * @param s   The input C-string (consisting of upper-case letters).
 * @param n   The 1-based index of the desired permutation.
 * @param out Output buffer for the result (must be at least strlen(s)+1 bytes).
 * @return true on success, false if n is out of range.
 */
uint64_t factorial(int n){
    if (n == 0 || n==1){
        return 1;
    }
    else{
        return n*factorial(n-1);
    }
}
uint64_t probab (const int app[26], int m){
    uint64_t res = factorial(m);

    for (int i = 0; i < 26; i++){
        res = res /factorial(app[i]);
    }
    return res;
}
bool nth_permutation(const char* s, uint64_t n, char* out) {
    int m = strlen(s);
    int letter[26] = {0};

    for (int i = 0; i<m; i++){
        letter[s[i] - 'A'] ++;
    }
    uint64_t number = probab(letter, m);

    if (n > number){
        return false;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < 26; j++){ //A = 0, ..., Z = 25
            if (letter[j] == 0){
                continue;
            }
            letter[j]--;
            uint64_t c = probab(letter, m - i -1);

            if (n > c){
                n = n - c;
                letter[j] ++;
            }
            else{
                out[i] = 'A' + j;
                break;
            }

        }
    }
    return true;
}

/**
 * @brief Computes the 1-based lexicographic rank of a given permutation.
 *
 * @param s The input C-string representing the permutation (upper-case letters).
 * @return  The 1-based rank of the permutation, or -1 if the string is empty.
 */
int64_t permutation_rank(const char* s) {
    int m = strlen(s);
    int letter[26] = {0};
    // counting letter (if there is any duplicated)
    for (int i = 0; i< m; i++){
        letter[s[i] - 'A'] ++;
    }
    uint64_t number = probab(letter, m);
    uint64_t rank = 1;

    for (int i = 0; i < m; i++) {

        int curr = s[i] - 'A';

        for (int j = 0; j < curr; j++) {

            if (letter[j] == 0)
                continue;

            letter[j]--;

            rank += probab(letter, m - i - 1);

            letter[j]++;
        }

        letter[curr]--;
    }

    return rank;

    return -1;
}

int main() {
    char s[20];
    uint64_t n;

    std::cin >> s;
    std::cin >> n;

    char result[20];
    nth_permutation(s, n, result);
    std::cout << result << std::endl;

    return 0;
}
