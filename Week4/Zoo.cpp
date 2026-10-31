#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* S: number of suricats*/
/* C: track's capacity */
/* K: difference between temperament*/

int transport(int s, int c, int k, vector<int> temp){

    sort(temp.begin(), temp.end());
    if (s == 0){
        return 0;
    }
    int count = 1;
    int current_capacity = 1;
    int start_temp = temp[0];

    for (int i = 1; i<s; i++){
        if (current_capacity < c && (temp[i] - start_temp) <= k) {
            current_capacity++;
        } else {
            count++;
            current_capacity = 1;
            start_temp = temp[i]; 
        }
    }
    return count ;
}
int main (){

    int s,c,k;
    cin >> s >> c >> k;
    vector <int> v(s);
    for (int i = 0; i < s; i++){
        cin >> v[i];
    }
    
    cout << transport(s,c,k,v) << endl;

}