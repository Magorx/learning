#include <iostream>
#include <vector>
#include <algorithm>

const int32_t BEGIN = 1;
const int32_t NEUTRAL = 0;
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

Point point(const int32_t coord, const int32_t type) {
    return Point {coord, type};
}

int32_t MAX_POINT_ID = -1;
std::istream& operator>>(std::istream& input_stream, Point& random_point) {
    ++MAX_POINT_ID;
    int32_t type = NEUTRAL;
    int32_t id = MAX_POINT_ID;
    int32_t coord;
    input_stream >> coord;
    random_point = Point {coord, type, id};
    return input_stream;
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
    int32_t a1, b1, c1, a2, b2, c2;
    input_stream >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    int32_t begin = a1 * 60 * 60 + b1 * 60 + c1;
    int32_t end = a2 * 60 * 60 + b2 * 60 + c2;
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

int32_t IntersectionSize(std::vector<Point> points, int32_t balance_lvl) {
    int32_t balance = std::max(points[0].type, 0);
    int32_t sum = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        Point point = points[i];
        if (balance >= balance_lvl && point.type == END) {
            sum += point.coord - points[i - 1].coord;
        }
        balance += point.type;
        // std::cout << i << ") " << balance << ' ' << point <<'\n';
    }
    return sum;
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

template<typename T>
std::vector<T> ConcatinateVector(std::vector<T> first, std::vector<T> second) {
    std::vector<T> result = first;
    for (T elem : second) {
        result.push_back(elem);
    }
    return result;
}

int main() {
    int32_t segment_count = 0;
    std::cin >> segment_count;
    int32_t removed_segment_cout = 0;
    std::vector<Segment> segments;
    segments.reserve(segment_count);
    for (int32_t i = 0; i < segment_count; ++i) {
        int32_t a1, b1, c1, a2, b2, c2;
        std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
        int32_t begin = a1 * 60 * 60 + b1 * 60 + c1;
        int32_t end = a2 * 60 * 60 + b2 * 60 + c2;
        if (begin == end) {
            segments.push_back(Segment {Point {0, BEGIN}, Point {24 * 60 * 60, END}});
        } else if (begin > end) {
            segments.push_back(Segment {Point {begin, BEGIN}, Point {24 * 60 * 60, END}});
            segments.push_back(Segment {Point {0, BEGIN}, Point {end, END}});
        } else {
            segments.push_back(Segment {Point {begin, BEGIN}, Point{end, END}});
        }
    }
    segment_count -= removed_segment_cout;
    std::vector<Point> points = SegmentsToPoints(segments);
    std::sort(points.begin(), points.end());

    // PrintVector(segments);
    // std::cout << '\n';
    // PrintVector(points);
    // std::cout << '\n' << segment_count << '\n';
    std::cout << IntersectionSize(points, segment_count) << '\n';

    return 0;
}