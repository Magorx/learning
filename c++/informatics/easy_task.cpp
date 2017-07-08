#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    int left = 0, right = 0;
    cin >> left;
    cin.get();
    cin >> right;
    if (left % 2) {
        ++left;
    }

    for (int i = left; i <= right; i += 2) {
        cout << i << ' ';
    }
    
    return 0;
}
