#include <cstdint>
#include <iostream>


uint64_t exponentiate_modulo(uint64_t a, uint64_t e, uint64_t m) {
    if ( e == 0){
        return 1;
    }
    if (e == 1){
        return a;
    }
    uint64_t res = 1;
    a %= m ;
    // for (uint64_t i = 1; i<= e; i++)
    //     res = (res * a) % m;
    // }
    // return res;

    while(e >= 1) {
        if( e % 2 == 1) {
            res = ((__int128)res * a) % m;
            e--;  
        }
        a = ((__int128)a * a) % m;
        e = e / 2;
    }
    return res;
}

int main() {
    uint64_t a, e, m;
    std::cin >> a >> e >> m;
    std::cout << exponentiate_modulo(a, e, m) << std::endl;
}
