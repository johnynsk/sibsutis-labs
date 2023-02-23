#include <fstream>

using namespace std;
 
int main() {
    char a[1005];
    int p[1005], n;
    
    fstream file("lepus.in", file.in);
    file >> n;
    for (int i = 1; i <= n; i++) {
        file >> a[i];
    }
    file.close();

    p[1] = 0;

    for (int i = 2; i <= n; i++) {
        int max_ = INT32_MIN;
        
        if (i - 1 >= 1 && a[i - 1] != 'w') {
            max_ = max(max_, p[i - 1]);
        }

        if (i - 3 >= 1 && a[i - 3] != 'w') {
            max_ = max(max_, p[i - 3]);
        }
        
        if (i - 5 >= 1 && a[i - 5] != 'w') {
            max_ = max(max_, p[i - 5]);
        }
        
        p[i] = max_;
        
        if (a[i] == '"') {
            p[i] ++;
        }
    }

    file.open("lepus.out", file.out);
    file << (p[n] < 0 ? -1 : p[n]) << endl;
    file.close();

    return 0;
}