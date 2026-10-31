#include <iostream>
#include <vector>
using namespace std;


vector <bool> sieve(int n){
    vector <bool> isMarked(n+1, true);
    for (int i = 2; i*i <= n; i++){
        if (isMarked[i]){
            for (int j = i*i; j<= n; j = j +i){
                isMarked[j] = false;
            }
        }
}
return isMarked;
}

int main(){

    int n, q;
    cin >> n >> q;

    vector <bool> prime = sieve(n);
    int count = 0;
    for ( int i = 2; i<=n; i++){
        if (prime[i]){
            count = count +1;
        }
    }
    cout << count << endl;

    for (int i = 0; i< q; i++){
        int x; 
        cin >> x;
        if (prime[x]){
            cout << 1 << endl;
        }
        else {
            cout << 0 << endl;
        }
    }


    return 0;
}