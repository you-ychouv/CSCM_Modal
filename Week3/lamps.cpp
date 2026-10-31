#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>
#include <queue>

constexpr char DIM = 4;

uint16_t read_configuration() {
    std::string buf;
    uint16_t c = 0;
    for (size_t j = 0; j < DIM; ++j) {
        std::cin >> buf;
        for (size_t k = 0; k < DIM; ++k) {
            if (buf[k] == '*') {
                c += (1 << (k + DIM * j));
            }
        }
    }
    return c;
}
uint64_t pressing[16];
void lamp(){
    for ( int i=0; i< DIM; i++){
        for (int j = 0; j < DIM; j++){
            int position = i * DIM + j; // lamp number 'pos'

            uint16_t mask = 0;
            uint16_t self_bit = (1 << position); // shift position
            mask = mask | self_bit;

            // UP
            if (i > 0) {
                int up_pos = (i - 1) * DIM + j;
                uint16_t up_bit = (1 << up_pos);
                mask = mask | up_bit;
            }

            // DOWN 
            if (i < DIM - 1) {
                int down_pos = (i + 1) * DIM + j;
                uint16_t down_bit = (1 << down_pos);
                mask = mask | down_bit;
            }

            //LEFT 
            if (j > 0) {
                int left_pos = i * DIM + (j - 1);
                uint16_t left_bit = (1 << left_pos);
                mask = mask | left_bit;
            }

            // RIGHT
            if (j < DIM - 1) {
                int right_pos = i * DIM + (j + 1);
                uint16_t right_bit = (1 << right_pos);
                mask = mask | right_bit;
            }
            pressing[position] = mask;
        }
    }
}

int BFS(uint64_t start, uint64_t target){
    std::vector<int> dist(1 << 16, -1); // -1 = not yet visited
    std::queue<uint16_t> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        uint16_t current = q.front();
        q.pop();

        if (current == target) return dist[current];

        for (int i = 0; i < 16; i++) {
            uint16_t next = current ^ pressing[i];

            if (dist[next] == -1) {
                dist[next] = dist[current] + 1;
                q.push(next);
            }
        }
    }

    return -1;

}



int main() {
    uint16_t source = read_configuration();
    uint16_t target = read_configuration();

    lamp();

    int res = BFS(source, target);

    if (res == -1){
        std::cout << "Not possible." << std::endl;
    }
    else {
        std:: cout<< res;
    }
}
