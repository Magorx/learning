#include <iostream>
#include <vector>
#include <algorithm>

const int32_t BEGIN = 1;
const int32_t NEUTRAL = 0;
const int32_t END = -1;

template<typename T>
using Row = std::vector<T>;

struct Point{
    int32_t x, y, type, id;
    std::pair<int32_t, int32_t> coords;
};

bool operator<(Point first, Point second) {
    if (first.coords < second.coords) {
        return true;
    } else if (first.coords > second.coords) {
        return false;
    } else {
        if (first.type > second.type) {
            return true;
        } else {
            return false;
        }
    }
}

Point point(const int32_t x, int32_t y, const int32_t type, int32_t id) {
    return Point {x, y, type, id, std::make_pair(x, y)};
}

std::ostream& operator<<(std::ostream& output_stream, const Point& point) {
    output_stream << '<' << "Point " << point.x << ' ' << point.y << '|' << point.type << '>';
    return output_stream;
}

struct Rectangle{
    Point downleft, upright;
    int32_t id;
};

Rectangle rectangle(int32_t x_downleft, int32_t y_downleft, int32_t x_upright, int32_t y_upright, int32_t id) {
    Point downleft = point(x_downleft, y_downleft, BEGIN, id);
    Point upright = point(x_upright, y_upright, END, id);
    return Rectangle {downleft, upright, id};
}

int32_t MAX_RECTANGLE_ID = 0;
std::istream& operator>>(std::istream& input_stream, Rectangle& random_rectangle) {
    int32_t x_downleft, y_downleft, x_upright, y_upright;
    input_stream >> x_downleft >> y_downleft >> x_upright >> y_upright;
    ++MAX_RECTANGLE_ID;
    random_rectangle = rectangle(x_downleft, y_downleft, x_upright, y_upright, MAX_RECTANGLE_ID);
    return input_stream;
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
void PrintVector(std::vector<T> random_vector) {
    for (size_t i = 0; i < random_vector.size(); ++i) {
        std::cout << random_vector[i];
        if (i < random_vector.size() - 1) {
            std::cout << ' ';
        }
    }
}

int main() {
    int32_t rectangles_count = 0;
    std::cin >> rectangles_count;
    std::vector<Rectangle> rectangles = ReadVector<Rectangle>(rectangles_count);

    int32_t x_downleft = 1e-9;
    int32_t y_downleft = 1e-9;
    int32_t x_upright = 1e9;
    int32_t y_upright = 1e9;

    for (Rectangle rect : rectangles) {
        if (x_downleft > rect.upright.x ||  x_upright < rect.downleft.x || y_downleft > rect.upright.y || y_upright < rect.downleft.y) {
            std::cout << -1 << '\n';
            return 0;
        }
        x_downleft = std::max(x_downleft, rect.downleft.x);
        y_downleft = std::max(y_downleft, rect.downleft.y);
        x_upright = std::min(x_upright, rect.upright.x);
        y_upright = std::min(y_upright, rect.upright.y);
    }
    std::cout << x_downleft << ' ' << y_downleft << ' ' << x_upright << ' ' << y_upright << '\n';

    return 0;
}