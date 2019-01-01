int jump_cnt(int v, int i) {
  if (jump[v][i] != -1) {
    return jump[v][i];
  } else if (i == 0) {
    return v;
  } else {
    int ret = jump_cnt(jump_cnt(v, i - 1), i - 1);
    jump[v][i] = ret;
    return ret;
  }
}

int min_edge(int v, int i) {
  jump_cnt(v, i);
  if (dp[v][i] != -1) {
    return dp[v][i];
  } else if (i <= 1) {
    return edge_to[v];
  } else {
    int ret = min(min_edge(jump_cnt(v, i - 1), i - 1), min_edge(v, i - 1));
  }
}

vector<int> to_bin(int n) {
  vector<int> ret;
  cout << n << " = [";
  while (n) {
    ret.push_back(n % 2);
    n /= 2;
  }
  reverse(ret.begin(), ret.end());
  for (auto x : ret) {
    cout << x;
  }
  cout << "]\n";
  return ret;
}