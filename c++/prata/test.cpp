#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct human
{
    string name;
    int hp;
    double luck;
};


int main() {
    using namespace std;
    
    vector<struct human> people(2);
    struct human guy;

    for (unsigned int i = 0; i < people.size(); ++i) {
        cout << "Введите параметры человека номер " << i << '\n';
        string name = "";
        int hp = 0;
        double luck = 0;
        cin >> name;
        cin >> hp;
        cin >> luck;
        cin.get();
        people[i].name = name;
        people[i].hp = hp;
        people[i].luck = luck;
    }    

    for (struct human guy: people) {
        cout << guy.name << ' ' << guy.hp << ' ' << guy.luck << '\n';
    }

    return 0;
}
