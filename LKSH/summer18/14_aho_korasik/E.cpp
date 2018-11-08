#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
const int ALPHABET_SIZE = 2;
const char MIN_LETTER = '0';
vector<char> ans;
int n;
int cnt;
int last_id = 0;

struct Node {
  bool isTerm;
  Node* next[ALPHABET_SIZE];
  Node* go[ALPHABET_SIZE];
  Node* suff_link;
  bool visited;
  int id;

  Node(int id_) {
    id = id_;
    isTerm = false;
    suff_link = nullptr;
    visited = false;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
      next[i] = nullptr;
      go[i] = nullptr;
    }
  }
};

Node* root;

void add(string s) {
  Node* cur_v = root;
  for (char ch : s) {
    int c = ch - MIN_LETTER;
    if (!cur_v->next[c]) {
      cur_v->next[c] = new Node(last_id);
      ++last_id;
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
      root->go[c] = root;
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
        v->go[c] = v->suff_link->next[c];
      } else {
        v->next[c]->suff_link = v->suff_link->next[c];
        q.push(v->next[c]);
      }
    }
  }
}

bool is_life_real(Node* n, bool flag=true) {
  cout << n << endl;
  cout << "HEAL\n";
  if (n->isTerm) {
    
    return false;
  }
  cout << "HEAL\n";
  if (n == root && !flag) {
    return true;
  }
  cout << "HEAL\n";
  n->visited = true;
  cout << "HEAL\n";

  bool life_is_real = false;

  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (life_is_real) {
      return life_is_real;
    }
    if (n->next[i]) {
      cout << n->id << ' ' << n->next[i]->id << " way next\n";
      life_is_real |= is_life_real(n->next[i], false);
    } else {
      cout << n->id << ' ' << n->next[i]->id << " way next\n";
      life_is_real |= is_life_real(n->go[i], false);
    }
  }

  return life_is_real;
}

bool check_s(string s) {
  Node* cur_v = root;
  for (char ch : s) {
    if (cur_v->isTerm) {
      return true;
    } else {
      int c = ch - MIN_LETTER;
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
  root = new Node(-1);
  cin >> n;
  cnt = 0;
  string s;
  getline(cin, s);  
  for (int i = 0; i < n; ++i) {
    getline(cin, s);
    add(s);
  }
  cnt_suffs();

  if (is_life_real(root)) {
    cout << "TAK\n";
  } else {
    cout << "NIE\n";
  }

  return 0;
}
