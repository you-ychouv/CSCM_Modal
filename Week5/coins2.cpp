#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int coin(int m, int N, vector<int> v){
    vector<int> k(N + 1, INT_MAX);
    vector<int> last(N + 1, -1);

    k[0] = 0;

    for (int i = 1; i <= N; i++){
        for (int j = 0; j < m; j++){
            if (v[j] <= i && k[i - v[j]] != INT_MAX){
                if (k[i - v[j]] + 1 < k[i]){
                    k[i] = k[i - v[j]] + 1;
                    last[i] = j; 
                }
            }
        }
    }

    if (k[N] == INT_MAX){
        return -1; 
    }

    vector<int> count(m, 0);
    int cur = N;

    while (cur > 0){
        int j = last[cur];
        count[j]++;
        cur -= v[j];
    }

    for (int i = 0; i < m; i++){
        cout << count[i] << " ";
    }
    cout << endl;

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
    }
}