#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, k, m, answer = -1;

vector<int>visit_n;
vector<int>visit_t;
vector<vector<int>>v;
vector<vector<int>>tube;

void sol() {

    int node, dist;

    visit_n[1] = 1;

    queue<pair<int, int>>q;

    q.push({ 1,1 });

    while (!q.empty()) {
        node = q.front().first;
        dist = q.front().second;

        q.pop();

        if (node == n) {
            answer = dist;
            break;
        }

        for (int i = 0; i < v[node].size(); i++) {
            int next_t = v[node][i];

            if (visit_t[next_t] == 1)
                continue;
            visit_t[next_t] = 1;

            for (int j = 0; j < tube[next_t].size(); j++) {
                int next_node = tube[next_t][j];
                if (visit_n[next_node] == 1)
                    continue;

                visit_n[next_node] = 1;
                q.push({ next_node,dist + 1 });
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a;

    cin >> n >> k >> m;

    visit_n.resize(n + 1);
    visit_t.resize(m);
    v.resize(n + 1);
    tube.resize(m, vector<int>(k));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            cin >> a;
            tube[i][j] = a;
            v[a].push_back(i);
        }
    }

    sol();

    cout << answer;

    return 0;
}