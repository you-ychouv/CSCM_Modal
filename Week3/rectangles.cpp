#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <climits>
#include <algorithm>

struct Rectangle {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;

    uint32_t area() const {
        return this->w * this->h;
    }
};

std::istream& operator >> (std::istream& is, Rectangle& s) {
    is >> s.w;
    is >> s.h;
    is >> s.x;
    is >> s.y;
    return is;
}

bool overlap(const Rectangle& s1, const Rectangle& s2) {
    if (s1.x + s1.w <= s2.x || s2.x + s2.w <= s1.x)
        return false;

    if (s1.y + s1.h <= s2.y || s2.y + s2.h <= s1.y)
        return false;

    return true;
}
// uint32_t max_area(){

//     for (int i =0; i < 1000; i++){

//     }
// }
std:: vector <Rectangle> v;
std:: vector <bool> used;
uint32_t max_area = 0;
int t;
std::vector <uint32_t> remaining_area;

void backtracking (int i, uint32_t current_area){
    if (current_area + remaining_area[i] <= max_area){
        return;
    }
    if (i == t){
        max_area = std::max(max_area, current_area);
        return;  
    }

    //skip rectangle i
    backtracking(i + 1, current_area);  

    //take rectangle i (if no overlap)
    bool ok = true;
    for (int j = 0; j < i; j++) {
        if (used[j] && overlap(v[i], v[j])) {
            ok = false;
            break;
        }
    }

    if (ok) {
        used[i] = true;
        backtracking(i + 1, current_area + v[i].area());
        used[i] = false;
    }
}


int main() {
    std::cin >> t;

    v.resize(t);
    for (int i = 0; i < t; i++) {
        std::cin >> v[i];
    }
    std::sort(v.begin(), v.end(), [](const Rectangle& a, const Rectangle& b) {
        return a.area() > b.area();
    });
    remaining_area.resize(t + 1, 0);

    for (int i = t - 1; i >= 0; i--) {
        remaining_area[i] = remaining_area[i + 1] + v[i].area();
    }

    used.resize(t, false);

    backtracking(0, 0);

    std::cout << max_area << std::endl;

}    

