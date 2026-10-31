#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/* n: number of exercices in the homework. */
/* v: list of exercises with space seperated. */
// vector <int> exo (int n, vector <int> v){
//     sort(v.begin(), v.end());
//     vector <int> l = {0};
//     for (int i = 0; i<n; i++){
//         if (v[i+1] == v[i] + 1){
//             l.push_back(i);
//             v.pop_back(i);
//         }
//     }
//     int m = l.size();
//     for (int j = 0; j<m; j++){
//         cout << l[j] << "-" ;
//     }
//     return  ?;
// }
void exo(int n, vector<int>& v){
    sort(v.begin(), v.end());
    int i = 0;
    while (i < n){
        int start = v[i];
        int j = i;
        while (j + 1 < n && v[j + 1] == v[j] + 1){
            j++;
        }
        int length = j - i + 1;

        if (length >= 3){
            cout << start << "-" << v[j] << " ";
        }
        else if (length == 2){
            cout << v[i] << " " << v[i+1] << " ";
        }
        else{
            cout << v[i] << " ";
        };
        i = j+ 1;
    }
}

int main(){

    int n; 
    cin >> n;
    vector <int> v(n);
    for (int i = 0; i< n; i++){
        cin >> v[i];
    }
    exo(n, v);


    return 0;
}