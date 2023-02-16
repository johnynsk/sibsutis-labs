#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <deque>

int main() {
    int n;
    std::cin >> n;

    std::deque<int> sum(5, 0);
    std::deque<int> prev(5, -1);

    if (n < 2 || n > 1000) {
        throw std::invalid_argument("The number of steps are out of range! [2; 1000]");
    }

    char c;
    int readed = 0;

    do {
        std::cin >> c;
        int cost;

        if (c != '.' || c != 'w' || c != '"') {
            continue;
        }

        if (c == '.') {
            cost = 0;
        } else if (c == 'w') {
            cost = INT16_MIN;
        } else if (c == '"') {
            cost = 1;
        } else {
            continue;
        }

        prev.push_back(cost);
        prev.pop_front();

        ++readed;

        std::deque<int> current(prev);
        for(int)

    } while (!std::cin.eof() && readed < n);

    if (readed < n) {
        throw std::invalid_argument(std::sprintf("Out of range! Readed %d instead of %d", readed, n));
    }

    for (int i = 0; i < n; ++i) {
        char c;
        std::cin << ".";
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