#include <iostream>
#include <random>
#include <vector>

int32_t RandInt(int32_t min, int32_t max) {
  if (max < min) {
    return 0;
  }
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int32_t> dist(min, max);
  return dist(mt);
}

template<typename T>
T RandElem(const T& collection) {
  auto size = collection.end() - collection.begin();
  auto elem_position = RandInt(0, size - 1);
  return *(collection.begin() + elem_position);
}

int main() {
  std::cout << RandElem(std::vector<int32_t>{1, 2, 3, 4, 5});
  return 0;
}