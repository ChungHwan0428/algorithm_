#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, m, sx, sy, ex, ey, answer1=999999999, answer2=999999999;

vector<vector<char>>v;
vector<vector<int>>dp;
vector<vector<int>>near_garbage;


int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    v.resize(n, vector<char>(m));
    dp.resize(n, vector<int>(m,99999999));
    near_garbage.resize(n, vector<int>(m));

    char a;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a;
            v[i][j] = a;
            if (a == 'F') {
                ex = i, ey = j;
            }
            else if (a == 'S') {
                sx = i, sy = j;
            }
        }
    }

    int tx, ty;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == 'g' || v[i][j] == 'F' || v[i][j] == 'S')
                continue;
            for (int k = 0; k < 4; k++) {
                tx = i + x_[k], ty = j + y_[k];
                if (tx<0 || ty<0 || tx>=n || ty>=m)
                    continue;
                if (v[tx][ty] == 'g') {
                    near_garbage[i][j] = 1;
                    break;
                }
            }
        }
    }
    
    dp[sx][sy] = 0;

    priority_queue < pair<int, pair<int, pair<int, int>>>>pq;

    pq.push({ 0,{0,{sx,sy}} });

    int x, y, nx, ny, g1, g2;

    while (!pq.empty()) {
        g1 = -pq.top().first;
        g2 = -pq.top().second.first;
        x = pq.top().second.second.first;
        y = pq.top().second.second.second;

        pq.pop();

        if (dp[x][y] < g1)
            continue;

        for (int i = 0; i < 4; i++) {
            nx = x + x_[i];
            ny = y + y_[i];

            if (nx<0 || ny<0 || nx>=n || ny>=m)
                continue;
            
            if (v[nx][ny] == 'g') {
                if (dp[nx][ny] > g1 + 1) {
                    dp[nx][ny] = g1 + 1;
                    pq.push({ -(g1 + 1),{-g2,{nx,ny}} });
                }
            }
            else if (v[nx][ny] == '.') {
                if (dp[nx][ny] > g1) {
                    if (near_garbage[nx][ny] == 1) {
                        dp[nx][ny] = g1;
                        pq.push({ -g1,{-(g2 + 1),{nx,ny}} });
                    }
                    else {
                        dp[nx][ny] = g1;
                        pq.push({ -g1,{-g2,{nx,ny}} });
                    }
                }
            }
            else if (v[nx][ny] == 'F') {
                if (answer1 >= g1) {
                    answer1 = min(answer1, g1);
                    answer2 = min(answer2, g2);
                }
            }
            else
                continue;

        }
    }

    cout << answer1 << " " << answer2;
    
    return 0;
}