#include <iostream>
#include <vector>
using namespace std;

int bestBookSize(int n, const vector<int>& pages) {
    int total = 0;
    for (int x : pages) {
        total += x;
    }

    vector<bool> dp(total + 1, false);
    dp[0] = true;

    for (int x : pages) {
        for (int s = total; s >= x; s--) {
            dp[s] = dp[s] || dp[s - x];
        }
    }

    int best = 0;

    for (int s = 0; s <= total; s++) {
        if (dp[s]) {
            int d1 = abs(s - 1000);
            int d2 = abs(best - 1000);

            if (d1 < d2 || (d1 == d2 && s > best)) {
                best = s;
            }
        }
    }

    return best;
}

int main() {
    int n;
    cin >> n;   

    vector<int> pages(n);

    for (int i = 0; i < n; i++) {
        cin >> pages[i];  
    }

    cout << bestBookSize(n, pages) << "\n";
}