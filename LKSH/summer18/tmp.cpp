#include <iostream>

#define int long long

using namespace std;
const int N = (int)1e6;

int p[N];
bool on_c[N];
int ans[N];
bool use[N];
int t;
int edge = -1;
int superflag = 0;

void dfs(int v) {
    use[v] = true;
    if (use[p[v]]) {
        if (ans[p[v]]) {
            ans[v] = ans[p[v]];
        } else {
            edge = p[v];
            superflag = 1;
            ans[v] = v;
            if (p[v] == v) {
                superflag = 2;
            }
        }
    } else {
        dfs(p[v]);
        if (superflag == 1) {
            if (v == edge) {
                ans[v] = v;
                superflag = 2;
            } else {
                ans[v] = v;
            }
        } else if (superflag == 2) {
            ans[v] = edge;
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> p[i];

    for (int i = 1; i <= n; i++)
    {
        superflag = 0;
        edge = -1;
        if (!use[i] || ans[i] == 0)
            dfs(i);
    }

    for (int i = 1; i <= n; i++)
    {
        if (ans[i] == 0) {
            cout << ans[p[p[p[i]]]] << " ";
            continue;
        }
        cout << ans[i] << ' ';
    }

    return 0;
}