#include <iostream>
#include <vector>

void solution(int32_t cockroach_count, const std::vector<std::pair<int32_t, int32_t>>& bets,
              int32_t last_solved_bet_index, std::vector<int32_t>* cockroach_before) {
  ++last_solved_bet_index;
  if (bets.size() == last_solved_bet_index + 1) {
    return;
  }
  auto bet = bets[last_solved_bet_index];
  if (!cockroach_before->at(bet.first)) {
    cockroach_before->at(bet.first) = true
  }
}

int main() {
  int32_t cockroach_count = 0, people_count = 0;
  std::cin >> cockroach_count >> people_count;

}