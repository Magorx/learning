#include <iostream>
#include <vector>
#include <string>

template<typename T>
using Row = std::vector<T>;

struct Coords {
    int32_t x = -1;
    int32_t y = -1;
};

Coords DeskCoordsToCoords(const std::string& coord) {
    return {coord[0] - 'a', static_cast<int32_t>(coord[1] - '1')};
}

std::string CoordsToDeskCoords(Coords coords) {
    return char(coords.x + 'a') + itos(coords.y + 1);
}

Coords get_coords

int main() {
    Coords king_coords;
    std::string raw_coords;
    std::cin >>   

    return 0;
}