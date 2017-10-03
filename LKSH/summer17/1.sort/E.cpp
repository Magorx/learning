#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::string itos(int32_t num) {
    std::string str;
    while (num >= 10) {
        str = str + char(num % 10 - '0');
        num /= 10;
    }
    str = str + char(num % 10 - '0');
    return str;
}

int main() {
    int32_t n;
    int32_t k;
    std::cin >> n >> k;

    std::vector<int32_t> razradi;
    razradi.reserve(10);
    for (char c : itos(n)) {
        std::cout << c;
    }

    std::cout << '\n';

    return 0;
}