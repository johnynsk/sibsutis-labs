#include <fstream>

using namespace std;

int main() {
    int n, m;
    
    fstream file("knight.in", file.in);
    file >> n >> m;
    file.close();

    int f[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                f[i][j] = 1;
            } else {
                f[i][j] += (i - 2 >= 0 && j - 1 >= 0) ? f[i - 2][j - 1] : 0;
                f[i][j] += (i - 1 >= 0 && j - 2 >= 0) ? f[i - 1][j - 2] : 0;
            }
        }
    }

    file.open("knight.out", file.out);
    file << f[n - 1][m - 1] << endl;
    file.close();

    return 0;
}