#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;

int n, m, cnt = 0;

vector<int>v;
vector<vector<int>>f;
vector<vector<int>>e;

void func(int x, int y) {
    for (int i = 0; i < e[y].size(); i++) {
        f[x].push_back(e[y][i]);
        f[e[y][i]].push_back(x);
    }
}

void dfs(int node) {

    for (int i = 0; i < f[node].size(); i++) {
        if (v[f[node][i]] != 0)
            continue;
        v[f[node][i]] = cnt;
        dfs(f[node][i]);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    char a;
    int b, c;

    e.resize(n + 1);
    v.resize(n + 1);
    f.resize(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a == 'E') {
            e[b].push_back(c);
            e[c].push_back(b);
        }
        else {
            f[b].push_back(c);
            f[c].push_back(b);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < e[i].size(); j++) {
            func(i, e[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (v[i] != 0)
            continue;
        cnt++;
        v[i] = cnt;
        dfs(i);
    }

    cout << cnt;

    return 0;
}