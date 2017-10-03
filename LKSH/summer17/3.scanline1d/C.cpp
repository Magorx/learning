#include <iostream>
#include <vector>
#include <algorithm>

const int32_t BEGIN = 1;
const int32_t END = -1;
std::vector<int32_t> RESULT;

template<typename T>
using Row = std::vector<T>;

struct Point{
    int32_t coord, type, id;
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

Point point(const int32_t coord, const int32_t type, int32_t id) {
    return Point {coord, type, id};
}

std::ostream& operator<<(std::ostream& output_stream, const Point& point) {
    output_stream << '<' << "Point " << point.coord << '|' << point.type << '>';
    return output_stream;
}

struct Segment{
    Point begin;
    Point end;
    int32_t id;
};

Segment segment(int32_t begin, int32_t end, int32_t id) {
    if (end < begin) {
        std::swap(begin, end);
    }
    Point begin_point = point(begin, BEGIN, id);
    Point end_point = point(end, END, id);
    return Segment {begin_point, end_point, id};
}

int32_t MAX_SEGMENT_ID = 0;
std::istream& operator>>(std::istream& input_stream, Segment& random_segment) {
    int32_t begin, end;
    input_stream >> begin >> end;
    if (begin > end) {
        std::swap(begin, end);
    }
    ++MAX_SEGMENT_ID;
    random_segment = segment(begin, end, MAX_SEGMENT_ID);
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

int32_t UnionSize(std::vector<Point> points) {
    int32_t balance = std::max(points[0].type, 0);
    int32_t sum = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        balance += points[i].type;
        if (balance > 0) {
            sum += points[i].coord - points[i - 1].coord;
        }
    }
    return sum;
}

int32_t IntersectionSize(std::vector<Point> points) {
    int32_t balance = std::max(points[0].type, 0);
    for (size_t i = 1; i < points.size(); ++i) {
        Point point = points[i];
        balance += point.type;
        if (balance > 0 && point.type == END) {
            RESULT[points[i - 1].id] = balance + 1;
        }
    }
    return 0;
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
    int32_t segment_count = 0;
    std::cin >> segment_count;
    RESULT.resize(segment_count);
    std::vector<Segment> segments = ReadVector<Segment>(segment_count);
    
    std::vector<Point> points = SegmentsToPoints(segments);
    std::sort(points.begin(), points.end());
    // PrintVector(segments);
    // std::cout << '\n';
    // PrintVector(points);
    // std::cout << '\n';
    IntersectionSize(points);
    PrintVector(RESULT);

    return 0;
}