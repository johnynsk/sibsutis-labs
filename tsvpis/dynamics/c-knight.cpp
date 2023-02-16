#include <iostream>
#include <stdexcept>
#include <vector>

int n, m;
std::vector<std::vector<int64_t>> map;


int64_t calc(const int n, const int m) {
    std::vector<std::vector<int64_t>> F;
    for (int i = 0; i < n + 3; i++) {
        F.push_back(std::vector<int64_t>(m + 3, 0));
    }

    F[2][2] = 1;
    int startI = 2, startJ = 2;
    while ((startI < n + 1) || (startJ < m + 1)) {
        if (startJ == m + 1) {
            startI++;
        } else {
            startJ++;
        }

        int i = startI, j = startJ;

        while ((i <= n + 1) && j > 2) {
            F[i][j] = F[i + 1][j - 2] + F[i - 1][j - 2] + F[i - 2][j + 1] + F[i - 2][j - 2];
            i++;
            j--;
        }
    }

    return F[n + 1][m + 1];
}

int64_t calc2(int i, int j) {
    if (i >= 0 && j >= 0 && i < n && j < m) {
        if (map[i][j] == -1) {
            map[i][j] = calc(i - 2, j - 1) + calc(i - 2, j + 1) + calc(i - 1, j - 2) + calc(i - 1, j + 2);
        }
    } else {
        return 0;
    }
    return map[i][j];
}

int main() {
    std::cin >> n >> m;
    
    if ((n < 1 || n > 50) || (m < 1 || m > 50)) {
        throw std::invalid_argument("N and M should be in range [1; 50]");
    }

/*
    for (int i = 0; i < n; i++) {
        map.push_back(std::vector<int64_t>(m, -1));
    }
    map[0][0] = 1;
*/

    int64_t paths = calc(n, m);
    // int64_t paths = calc(n - 1, m - 1);
    std::cout << paths << '\n';
}