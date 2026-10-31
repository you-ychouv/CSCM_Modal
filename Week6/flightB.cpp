#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

long long shortest_duration(int n, int s, int d, vector<int>& change, vector<vector<pair<int,int>>>& adj,vector<int>& parent) {
    vector<long long> dist(n, LLONG_MAX);
    priority_queue< pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;

    dist[s] = 0;
    parent.assign(n, -1);
    pq.push({0, s});

    while (!pq.empty()) {
        auto [dist_u, u] = pq.top();
        pq.pop();

        if (dist_u > dist[u]){
            continue;
        }
        for (auto [v, w] : adj[u]) {

            long long cost = dist_u + w;
            if (v != d) cost += change[v];

            if (cost < dist[v]) {
                dist[v] = cost;
                parent[v] = u;
                pq.push({cost, v});
            }
        }
    }

    return dist[d];
}

int main() {
    int n, m, s, d;
    cin >> n >> m >> s >> d;

    vector<int> change(n);
    for (int i = 0; i < n; i++) cin >> change[i];

    vector<vector<pair<int,int>>> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> parent;

    long long ans = shortest_duration(n, s, d, change, adj, parent);

    if (ans == LLONG_MAX) {
        cout << -1 << "\n\n";
        return 0;
    }

    cout << ans << "\n";
    vector<int> path;
    for (int v = d; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " ";
    }

    cout << "\n";
}