#include <iostream>
#include <vector>
using namespace std;

int turn(int n, const string& target) {
    const int INF = 1e9;
    if (n == 0) return 0;

    vector<int> next(2, INF), curr(2, INF);

    next[0] = 0;
    next[1] = INF;

    for (int i = n; i >= 1; i--) {
        int t = (target[i - 1] == '1');

        for (int f = 0; f <= 1; f++) {
            int fix = (f != t);

            int stay = next[f];

            int flip = (next[f ^ 1] == INF) ? INF : 1 + next[f ^ 1];

            curr[f] = fix + min(stay, flip);
        }
        next = curr;
    }

    return min(next[0], next[1]);
}

int main() {
    int n;
    cin >> n;
    string target;
    cin >> target;
    cout << turn(n, target) << endl;
}