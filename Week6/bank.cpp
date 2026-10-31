#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <math.h>

struct Exchange {
    int from, to;
    double rate;
};

// Your code goes here
// n is the currency
double best_exchange_rate(int n, const std::vector<Exchange>& services) {
    const double INF = std::numeric_limits<double>::max();

    std::vector<double> dist(n, INF);
    dist[0] = 0.0;

    for (int i = 0; i<n - 1; i++){
        bool updated = false;
        for (const auto& s : services){
            if (dist[s.from] < INF){
                double w = dist[s.from] - std::log(s.rate);
                if ( w < dist[s.to]){
                    dist[s.to] = w;
                    updated = true;
                }
            }
        }
        if (!updated){
            break;
        }
    }

    if (dist[n-1] == INF){
        return 0.0;
    }

    std::vector <bool> check (n, false);

    for (int i = 0; i< n-1; i++){
        for (const auto& s : services){
            if (dist[s.from] < INF && dist[s.from] - std::log(s.rate) < dist[s.to]){
                dist[s.to] = dist[s.from] - std::log(s.rate);
                check[s.from] = true;
            }
            if (check[s.from]){
                check[s.to] = true;
            }
        }
        
    }

    if (check[n-1]){
        return INF;
    }
    //return 0.0;
    return std::exp(- dist[n-1]);
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Exchange> services(m);
    for (auto& svc : services) {
        std::cin >> svc.from >> svc.to >> svc.rate;
    }

    double result = best_exchange_rate(n, services);

    if (result == 0.0) {
        std::cout << "Not possible" << std::endl;
    } else if (result == std::numeric_limits<double>::max()) {
        std::cout << "Youhou!" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision(4) << result << std::endl;
    }

    return 0;
}
