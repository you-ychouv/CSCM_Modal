ni#include <iostream>
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

uint64_t factorial(int n) {
    if (n == 1 || n == 0){
        return 1;
    }
    else{
        return n * factorial(n - 1);
    }
}

uint64_t count(const int app[26], int m){
    uint64_t res = factorial(m);

    for (int i = 0; i< 26; i++){
        res /= factorial(app[i]);
    }
    return res;
}

bool nth_permutation(const char* s, uint64_t n, char* out) {
    int m = strlen(s);
    int letter[26] = {0};

    for (int i = 0; i < m; i++) // for counting letters
        letter[s[i] - 'A']++;

    uint64_t number = count(letter, m);
    if (n > number){
        return false;
   

    for (int i = 0; i<m; i++){
        for (int j = 0; j <26; j++){
            if (letter[j] == 0){
                continue;
            }
            letter[j] --;
            uint64_t c = count(letter, m-i-1);

            if (n > c){
                n = n -c;
                letter[j]++;
            }else {
                out[i] = 'A' +j ;
                break;
            }
        }


    }
    out[m] = '\0';
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

    for (int i = 0; i < m; i++) // for counting letters
        letter[s[i] - 'A']++;

    uint64_t number = count(letter, m);
    uint64_t rank = 1;

    for (int i = 0; i < m; i++) {

        int curr = s[i] - 'A';

        for (int j = 0; j < curr; j++) {

            if (letter[j] == 0)
                continue;

            letter[j]--;

            rank += count(letter, m - i - 1);

            letter[j]++;
        }

        letter[curr]--;
    }

    return rank;
}

int main() {
    char s[20];
    uint64_t n;

    std::cin >> s;
    std::cin >> n;

    char result[20];
    nth_permutation(s, n, result);
    std::cout << result << std::endl;

    int k = permutation_rank(s);
    std::cout << k << std::endl;

    return 0;
}
