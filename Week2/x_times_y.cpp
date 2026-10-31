#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

/**
 * @brief Finds the largest x*y among all nonnegative integer solutions of
 *        a*x+b*y=c using the extended Euclidean algorithm.
 *
 * @param a Positive coefficient of x.
 * @param b Positive coefficient of y.
 * @param c Positive right-hand side of the equation.
 * @return The maximum value of x*y, or -1 if no nonnegative solution exists.
 */
int64_t floordiv(int64_t a, int64_t b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);
}

int64_t ceildiv(int64_t a, int64_t b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return (a + b - 1) / b;
    return - ((-a) / b);
}
 int64_t gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int64_t x1, y1;
    int64_t g = gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}
int64_t maximize_product(int64_t a, int64_t b, int64_t c) {
    int64_t x0, y0, x, y;
    int64_t g = gcd(a,b, x0, y0);
    int64_t k;
    if (c % g != 0) return -1;
    x0 *= c/g;
    y0 *= c/g;
    x = x0 + k*b/g;
    y = y0 - k*a/g;

    int64_t k_min = ceildiv(-x0, b/g);
    int64_t k_max = floordiv(y0, a/g);

    if (k_min > k_max) return -1;


    double k_star = (double)(g * (b*y0 - a*x0)) / (2.0 * a * b); // k calculated from equation x*y

    int64_t k1 = (int64_t)k_star;
    int64_t k2 = k1 + 1;

    int64_t best = 0;

    for (int64_t k : {k_min, k_max, k1, k2}) {
        if (k < k_min || k > k_max) continue;

        int64_t x = x0 + k * b/g;
        int64_t y = y0 - k * a/g;

        if (x >= 0 && y >= 0)
            best = std::max(best, x * y);
    }

    return best;
}

int main() {
    int64_t a, b, c;
    std::cin >> a >> b >> c;
    std::cout <<  maximize_product(a, b, c) << std::endl;

    return 0;
}
