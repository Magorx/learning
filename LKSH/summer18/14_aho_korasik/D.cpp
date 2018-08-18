#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
const int ALPHABET_SIZE = 128;
vector<char> ans;
int n;
int cnt;

struct Node {
  bool isTerm;
  Node* next[ALPHABET_SIZE];
  Node* suff_link;

  Node() {
    isTerm = false;
    suff_link = nullptr;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
      next[i] = nullptr;
    }
  }
};

Node* root;

void add(string s) {
  Node* cur_v = root;
  for (char ch : s) {
    int c = ch - ' ';
    if (!cur_v->next[c]) {
      cur_v->next[c] = new Node();
    }
    cur_v = cur_v->next[c];
  }
  cur_v->isTerm = true;
}

void cnt_suffs() {
  root->suff_link = root;
  queue<Node*> q;
  for (int c = 0; c < ALPHABET_SIZE; ++c) {
    if (!root->next[c]) {
      root->next[c] = root;
    } else {
      root->next[c]->suff_link = root;
      q.push(root->next[c]);
    }
  }

  while (!q.empty()) {
    Node* v = q.front();
    q.pop();
    if (v->suff_link->isTerm) {
      v->isTerm = true;
    }

    for (int c = 0; c < ALPHABET_SIZE; ++c) {
      if (!v->next[c]) {
        v->next[c] = v->suff_link->next[c];
      } else {
        v->next[c]->suff_link = v->suff_link->next[c];
        q.push(v->next[c]);
      }
    }
  }
}

bool check_s(string s) {
  Node* cur_v = root;
  for (char ch : s) {
    if (cur_v->isTerm) {
      return true;
    } else {
      int c = ch - ' ';
      cur_v = cur_v->next[c];
    }
  }
  if (cur_v->isTerm) {
    return true;
  } else {
    return false;
  }
}

int main() {
  root = new Node();
  cin >> n;
  cnt = 0;
  string s;
  getline(cin, s);  
  for (int i = 0; i < n; ++i) {
    getline(cin, s);
    add(s);
  }

  cnt_suffs();
  while (getline(cin, s)) {
    if (check_s(s)) {
      cout << s << '\n';
    }
  }

  return 0;
}
