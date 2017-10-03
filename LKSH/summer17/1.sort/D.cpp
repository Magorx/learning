#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


bool StrComparator(std::string first, std::string second) {
    if (first + second > second + first) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::vector<std::string> numbers;
    std::string number;
    while (std::cin >> number) {        
        numbers.push_back(number);
    }

    std::sort(numbers.begin(), numbers.end(), StrComparator);
    for (std::string number : numbers) {
        std::cout << number;
    }
    std::cout << '\n';

    return 0;
}