#include <iostream>
#include <cstdint>

#include <vector>
#include <cstring>

std::vector<std::string> split(std::string string, char splitting_symb) {
    std::vector<std::string> array;

    std::string buffer = "";
    for (char ch: string) {
        if (ch == splitting_symb) {
            array.push_back(buffer);
            buffer = "";
        } else {
            buffer += ch;
        }
    }
    array.push_back(buffer);

    return array;
}

int main() {
    
    std::cout << '\n';
    return 0;
}
