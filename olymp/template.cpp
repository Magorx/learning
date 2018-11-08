#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>

template<typename T>
using Row = std::vector<T>;

struct Coords {
  int32_t x = 0;
  int32_t y = 0;
  bool exists = true;
}

std::ostream& operator<<(std::ostream& output_stream, const Coords& coords) {
  output_stream << coords.x + 1 << ' ' << coords.y + 1;
  return output_stream;
}

std::istream& operator>>(std::istream& input_stream, Coords& coords) {
  input_stream >> coords.x >> coords.y;
  return input_stream;
}

std::vector<std::string> split(std::string string, char delimiter) {
    std::vector<std::string> array;

    std::string buffer = "";
    for (char ch: string) {
        if (ch == delimiter) {
            array.push_back(buffer);
            buffer = "";
        } else {
            buffer += ch;
        }
    }
    array.push_back(buffer);

    return array;
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

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

template<typename T>
std::vector<Row<T>> ReadMatrix(size_t row_count, size_t column_count) {
    std::vector<Row<T>> matrix;
    matrix.reserve(row_count);
    for (size_t i = 0; i < row_count; ++i) {
        matrix.push_back(ReadVector<T>(column_count));
    }
    return matrix;
}

template<typename T>
void PrintCollection(const T& collection, std::string separator=" ", std::string end="") {
  if (!(collection.end() - collection.begin()))
    return;

  for (auto i = collection.begin(); i != collection.end() - 1; ++i) {
    std::cout << *i << separator;
  }
  std::cout << *(collection.end() - 1) << end;
}

template<typename T>
void PrintMatrix(std::vector<Row<T>> matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << '\n';
    }
}

template<typename T>
Coords FindInMatrix(const std::vector<Row<T>> maxtrix, const T& to_find) {
  for (size_t x = 0; x < matrix.size(); ++x) {
    for (size_t y = 0; y < maxtrix[x].size(); ++y) {
      if (matrix[x][y] == to_find) {
        return {x, y};
      }
    }
  }

  return {-1, -1, false};
}

int main() {
    
    std::cout << '\n';
    return 0;
}
