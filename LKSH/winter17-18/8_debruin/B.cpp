#include <iostream>
#include <vector>
#include <string>

const int ERR_MAX_PERMUTATION_REACHED = -1;

class Permutator {
private:
  std::vector<char> elements;
  std::vector<int> current_permutation;
  int elements_count;
  int permutation_length;
  bool to_print_while_calculating;
public:
  Permutator(std::vector<char> _elements, int _permutation_length, bool _to_print_while_calculating) {
    elements = _elements;
    permutation_length = _permutation_length;
    to_print_while_calculating = _to_print_while_calculating;
    elements_count = _elements.size();
    reset_current_permutation();
  }

  void reset_current_permutation() {
    current_permutation = std::vector<int>(permutation_length, 0);
  }

  std::string get_current_permutation() {
    std::string permutation;
    for (int i = 0; i < permutation_length; ++i) {
      permutation += elements[current_permutation[i]];
    }
    return permutation;
  }

  void store_current_permutation(std::string file) {
    return;
  }

  int generate_next_permutation() {
    for (int increasing_element_position = permutation_length - 1; increasing_element_position >= 0; --increasing_element_position) {
      if (current_permutation[increasing_element_position] != elements_count - 1) {
        current_permutation[increasing_element_position] += 1;
        for (int nullifieing_element_position = increasing_element_position + 1; nullifieing_element_position < permutation_length; ++nullifieing_element_position) {
          current_permutation[nullifieing_element_position] = 0;
        }
        return 0;
      }
    }
    return ERR_MAX_PERMUTATION_REACHED;
  }

  std::vector<std::string> calculate_all_permutations() {
    reset_current_permutation();
    std::vector<std::string> result;
    result.push_back(get_current_permutation());
    while (!generate_next_permutation()) {
      result.push_back(get_current_permutation());
    }
    return result;
  } 

};

int main() {
  
}