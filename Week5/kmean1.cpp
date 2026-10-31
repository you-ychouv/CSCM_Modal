#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
using namespace std;

vector <long double> prefix_sum,prefix_sum2;
long double variance(int start, int end){

    long double sum = prefix_sum[end] - prefix_sum[start - 1];
    long double square = prefix_sum2[end] - prefix_sum2[start - 1];
    //long double mean = sum / (end - start + 1);

    return square - (sum * sum)/(end - start +1);
}
long double kmean( int k, int n, vector <long double>& v){
    //float c = (accumulate(v.begin(), v.end(), 0))/ v.size();
    // for (int i = 0; i<n; i++){
    //     float l = pow(v[i] - c, 2);
    //     variance.push_back(l);
    // }
    // return *min_element(variance.begin(), variance.end());
    prefix_sum.assign(n+1, 0);
    prefix_sum2.assign(n+1, 0);
    const long double INF = 1e18;
    for (int i = 1; i<=n ; i++){
        prefix_sum[i] = v[i-1] + prefix_sum[i-1];
        prefix_sum2[i] = v[i-1]*v[i-1] + prefix_sum2[i-1];
    }

    vector<vector<long double>> dp(n + 1, vector<long double>(k + 1, INF));

    dp[0][0] = 0;
    //if (k = 0) return 0;
    // if (k= 1) return variance(v.begin(), v.end());
    if (k >=n){
        return 0;
    }

    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            for (int p = 0; p < i; p++) {
                if (dp[p][j-1] == INF) continue;
                dp[i][j] = min(dp[i][j], dp[p][j-1] + variance(p+1, i));
        }
    }
}
    
    return dp[n][k];
    
}


int main (){
    int k,n;
    cin >> k >> n;

    vector <long double> v(n);

    for (int i = 0; i<n; i++){
        cin >> v[i];
    }
    cout << fixed << setprecision(10) <<  kmean(k,n,v);
}