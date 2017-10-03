#include <iostream>
#include <stack>
#include <string>

bool RightBracketSequence(std::string sequence) {
    std::stack<char> stack;
    for (char symbol : sequence) {
        if (symbol == ')' || symbol == ']' || symbol == '}') {
            if (!stack.empty()) {
                char poped = stack.top();
                stack.pop();
                if ((poped == '(' && symbol == ')') || (poped == '[' && symbol == ']') || (poped == '{' && symbol == '}')) {
                    continue;
                } else {
                    return false;
                    return 0;
                }
            } else {
                return false;
                return 0;
            }
        } else {
            stack.push(symbol);
        }
    }
    if (!stack.empty()) {
        return false;
    } else {
        return true;
    }
}

bool RightBracketSequenceBalance(std::string sequence) {
    int32_t balance = 0;
    for (char symbol : sequence) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            ++balance;
        } else  if (symbol == ')' || symbol == ']' || symbol == '}') {
            --balance;
        }
    }       
    if (balance == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::string string;
    std::getline(std::cin, string);
    std::cout << (RightBracketSequenceBalance(string) ? "YES" : "NO") << '\n';
}