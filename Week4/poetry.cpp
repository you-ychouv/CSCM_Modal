#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

uint64_t max_profit(int n, int m, vector<int>& length, vector<pair<int,int>>& journal) {

    sort(length.rbegin(), length.rend());

    sort(journal.begin(), journal.end(), [](pair<int,int> a, pair<int,int> b) {
        return a.second > b.second;
    });

    uint64_t profit = 0;
    int i = 0;
    for (int j = 0; j < m && i < n; j++) {
        int count = journal[j].first;
        int price = journal[j].second;

        while (count > 0 && i < n) {
            profit += (uint64_t)length[i] * price;
            i++;
            count--;
        }
    }

    return profit;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> l(n);
    vector<pair<int,int>> j;

    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }

    for (int i = 0; i < m; i++) {
        int first, second;
        cin >> first >> second;
        j.push_back({first, second});
    }

    cout << max_profit(n, m, l, j) << endl;
}