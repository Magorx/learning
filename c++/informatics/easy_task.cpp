#include <iostream>
#include <ctype.h>

bool digit_can_be_used(int32_t number) {
    return number <= 5;
}

int main() {
    std::string str;
    getline(std::cin, str);

    bool can_be_used = true;
    char ch = ' ';
    for (unsigned int i = 0; i < str.length() - 1; ++i) {
        if (!can_be_used) {
            break;
        }
        ch = str[i];
        if (isdigit(ch)) {
            can_be_used = digit_can_be_used(ch - '0');
            if (isdigit(str[i + 1]) && ch != '0') {
                can_be_used = false;
            }
        }
    }
    if (can_be_used && isdigit(str.back())) {
        can_be_used = digit_can_be_used(str.back() - '0');
    }

    std::cout << (can_be_used ? "YES\n" : "NO\n");
    
    return 0;
}
