#include <algorithm>
#include <iostream>
#include <stdexcept>

int main() {
    int n;
    std::cin >> n;
    
    int s1 = 0; // best sum N-1 step
    int s2 = 0; // best sum N-2 step
    int c1 = INT16_MAX; // value on N-1 step
    int c2 = INT16_MAX; // value on N-2 step

    if (n < 1 || n > 100) {
        throw std::invalid_argument("The number of stair's steps are out of range! [1; 100]");
    }

    for (int i = 0; i < n; ++i) {
        int c; // value on N step
        std::cin >> c;
        
        if (c < -10000 || c > 10000) {
            throw std::invalid_argument("The value is out of range! [-10000; 10000]");
        }

        // BEST sum on N step
        const int s0 = c + std::max(s1, s2);

        // forget about N-2 step
        s2 = s1;
        s1 = s0;
        c2 = c1;
        c1 = c;
    }

    std::cout << s1 << '\n';
}