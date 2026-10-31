#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <iomanip>
using namespace std;

// look for a smallest total length = MST

// double distance(double c1, double c2){
//     double d_sqrt 
// }

long double euclidean_dist(pair<double,double> c1, pair<double, double> c2){
    return sqrtl(pow(c1.first - c2.first, 2) + pow(c1.second - c2.second, 2));
}
long double smallest_len (int n, vector <pair<double, double>>& coords){

    vector <long double> small_dist(n, 1e18);
    small_dist[0] = 0;

    vector<bool> visited(n, false);

    long double total = 0;

    for (int i = 0; i < n; i++) {
        int u = -1; // u here is the index of the island 
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || small_dist[j] < small_dist[u])) {
                u = j;
            }
        }

        visited[u] = true;
        total += small_dist[u];

        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                long double d = euclidean_dist(coords[u], coords[v]);
                if (d < small_dist[v]) {
                    small_dist[v] = d;
                }
            }
        }
    }
    //return 0;
    return total;

}

int main() {
    int n;
    cin >> n;

    vector <pair<double, double>> coords(n);

    for (int i = 0; i < n; i++) {
        cin >> coords[i].first >> coords[i].second;
    }

    long double result = smallest_len(n, coords);

    cout << fixed << setprecision(4) << result << endl;

    return 0;
}