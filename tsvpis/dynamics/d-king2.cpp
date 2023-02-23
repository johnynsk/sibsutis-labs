#include <fstream>
#include <iostream>
#include <array>
#include <list>
#include <algorithm>
#define n 8
using namespace std;

int main() {
    array<array<int, 8>, 8> a, f;

    fstream file("king2.in", file.in);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
            f[i][j] = 0;
        }
    }
    file.close();
    reverse(begin(a), end(a));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            list<int> c;
            if (i - 1 >= 0) {
                c.push_back(f[i - 1][j]);
            }
            if (j - 1 >= 0) {
                c.push_back(f[i][j - 1]);
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                c.push_back(f[i - 1][j - 1]);
            }
            if (c.size() > 0) {
                c.sort();
                f[i][j] = *c.begin() + a[i][j];
            } else {
                f[i][j] = a[i][j];
            }
        }
    }

    file.open("king2.out", file.out);
    file << f[n - 1][n - 1] << endl;
    file.close();

    return 0;
}