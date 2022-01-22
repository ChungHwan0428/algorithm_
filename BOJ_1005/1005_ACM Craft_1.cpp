#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int n, des;
long long answer = 0;

vector<int>v;
vector<long long>dp;
vector<vector<int>>path;

long long func(int node) {

    if (dp[node] != -1)
        return dp[node];

    for (int i = 0; i < path[node].size(); i++) {
        dp[node] = max(dp[node], v[node] + func(path[node][i]));
    }

    if (dp[node] == -1)
        dp[node] = v[node];

    return dp[node];

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
        dp.clear();
        dp.resize(n + 1, -1);
        path.clear();
        path.resize(n + 1);

        answer = 0;

        for (int j = 1; j <= n; j++) {
            cin >> v[j];
        }
        for (int j = 0; j < k; j++) {
            cin >> a >> b;
            path[b].push_back(a);
        }

        cin >> des;
        func(des);
        cout << dp[des] << "\n";

    }

    return 0;
}