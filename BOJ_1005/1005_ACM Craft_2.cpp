#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int n, des;
long long answer = 0;

vector<int>v;
vector<int>dep;
vector<long long>time_;
vector<vector<int>>path;

void func() {

    queue<int>q;

    for (int i = 1; i <= n; i++) {
        if (dep[i] == 0) {
            q.push(i);
            time_[i] = v[i];
        }
    }

    int node, nnode;

    while (!q.empty()) {
        node = q.front();
        q.pop();

        for (int i = 0; i < path[node].size(); i++) {
            nnode = path[node][i];

            time_[nnode] = max(time_[nnode], time_[node] + v[nnode]);
            dep[nnode]--;

            if (dep[nnode] == 0)
                q.push(nnode);
        }

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t, k, a, b;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n >> k;

        v.clear();
        v.resize(n + 1);
        dep.clear();
        dep.resize(n + 1);
        time_.clear();
        time_.resize(n + 1, -1);
        path.clear();
        path.resize(n + 1);

        answer = 0;

        for (int j = 1; j <= n; j++) {
            cin >> v[j];
        }
        for (int j = 0; j < k; j++) {
            cin >> a >> b;
            path[a].push_back(b);
            dep[b]++;
        }

        cin >> des;

        func();

        cout << time_[des] << "\n";

    }

    return 0;
}