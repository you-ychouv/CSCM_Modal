#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdint>
using namespace std;

/* N cases*/
/* V: length of the description. */
// priority queue: highest item first, c-a-d top is the largest number

uint64_t lecture(int n, const vector<uint64_t>& v) {
    priority_queue<uint64_t> pq;
    uint64_t total = 0;

    for (uint64_t i = 0; i <v.size(); i++) {
        pq.push(-v[i]);
        total = total + v[i];
    }

    while (pq.size() > 1) {
        uint64_t a = - pq.top(); 
        pq.pop();
        uint64_t b = - pq.top(); 
        pq.pop();

        uint64_t sum = a + b;
        total += sum;

        pq.push(- sum);
    }
    return total;
}
int main(){
    uint64_t n;
    cin >> n;

    vector <uint64_t> v(n); 
    for (uint64_t i = 0; i<n; i++){
        cin >> v[i];
    }

    cout << lecture(n,v) << endl;

}