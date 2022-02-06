#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, m, t, d, answer = 0;

vector<vector<char>>v;
vector<vector<int>>visit;
vector<vector<int>>down_;

int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

void sol() {

    int x, y, nx, ny, dist, ndist, node, nnode, total_dist, ntotal_dist;

    priority_queue<pair<int, pair<int, int>>>q;

    q.push({ 0,{0,0} });

    visit[0][0] = 0;

    while (!q.empty()) {
        x = q.top().second.first;
        y = q.top().second.second;
        dist = -q.top().first;

        if (v[x][y] >= 'A' && v[x][y] <= 'Z')
            node = v[x][y] - 'A';
        else {
            node = v[x][y] - 'a' + 26;
        }

        if(dist+down_[x][y] <= d)
            answer = max(answer, node);
            
        q.pop();

        for (int i = 0; i < 4; i++) {
            nx = x + x_[i];
            ny = y + y_[i];

            if (nx<0 || ny<0 || nx>=n || ny>=m)
                continue;

            if (v[nx][ny] >= 'A' && v[nx][ny] <= 'Z')
                nnode = v[nx][ny] - 'A';
            else {
                nnode = v[nx][ny] - 'a' + 26;
            }

            if (abs(nnode - node) > t)
                continue;

            if (nnode > node) {
                ndist = dist + (nnode - node) * (nnode - node);
            }
            else {
                ndist = dist + 1;
            }

            if (ndist > d)
                continue;

            if (visit[nx][ny] <= ndist)
                continue;

            visit[nx][ny] = ndist;
            q.push({ -ndist,{nx,ny} });

        }
    }
}

void sol2(int a,int b) {

    int x, y, nx, ny, dist, ndist, node, nnode, total_dist, ntotal_dist;

    visit.clear();
    visit.resize(n, vector<int>(m, 999999999));

    priority_queue<pair<int, pair<int, int>>>q;

    q.push({ 0,{a,b} });

    visit[a][b] = 0;

    while (!q.empty()) {
        x = q.top().second.first;
        y = q.top().second.second;
        dist = -q.top().first;

        if (v[x][y] >= 'A' && v[x][y] <= 'Z')
            node = v[x][y] - 'A';
        else {
            node = v[x][y] - 'a' + 26;
        }

        q.pop();

        for (int i = 0; i < 4; i++) {
            nx = x + x_[i];
            ny = y + y_[i];

            if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                continue;

            if (v[nx][ny] >= 'A' && v[nx][ny] <= 'Z')
                nnode = v[nx][ny] - 'A';
            else {
                nnode = v[nx][ny] - 'a' + 26;
            }

            if (abs(nnode - node) > t)
                continue;

            if (nnode >= node) {
                ndist = dist + 1;
            }
            else {
                ndist = dist + (nnode - node) * (nnode - node);
            }

            if (visit[nx][ny] <= ndist)
                continue;

            visit[nx][ny] = ndist;
            q.push({ -ndist,{nx,ny} });

        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> t >> d;

    v.resize(n, vector<char>(m));
    visit.resize(n, vector<int>(m,999999999));
    down_.resize(n, vector<int>(m));

    string a;

    for (int i = 0; i < n; i++) {
        cin >> a;
        for (int j = 0; j < m; j++) {
            v[i][j] = a[j];
        }
    }

    sol2(0, 0);

    down_ = visit;

    visit.clear();
    visit.resize(n, vector<int>(m, 999999999));

    sol();

    cout << answer;

    return 0;
}