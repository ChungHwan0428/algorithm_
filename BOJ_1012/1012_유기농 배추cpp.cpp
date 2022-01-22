#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int n, m, k, answer = 0;

vector<vector<int>>v;
vector<pair<int, int>>dir;

int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

void Initialize() {
    v.clear();
    v.resize(n, vector<int>(m));
    dir.clear();
    dir.resize(k);
    answer = 0;
}

void sol() {

    int x, y, nx, ny;

    queue<pair<int, int>>q;
    
    for (int i = 0; i < k; i++) {
        x = dir[i].first;
        y = dir[i].second;

        if (v[x][y] != -1)
            continue;

        answer++;
        q.push({ x,y });
        v[x][y] = answer;

        while (!q.empty()) {
            x = q.front().first;
            y = q.front().second;

            q.pop();

            for (int j = 0; j < 4; j++) {
                nx = x + x_[j];
                ny = y + y_[j];

                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;

                if (v[nx][ny] != -1)
                    continue;

                v[nx][ny] = answer;
                q.push({ nx,ny });

            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc, a, b;

    cin >> tc;

    for (int i = 0; i < tc; i++) {
        cin >> n >> m >> k;
        Initialize();
        for (int j = 0; j < k; j++) {
            cin >> a >> b;
            dir[j] = { a,b };
            v[a][b] = -1;
        }

        sol();

        cout << answer << "\n";

    }

    return 0;
}