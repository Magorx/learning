#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

struct Node {
    Node* next;
    Node* prev;
    long long val;
    int size;

    Node() {
        val = 0;
        next = this;
        prev = this;
    }

    Node (long long val_) {
        next = this;
        prev = this;
        val = val_;
    }

    void push_back(long long val_) {
        ++size;
        Node* new_node = new Node(val_);
        new_node->prev = this;
        next->prev = new_node;
        new_node->next = next;
        next = new_node;
    }

    void push_front(long long val_) {
        ++size;
        Node* new_node = new Node(val_);
        new_node->next = this;
        prev->next = new_node;
        new_node->prev = prev;
        prev = new_node;
    }

    void del(long long depth) {
        --size;
        if (depth > 0) {
            prev->del(depth - 1);
        } else {
            next->prev = prev;
            prev->next = next;
        }
    }

    void wipe() {
        next = this;
        prev = this;
    }
};

int main() {
    int n, k, p;
    cin >> n >> k >> p;
    vector<Node*> arr(k, new Node(0));
    vector<int> sizes(k, 0);
    int max_size = 0;
    int cur_size = 0;
    for (int i = 0; i < n; ++i) {
        char c;
        int num, oil;
        cin >> c >> num >> oil;
        num--;
        if (c == '+') {
            arr[num]->push_front(oil);
            sizes[num] += 1;
            ++cur_size;
            max_size = max(max_size, cur_size);
            if (cur_size > p) {
                cout << "Error\n";
                return 0;
            }
        } else {
            if (sizes[num]) {
                int val = arr[num]->prev->val;
                arr[num]->del(1);
                --cur_size;
                sizes[num] -= 1;
                if (val != oil) {
                    cout << "Error\n";
                    return 0;
                }
            } else {
                cout << "Error\n";
                return 0;
            }
        }
    }
    if (cur_size > 0) {
        cout << "Error\n";
        return 0;
    }
    cout << max_size << '\n';

    return 0;
}