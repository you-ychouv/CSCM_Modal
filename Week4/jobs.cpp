#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

typedef std::vector<uint32_t>::iterator Iter;

uint32_t count_max_jobs(Iter sessions_start, Iter sessions_end, Iter jobs_start, Iter jobs_end) {
    // Your code here
    //sort(jobs_end.begin(), jobs_end.end());
    sort(jobs_start, jobs_end);
    sort(sessions_start, sessions_end);

    //for (uint32_t i = jobs_start.begin(); i != )
    uint32_t count = 0;
    Iter currentJ = jobs_start;
    Iter currentS = sessions_start;

    while (currentJ != jobs_end && currentS != sessions_end){
        if (*currentJ <= *currentS){
            count ++;
            currentJ++;
            currentS++;
        }
        else {
            currentS++;
        }
    }
    return count;
}

int main() {
    size_t num_jobs, num_times;
    std::cin >> num_jobs >> num_times;
    std::vector<uint32_t> jobs(num_jobs, 0);
    std::vector<uint32_t> times(num_times, 0);
    for (size_t i = 0; i < num_jobs; ++i) {
            std::cin >> jobs[i];
    }
    for (size_t i = 0; i < num_times; ++i) {
            std::cin >> times[i];
    }
    std::cout << count_max_jobs(times.begin(), times.end(), jobs.begin(), jobs.end()) << std::endl;
}
