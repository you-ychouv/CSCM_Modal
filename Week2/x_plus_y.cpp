#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

/**
 * @brief Finds the largest x+y among all nonnegative solutions of a*x+b*y=c
 *        using the extended Euclidean algorithm.
 *
 * @param a Positive coefficient of x.
 * @param b Positive coefficient of y.
 * @param c Positive right-hand side of the equation.
 * @return The maximum value of x+y, or -1 if no nonnegative solution exists.
 */

int64_t egcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int64_t x1, y1;
    int64_t g = egcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

int64_t maximize_extended_gcd(int64_t a, int64_t b, int64_t c) {
    int64_t x0, y0;
    int64_t g = egcd(a, b, x0, y0);

    if (c % g != 0) {
        return -1;
    }

    x0 *= c / g;
    y0 *= c / g;

    int64_t b1 = b/g;
    int64_t a1 = a/g;

    int64_t best = -1;

    // k??? Find k
    auto lower = [](int64_t a, int64_t b) {
        return a / b - (a % b != 0 && (a ^ b) < 0);
    };
    auto upper = [](int64_t a, int64_t b) {
        return a / b + (a % b != 0 && (a ^ b) > 0);
    };

    int64_t k_min = lower(-x0, b1);
    int64_t k_max = upper(y0, a1);

    if (k_min > k_max){
        return -1;  
    } 
    for (int64_t k : {k_min, k_max}) {
        int64_t x = x0 + b1 * k;
        int64_t y = y0 - a1 * k;
        if (x0 >= 0 && y0 >= 0)
            best = std::max(best, x + y);
    }
    return best;
    // for (int k = -1000000; k <= 1000000; k++) {
    //     int64_t xx = x + k * (b / g);
    //     int64_t yy = y - k * (a / g);

    //     if (xx >= 0 && yy >= 0)
    //         best = std::max(best, xx + yy);
    // }

    //return best;
}

// ─── Brute-force approach ─────────────────────────────────────────────────────

/**
 * @brief Finds the largest x+y among all nonnegative solutions of a*x+b*y=c
 *        via brute-force search.
 *
 * @param a Positive coefficient of x.
 * @param b Positive coefficient of y.
 * @param c Positive right-hand side of the equation.
 * @return The maximum value of x+y, or -1 if no nonnegative solution exists.
 */
int64_t maximize_brute_force(int64_t a, int64_t b, int64_t c) {
    int64_t best = -1;

    if (a < b) {
        for (int64_t x = c / a; x >= 0; --x) {
            if ((c - a * x) % b == 0) {
                return x + (c - a * x) / b;
            }
        }
    } else {
        for (int64_t y = c / b; y >= 0; --y) {
            if ((c - b * y) % a == 0) {
                return y + (c - b * y) / a;
            }
        }
    }

    return -1;
}

int main() {
    int64_t a, b, c;
    std::cin >> a >> b >> c;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res_bf = maximize_brute_force(a, b, c);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Bruteforce search. Result: " << res_bf << ". Runtime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microsec" << std::endl;

    begin = std::chrono::steady_clock::now();
    int res_egcd = maximize_extended_gcd(a, b, c);
    end = std::chrono::steady_clock::now();

    std::cout << "EGCD solution. Result: " << res_egcd << ". Runtime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microsec" << std::endl;

    return 0;
}
