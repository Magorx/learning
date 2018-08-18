#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<vector<long long>>> fenvik;

long long prefix_sum(int x, int y, int z) {
  long long res = 0;
  for (int i = x; i > 0; i &= (i - 1)) {
    for (int j = y; j > 0; j &= (j - 1)) {
      for (int k = z; k > 0; k &= (k - 1)) {
        res += fenvik[i][j][k];
      }
    }
  }

  return res;
}

long long sum(int x1, int y1, int z1, int x2, int y2, int z2) {
  // cout << "pum-";
  int s1 = prefix_sum(x1, y1, z1);
  int s2 = prefix_sum(x1, y1, z2);
  int s3 = prefix_sum(x1, y2, z1);
  int s4 = prefix_sum(x1, y2, z2);
  int s5 = prefix_sum(x2, y1, z1);
  int s6 = prefix_sum(x2, y1, z2);
  int s7 = prefix_sum(x2, y2, z1);
  int s8 = prefix_sum(x2, y2, z2);
  // cout << "pom\n";
  // cout << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << ' ' << s5 << ' ' << s6 << ' ' << s7 << ' ' << s8 << '\n';

  return s1 - s2 - s3 + s4 - s5 + s6 + s7 - s8;
}

void add(int x, int y, int z, long long delta) {
  for (int i = x; i <= n; i = (i | (i - 1)) + 1) {
    for (int j = y; j <= n; j = (j | (j - 1)) + 1) {
      for (int k = z; k <= n; k = (k | (k - 1)) + 1) {
        // cout << "tadas\n";
        fenvik[i][j][k] += delta; 
      }
    }
  }
}

int main() {
  cin >> n;
  fenvik.resize(n + 1, vector<vector<long long>>(n + 1, vector<long long>(n + 1, 0)));
  while (true) {
    long long type, x1, y1, z1;
    cin >> type >> x1 >> y1 >> z1;
    if (type == 2) {
      int x2, y2, z2;
      cin >> x2 >> y2 >> z2;
      ++x2;
      ++y2;
      ++z2;
      cout << sum(x2, y2, z2, x1, y1, z1) << '\n';
    } else if (type == 1) {
      long long delta;
      cin >> delta;
      ++x1;
      ++y1;
      ++z1;
      add(x1, y1, z1, delta);
      /*for (int i = 0; i <=n; ++i) {
        for (int j = 0; j <= n; ++j) {
          for (int z = 0; z <= n; ++z) {
            cout << fenvik[i][j][z] << ' ';
          }
          cout << '\n';
        }
        cout << '\n';
      }
      cout << '\n';*/
    } else {
      break;
    }
  }

  return 0;
}