#include <iostream>
#include <vector>
#include <random>

template<typename T>
void PrintCollection(const T& collection, std::string separator=" ", std::string end="") {
  if (!(collection.end() - collection.begin()))
    return;

  for (auto i = collection.begin(); i != collection.end() - 1; ++i) {
    std::cout << *i << separator;
  }
  std::cout << *(collection.end() - 1) << end;
}

int32_t RandInt(int32_t min, int32_t max) {
  if (max < min) {
    return 0;
  }
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int32_t> dist(min, max);
  return dist(mt);
}

int main() {
  for (int32_t i = 0; i < 10; ++i) {
    std::cout << RandInt(0, 9) << ' ';
  }
  std::cout << '\n';
  return 0;
}