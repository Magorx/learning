#include <iostream>
#include <vector>
#include <string>

bool RightBracketSequenceBalance(std::string sequence) {
    int32_t balance = 0;
    for (char symbol : sequence) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            ++balance;
        } else  if (symbol == ')' || symbol == ']' || symbol == '}') {
            --balance;
        }
        if (balance < 0) {
            return false;
        }
    }
    if (balance == 0) {
        return true;
    } else {
        return false;
    }
}

int32_t solution(std::string sequence) {
    int32_t result = 0;
    if (sequence.find('?') >= sequence.length()) {
        if (RightBracketSequenceBalance(sequence)) {
            //std::cout << sequence << '\n';
            result = 1;
        }
    } else {
        auto undefined_symb_index = sequence.find('?');
        sequence[undefined_symb_index] = '(';
        result = solution(sequence);
        sequence[undefined_symb_index] = ')';
        result += solution(sequence);
    }
    return result;
}

int main() {
    std::string string;
    std::getline(std::cin, string);
    std::cout << solution(string) << '\n';  

    return 0;
}