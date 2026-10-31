#include <iostream>
//using namespace std;
#include <numeric>

// Trouver phi(m)
int64_t phi(int64_t m){
    int64_t res = m;
    int p = 2;
    for (int64_t p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            while (m % p == 0) {
                m /= p;
            }
            res -= res / p;
        }
    }
    if (m > 1) {
        res -= res/ m;
    }

    return res;
}
int64_t ExpoFactorial(int64_t n, int64_t m)
{
    if (n == 1) {
        return 1;
    }
    int64_t p = phi(m);
    int64_t exp = ExpoFactorial(n-1, p);
    if (std::gcd(n, m) == 1) {
        return pow(n, exp, m);
    } else {
        return pow(n, exp + p, m);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    cout << (ExpoFactorial(n,m));
  
    return 0;
}
