#include <iostream>
#include <vector>
#include <string>

const long long K = 137;
const long long M = (1ll << 31) - 1;
std::vector<long long> K_POWS;

void CALC_K_POWS() {
  long long n = 1;
  for (int i = 0; i < 100000; ++i) {
    K_POWS.push_back(n);
    n = (n % M * K % M) % M;
  }
}

int main() {
  CALC_K_POWS();
  std::string input;
  std::cin >> input;

  std::vector<long long> hashes(input.length() + 1, 0);
  for (int i = input.length() - 1; i >= 0; --i) {
    hashes[i] = (1 + int(input[i] - 'a') + hashes[i + 1] * K % M) % M;
  }

  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    l1--, l2--;
    //std::cout << (hashes[l1] - (hashes[r1] * K_POWS[r1 - l1]) % M + M) % M << ' ' << (hashes[l2] - (hashes[r2] * K_POWS[r2 - l2]) % M + M) % M << '\n';
    if ((hashes[l1] - (hashes[r1] * K_POWS[r1 - l1]) % M + M) % M == (hashes[l2] - (hashes[r2] * K_POWS[r2 - l2]) % M + M) % M) {
      std::cout << '+';
    } else {
      std::cout << '-';
    }
  }

  std::cout << '\n';

  return 0;
}