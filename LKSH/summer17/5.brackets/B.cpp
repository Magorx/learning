#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

std::string get_all(std::stack<char> stack) {
    std::string result;
    int32_t to_get = stack.size();
    for (int32_t i = 0; i < to_get; ++i) {
        result.push_back(stack.top());
        stack.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string string;
    std::getline(std::cin, string);
    std::stack<char> stack;
    for (char symbol : string) {
        if (!stack.empty()) {
            if (symbol == stack.top()) {
                stack.pop();
            } else {
                stack.push(symbol);
            }
        } else {
            stack.push(symbol);
        }
    }
    std::cout << get_all(stack) << '\n';
}