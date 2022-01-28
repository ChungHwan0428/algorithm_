#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, max_, min_;

vector<vector<int>>v;
vector<vector<int>>dp;
vector<vector<vector<pair<int, int>>>>visit;
vector<vector<int>>vv;

int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    v.resize(n + 1, vector<int>(n + 1));
    vv.resize(n + 1, vector<int>(n + 1));
    dp.resize(n + 1, vector<int>(n + 1,1000));
    visit.resize(n + 1, vector < vector<pair<int, int>>>(n + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> v[i][j];
        }
    }

    max_ = max(v[1][1], v[n][n]);
    min_ = min(v[1][1], v[n][n]);

    priority_queue<pair<int, pair<int,pair<int,pair<int,int>>>>>pq;

    pq.push({ 0,{1,{1,{max_,min_}}} });

    dp[1][1] = 0;
    vv[1][1] = 1;
    visit[1][1].push_back({ max_,min_ });

    int x, y, dist, nx, ny, ndist, nmax, nmin, pmax, pmin;

    while (!pq.empty()) {
        dist = -pq.top().first;
        x = pq.top().second.first;
        y = pq.top().second.second.first;
        pmax = pq.top().second.second.second.first;
        pmin = pq.top().second.second.second.second;

        pq.pop();

        if (dp[x][y] < dist)
            continue;

        if (x == n && y == n)
            break;

        for (int i = 0; i < 4; i++) {
            nx = x + x_[i];
            ny = y + y_[i];

            if (nx<1 || ny<1 || nx>n || ny>n)
                continue;

            if (vv[nx][ny] == 1)
                continue;  

            nmax = max(pmax, v[nx][ny]);
            nmin = min(pmin, v[nx][ny]);
            ndist = (nmax - nmin) - (max_ - min_);

            if (dp[nx][ny] >= ndist) {
                int temp = 0;
                for (int j = 0; j < visit[nx][ny].size(); j++) {
                    if (visit[nx][ny][j].first == nmax && visit[nx][ny][j].second == nmin) {
                        temp++;
                        break;
                    }
                }
                if (temp == 0) {
                    dp[nx][ny] = ndist;
                    visit[nx][ny].push_back({ nmax,nmin });
                    pq.push({ -ndist,{nx,{ny,{nmax,nmin}}} });
                }
            }
        }
    }

    cout << dp[n][n] + (max_ - min_);

    return 0;
}