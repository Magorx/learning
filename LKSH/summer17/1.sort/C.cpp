#include <iostream>
#include <vector>
#include <algorithm>

using Row = std::pair<size_t, size_t>;

struct team {
    size_t id;
    size_t tasks_done;
    size_t bad_time;
};

template<typename T>
std::vector<T> ReadVectorOfTeams(size_t length) {
    std::vector<T> objects(length);
    for (size_t i = 0; i < length; ++i) {
        std::cin >> objects[i].tasks_done >> objects[i].bad_time;
        objects[i].id = i + 1;
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

bool TeamComparator(team first, team second) {
    if (first.tasks_done > second.tasks_done) {
        return true;
    } else if (first.tasks_done < second.tasks_done){
        return false;
    } else if (first.bad_time < second.bad_time) {
        return true;
    } if (first.bad_time > second.bad_time) {
        return false;
    }
    else if (first.id < second.id) {
        return true;
    } else {
        return false;
    }
}

int main() {
    size_t team_count = 0;
    std::cin >> team_count;
    std::vector<team> teams = ReadVectorOfTeams<team>(team_count);

    std::sort(teams.begin(), teams.end(), TeamComparator);
    for (team cur_team : teams) {
        std::cout << cur_team.id << ' ';
    }
    std::cout << '\n';

    return 0;
}