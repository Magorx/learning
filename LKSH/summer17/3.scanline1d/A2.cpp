#include <iostream>
#include <vector>
#include <algorithm>

const int32_t BEGIN = 1;
const int32_t END = -1;

template<typename T>
using Row = std::vector<T>;

struct Point{
    int32_t coord, type;
};

bool operator<(Point first, Point second) {
    if (first.coord < second.coord) {
        return true;
    } else if (first.coord > second.coord) {
        return false;
    } else {
        if (first.type > second.type) {
            return true;
        } else {
            return false;
        }
    }
}

Point point(const int32_t coord, const int32_t type) {
    return Point {coord, type};
}

std::ostream& operator<<(std::ostream& output_stream, const Point& point) {
    output_stream << '<' << "Point " << point.coord << '|' << point.type << '>';
    return output_stream;
}

struct Segment{
    Point begin;
    Point end;
};

Segment segment(int32_t begin, int32_t end) {
    if (end < begin) {
        std::swap(begin, end);
    }
    Point begin_point = point(begin, BEGIN);
    Point end_point = point(end, END);
    return Segment {begin_point, end_point};
}

std::istream& operator>>(std::istream& input_stream, Segment& random_segment) {
    int32_t begin, end;
    input_stream >> begin >> end;
    if (begin > end) {
        std::swap(begin, end);
    }
    random_segment = segment(begin, end);
    return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, Segment segment) {
    output_stream << '<' << "Segment " << segment.begin.coord << '-' << segment.end.coord << '>';
    return output_stream;
}

template<typename T>
std::vector<T> ReadVector(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

std::vector<Point> SegmentsToPoints(const std::vector<Segment> segments) {
    std::vector<Point> points;
    for (size_t i = 0; i < segments.size(); ++i) {
        points.push_back(segments[i].begin);
        points.push_back(segments[i].end);
    }

    return points;
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

std::istream& operator>>(std::istream& input_stream, std::pair<int32_t, int32_t>& pair) {
    int32_t begin, end;
    std::cin >> begin >> end;
    if (begin > end) {
        std::swap(begin, end);
    }
    pair = std::pair<int32_t, int32_t> {being, end};
    return input_stream;
}

int main() {
    int32_t segment_count = 2;
    std::vector<std::pair<int32_t, int32_t>> segments = ReadVector<std::pair<int32_t, int32_t>>(segment_count);
    std::sort(segments.begin(), segment.end());
    if (points[0][0] < points[1][0] && points[1][1] < points[0][1]) {
        std::cour << points[1][1] - points[1][0] << '\n';
    } else {
        std::cout << points[]
    }
    return 0;
}