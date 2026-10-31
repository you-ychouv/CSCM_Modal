#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int coin(int m, int N, vector<int> v){
    vector<int> k(N + 1, INT_MAX);
    k[0] = 0;

    for (int i = 1; i <= N; i++){
        for (int j = 0; j < m; j++){
            if (v[j] <= i && k[i - v[j]] != INT_MAX){
                k[i] = min(k[i], k[i - v[j]] + 1);
            }
        }
    }

    if (k[N] == INT_MAX){
        return -1; 
    }
    return k[N];
}

int main(){
    int m, N;
    cin >> m >> N;

    vector<int> v(m);
    for (int i = 0; i < m; i++){
        cin >> v[i];
    }

    int res = coin(m, N, v);

    if (res == -1){
        cout << "Impossible";
    } else {
        cout << res;
    }
}