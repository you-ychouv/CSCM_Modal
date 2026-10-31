#include <iostream>
#include <numeric>
// We assume that the input array of duration is already in order respecting the order of the eps 
uint64_t min_daily_limit(const uint64_t* duration, int n, int k) {
    uint64_t lower = *std::max_element(duration, duration + n);
    uint64_t upper = std::accumulate(duration, duration + n, uint64_t(0));

    while (lower < upper){
        uint64_t mid = (lower + upper)/2;

        int day = 1;
        uint64_t today_dur = 0;
        for (int i = 0; i< n; i++){
            if (today_dur + duration[i] <= mid){
                today_dur = today_dur + duration[i];
            }
            else{
                day = day + 1;
                today_dur = duration[i];
            }
        }
        if (day <= k){
            upper = mid;

        }
        else{
            lower = mid +1;
        }
    }

    return lower;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    uint64_t* duration = new uint64_t[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> duration[i];
    }
    
    uint64_t result = min_daily_limit(duration, n, k);
    std::cout << result << std::endl;

    return 0;
}
