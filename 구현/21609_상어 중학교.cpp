#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, m, answer = 0;

int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

vector<vector<int>>v;
vector<vector<int>>visit;
vector<pair<int, int>>max_group;

pair<int, pair<int, pair<int, int>>> max_node = { 0,{0,{0,0} } };

void Find_group(int a, int b) {

    if (v[a][b] == -2 || v[a][b] == -1 || v[a][b] == 0 || visit[a][b] == 1)
        return;

    vector<vector<int>>temp_visit = visit;
    vector<pair<int,int>>tmax_group;

    int x, y, nx, ny, node = v[a][b], total = 1, rain_total = 0;

    temp_visit[a][b] = 1;

    queue<pair<int, int>>q;

    q.push({ a,b });
    tmax_group.push_back({ a,b });

    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;

        q.pop();

        for (int i = 0; i < 4; i++) {
            nx = x + x_[i];
            ny = y + y_[i];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                continue;

            if (temp_visit[nx][ny] == 1 || v[nx][ny] == -1 || v[nx][ny] == -2)
                continue;

            if (v[nx][ny] == 0) {
                total++;
                rain_total++;
                temp_visit[nx][ny] = 1;
                tmax_group.push_back({ nx,ny });
                q.push({ nx,ny });
            }
            else if (v[nx][ny] == node) {
                total++;
                temp_visit[nx][ny] = 1;
                visit[nx][ny] = 1;
                tmax_group.push_back({ nx,ny });
                q.push({ nx,ny });
            }
            else
                continue;
          
        }

    }
    
    if (total < 2)
        return;

    if (max_node.first < total) {
        max_node = { total, {rain_total,{a, b}} };
        max_group = tmax_group;
    }
    else if (max_node.first == total) {
        if (rain_total >= max_node.second.first) {
            max_node = { total, {rain_total,{a, b}} };
            max_group = tmax_group;
        }
    }

}

void Remove() {

    for (int i = 0; i < max_node.first; i++) {
        v[max_group[i].first][max_group[i].second] = -2;
    }

    answer += max_node.first * max_node.first;

}

void Gravity() {

    int cnt = 0, ncnt = 0;

    for (int i = 0; i < n; i++) {
        cnt = 0;
        ncnt = 0;
        for (int j = 0; j < n; j++) {
            if (v[j][i] == -1) {
                if (cnt == 0) {
                    ncnt = 0;
                }
                else {
                    if (ncnt == 0) {
                        cnt = 0;
                    }
                    else {
                        int temp = 0;
                        for (int k = j - 1; k >= j - cnt - ncnt; k--) {
                            if (v[k][i] == -2) {
                                temp++;
                            }
                            else {
                                v[k + temp][i] = v[k][i];
                            }
                        }
                        for (int k = j - cnt - ncnt; k < j - cnt; k++) {
                            v[k][i] = -2;
                        }
                        cnt = 0, ncnt = 0;
                    }
                }  
            }
            else if (v[j][i] == -2) {
                ncnt++;
            }
            else {
                cnt++;
            }
        }
        if (ncnt != 0) {
            int temp = 0;
            for (int k = n - 1; k >= n - cnt - ncnt; k--) {
                if (v[k][i] == -2) {
                    temp++;
                }
                else {
                    v[k + temp][i] = v[k][i];
                }
            }
            for (int k = n - cnt - ncnt; k < n - cnt; k++) {
                v[k][i] = -2;
            }
        }
    }

}

void Rotation() {

    vector<vector<int>> newGraph(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 반시계방향 90도
            newGraph[i][j] = v[j][n - i - 1];
        }
    }

    v = newGraph;
}

bool func() {

    visit.clear();
    visit.resize(n, vector<int> (n));
    max_node = { 0,{0,{0,0} } };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visit[i][j] != 1) {
                Find_group(i, j);
            }
        }
    }

    if (max_node.first == 0)
        return false;

    Remove();

    Gravity();
    Rotation();
    Gravity();

    return true;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    v.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    while (func()) {


    }

    cout << answer;

    return 0;
}