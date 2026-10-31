#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdint>

class Sudoku {
    private:
        uint16_t cells[9][9];
    public:
        uint16_t get(int i, int j) const {
            assert((0 <= i) && (i < 9));
            assert((0 <= j) && (j < 9));
            return cells[i][j];
        }
        void unset(int i, int j);
        void set(int i, int j, uint16_t val);
        bool is_complete() const;

        Sudoku& operator = (const Sudoku& other) {
            for (size_t i = 0; i < 9; ++i) {
                for (size_t j = 0; j < 9; ++j) {
                    this->cells[i][j] = other.cells[i][j];
                }
            }
            return *this;
        }

        friend std::istream& operator >> (std::istream& is, Sudoku& s);
};

bool Sudoku::is_complete() const {
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            if (this->cells[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void Sudoku::unset(int i, int j) {
    assert((0 <= i) && (i < 9));
    assert((0 <= j) && (j < 9)); 
    this->cells[i][j] = 0;
}

void Sudoku::set(int i, int j, uint16_t val) {
    assert((0 <= i) && (i < 9));
    assert((0 <= j) && (j < 9)); 
    // this->cells[i][j] = val;
    //check row
    if (this -> cells[i][j] != 0){
        return;
    }
    for (int a = 0 ; a<9; a++){
        if (a != j && this -> cells[i][a] == val){
            return;
        }
    }
    // Check column
    for (int b = 0; b < 9; b++) {
        if (b != i && this->cells[b][j] == val) {
            return;
        }
    }
    int startRow = (i / 3) * 3;
    int startCol = (j / 3) * 3;

    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            if (r == i && c == j) continue; 
            if (this->cells[r][c] == val) {
                return; 
            }
        }
    }
    this->cells[i][j] = val;
}

std::istream& operator >> (std::istream& is, Sudoku& s) {
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            is >> s.cells[i][j];
        }
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Sudoku& s) {
     for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            os << s.get(i, j);
            if (j < 8) {
                os << " ";
            }
        }
        os << std::endl;
    }
    return os;
}
int count = 0;
void solve(Sudoku& s, int& count, Sudoku& solution) {
    if (count >= 2) return;
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         if (s.get(i, j) != 0) continue;
    //         for (int val = 1; val <= 9; val++) {
    //             s.set(i, j, val);
    //             if (s.get(i, j) == val) {
    //                 solve(s, count, solution);
    //             }
    //             s.unset(i, j);
    //         }
    //         return;
    //     }
    // }
    // count++;
    // if (count == 1) solution = s;
    int best_i = -1, best_j = -1;
    int min_choices = 10;

// Find the best cell (MRV)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (s.get(i, j) != 0) continue;

            int choices = 0;
            for (int val = 1; val <= 9; val++) {
                s.set(i, j, val);
                if (s.get(i, j) == val) choices++;
                s.unset(i, j);
        }

            if (choices < min_choices) {
                min_choices = choices;
                best_i = i;
                best_j = j;
        }
    }
}
    if (best_i == -1) {
        count++;
        if (count == 1) solution = s;
        return;
    }

    for (int val = 1; val <= 9; val++) {
        s.set(best_i, best_j, val);
        if (s.get(best_i, best_j) == val) {
            solve(s, count, solution);
        }
        s.unset(best_i, best_j);
    }
}

int main() {
    Sudoku s;
    std::cin >> s;
    int count = 0;
    Sudoku solution;
    solve(s, count, solution);  
    if (count == 0) {
        std::cout << "None\n";
    }
    else if (count == 1) {
        std::cout << solution; // solved grid
    }
    else {
        std::cout << "Multiple\n";
    }
}
