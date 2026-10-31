#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

const double INF = 1e18;

double distance(pair<int,int> town1, pair<int,int> town2) {
    double x = town1.first  - town2.first;
    double y = town1.second - town2.second;
    return sqrt(x*x + y*y);
}

void floydWarshall(int n, vector<vector<double>>& dist) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

double imperfectivity(int n, const vector<vector<double>>& dist) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            sum += dist[i][j];
    return sum;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int,int>> coords(n);
    for (int i = 0; i < n; i++)
        cin >> coords[i].first >> coords[i].second;

    vector<vector<double>> dist(n, vector<double>(n, INF));
    for (int i = 0; i < n; i++)
        dist[i][i] = 0.0;

    for (int k = 0; k < m; k++) {
        int u, v;
        cin >> u >> v;
        double d = distance(coords[u], coords[v]);
        dist[u][v] = d;
        dist[v][u] = d; 
    }

    floydWarshall(n, dist);

    double resultat = imperfectivity(n, dist);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double road = distance(coords[i], coords[j]);
            double minimum = 0.0;
            for (int a = 0; a < n; a++) {
                for (int b = a + 1; b < n; b++) {
                    double ij = dist[a][i] + road + dist[j][b];
                    double ji = dist[a][j] + road + dist[i][b];
                    minimum += min({dist[a][b], ij, ji});
                }
            }
            resultat = min(resultat, minimum);
        }
    }
    

    cout << fixed << setprecision(4) << resultat << endl;
    //return 0;
}