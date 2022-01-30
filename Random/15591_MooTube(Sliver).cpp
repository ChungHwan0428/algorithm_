#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, q;

vector<vector<pair<int,int>>>v;

void sol(int cost, int start) {

    int answer = 0;

    vector<int>visit(n + 1);
    
    visit[start] = 1;

    queue<int>q;

    q.push(start);

    int node, nnode, ncost;

    while (!q.empty()) {
        node = q.front();
        q.pop();

        for (int i = 0; i < v[node].size(); i++) {
            nnode = v[node][i].first;
            ncost = v[node][i].second;

            if (ncost < cost)
                continue;

            if (visit[nnode] == 1)
                continue;

            visit[nnode] = 1;
            answer++;
            q.push(nnode);
        }
    }

    cout << answer << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> q;

    v.resize(n + 1);

    int a, b, c;

    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b >> c;
        v[a].push_back({ b,c });
        v[b].push_back({ a,c });
    }

    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        sol(a, b);
    }

    return 0;
}