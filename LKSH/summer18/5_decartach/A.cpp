#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Node {
  int x;
  int y;
  int id;
  Node* l;
  Node* r;
  Node* parent;

  Node(int x_, int y_, int id_) {
    x = x_;
    y = y_;
    id = id_;
    l = nullptr;
    r = nullptr;
    parent = nullptr;
  }

  Node() {
    x = 0;
    y = 0;
    l = nullptr;
    r = nullptr;
    parent = nullptr;
  }
};

bool cmp(Node* first, Node* second) {
  if (first->x < second->x) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int n = 0;
  cin >> n;
  vector<Node*> arr;
  vector<pair<long long, long long>> kektor_helper(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    kektor_helper[i].first = x;
    kektor_helper[i].second = i;
    arr.push_back(new Node(x, y, i));
  }

  sort(arr.begin(), arr.end(), cmp);
  sort(kektor_helper.begin(), kektor_helper.end());
  stack<Node*> s;
 
  for (int i = 0; i < n; ++i) {
    Node* cur_node = arr[i];
    Node* last_node = nullptr;
    while (!s.empty() && s.top()->y > cur_node->y) {
      last_node = s.top();
      s.pop();
    }
    if (last_node) {
      if (last_node->parent) {
        last_node->parent->r = cur_node;
        cur_node->parent = last_node->parent;
      }
      cur_node->l = last_node;
      last_node->parent = cur_node;
    } else {
      if (!s.empty()) {
        last_node = s.top();
        cur_node->parent = last_node;
        last_node->r = cur_node;
      }
    }
    s.push(cur_node);
  }
  vector<vector<int>> ans(n);
  cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    Node* cur_node = arr[kektor_helper[i].second];
    int parent = 0;
    int left = 0;
    int right = 0;
    if (cur_node->parent) {
      parent = cur_node->parent->id;
      parent += 1;
    }
    if (cur_node->l) {
      left = cur_node->l->id;
      left += 1;
    }
    if (cur_node->r) {
      right = cur_node->r->id;
      right += 1;
    }
    ans[cur_node->id] = vector<int>({parent, left, right});
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
  }

  return 0;
}