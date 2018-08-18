#include <bits/stdc++.h>

using namespace std;

struct Node;
int size(Node* n);
int node_min(Node* n);
int inf = 10000000;

struct Node{ 
  int value;
  int y;
  int s;
  Node* L;
  Node* R;

  Node(int value_) {
    value = value_;
    y = rand();
    s = 1;
    L = nullptr;
    R = nullptr;
  }

  void push() {}

  void update() {
    s = size(L) + size(R) + 1;
  }
};

int size(Node* n) {
  if (!n) {
    return 0;
  } else {
    return n->s;
  }
}

Node* merge(Node* L, Node* R) {
  if (!L) {
    return R;
  }
  if (!R) {
    return L;
  }

  if (L->y > R->y) {
    L->push();
    L->R = merge(L->R, R);
    L->update();
    return L;
  } else {
    R->push();
    R->L = merge(L, R->L);
    R->update();
    return R;
  }
}

pair<Node*, Node*> split(Node* n, int k) {
  if (!n) {
    return {nullptr, nullptr};
  }

  int l_size = size(n->L);
  if (l_size >= k) {
    n->push();
    auto ret = split(n->L, k);
    n->L = ret.second;
    n->update();
    return {ret.first, n};
  } else {
    n->push();
    auto ret = split(n->R, k - l_size - 1);
    n->R = ret.first;
    n->update();
    return {n, ret.second};
  }
}

void print_tree(Node* n) {
  if (!n) {
    return;
  }

  n->push();
  print_tree(n->L);
  cout << n->value << ' ';
  print_tree(n->R);
}

int main() {
  srand(time(NULL));
  int n, m = 0;
  cin >> n >> m;
  vector<Node*> arr;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    cin >> x;
    arr.push_back(new Node(x));
  }

  stack<Node*> s;
  Node* tree = nullptr;
 
  for (int i = 0; i < n; ++i) {
    Node* cur_node = arr[i];
    Node* last_node = nullptr;
    while (!s.empty() && s.top()->y > cur_node->y) {
      last_node = s.top();
      last_node->update();
      s.pop();
    }
    if (s.empty()) {
        tree = cur_node;
        tree->update();
    }
    if (last_node) {
      cur_node->L = last_node;
      cur_node->update();
      if (!s.empty()) {
        s.top()->R = cur_node;
        s.top()->update();
      }
    } else {
      if (!s.empty()) {
        last_node = s.top();
        last_node->update();
        last_node->R = cur_node;
        last_node->update();
      }
    }
    s.push(cur_node);
  }

  for (int i = 0; i < m; ++i) {
    int type = -1;
    cin >> type;

    if (type == 1) {
      int l1, r1, l2, r2;
      cin >> l1 >> r1 >> l2 >> r2;
      Node* left_part;
      Node* middle_part_one;
      Node* middle_part_two;
      Node* middle_part_three;
      Node* right_part;

      --l1;
      --l2;
      tie(left_part, middle_part_one) = split(tree, l1);
      tie(middle_part_one, middle_part_two) = split(middle_part_one, r1 - l1);
      tie(middle_part_two, middle_part_three) = split(middle_part_two, l2 - r1);
      tie(middle_part_three, right_part) = split(middle_part_three, r2 - l2);

      print_tree(left_part);
      cout << "| ";
      print_tree(middle_part_one);
      cout << "| ";
      print_tree(middle_part_two);
      cout << "| ";
      print_tree(middle_part_three);
      cout << "| ";
      print_tree(right_part);
      cout << '\n';

      tree = merge(left_part, middle_part_three);
      tree = merge(tree, middle_part_two);
      tree = merge(tree, middle_part_one);
      tree = merge(tree, right_part); 

    }

    print_tree(tree);
    cout << '\n';
  }

  // print_tree(tree);

  return 0;
}