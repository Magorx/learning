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
    int32_t id;
};

Segment segment(int32_t begin, int32_t end, int32_t id) {
    if (end < begin) {
        std::swap(begin, end);
    }
    Point begin_point = point(begin, BEGIN);
    Point end_point = point(end, END);
    return Segment {begin_point, end_point, id};
}

int32_t MAX_SEGMENT_ID = 0;
std::istream& operator>>(std::istream& input_stream, Segment& random_segment) {
    int32_t begin, end;
    ++MAX_SEGMENT_ID;
    input_stream >> begin >> end;
    if (begin > end) {
        std::swap(begin, end);
    }
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
        std::cout << points[i].type << '\n';
        balance += points[i].type;
        if (balance > 0) {
            sum += points[i].coord - points[i - 1].coord;
        }
    }
    return sum;
}

int32_t PeresechenieSize(std::vector<Point> points, int32_t balance_lvl) {
    int32_t balance = std::max(points[0].type, 0);
    int32_t sum = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        Point point = points[i];
        balance += point.type;
        if (balance > 0 && point.type == END) {
            sum += point.coord - points[i - 1].coord + 1;
        }
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

std::vector<int32_t> Solution(std::vector<Segment> segments) {
    bool taken = false;
    Segment seg_taken = segments[0];
    std::vector<int32_t> ans;
    for (Segment seg : segments) {
        if (seg.begin.coord >= seg_taken.end.coord) {
            taken = false;
        }
        if (!taken) {
            taken = true;
            seg_taken = seg;
            ans.push_back(seg.id);
        } else {
            if (seg.begin.coord >= seg_taken.begin.coord && seg.end.coord < seg_taken.end.coord) {
                seg_taken = seg;
                ans[ans.size() - 1] = seg.id;
            }
        }
    }
    return ans;
}

bool operator<(Segment first, Segment second) {
    if (first.begin < second.begin) {
        return true;
    } else if (first.begin.coord > second.begin.coord) {
        return false;
    } else {
        if (first.end < second.end) {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
    int32_t segment_count = 0;
    std::cin >> segment_count;
    std::vector<Segment> segments = ReadVector<Segment>(segment_count);
    std::vector<Point> points = SegmentsToPoints(segments);
    std::sort(segments.begin(), segments.end());
    // PrintVector(segments);
    // std::cout << '\n';
    // PrintVector(points);
    // std::cout << '\n';
    
    PrintVector(Solution(segments));
    std::cout << '\n';

    return 0;
}   