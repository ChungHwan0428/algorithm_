#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, m, k, total, cnt = 0;

int x_[5] = { 0,-1,1,0,0 };
int y_[5] = { 0,0,0,-1,1 };

vector<vector<pair<int,pair<int,int>>>>v;
vector<pair<int, pair<int,int>>>where;
vector<vector<vector<int>>>pri;

void Count() {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j].first == 0 || v[i][j].first == 1)
                continue;

            if (v[i][j].second.second == 1) {
                v[i][j] = { 0,{0,0} };
            }
            else {
                v[i][j].second.second--;
            }

        }
    }

}

void Move() {

    int x, y, nx, ny, dir, ndir, go;

    vector<vector<pair<int, pair<int, int>>>>temp = v;

    for (int i = 1; i <= m; i++) {

        if (where[i].first == -1)
            continue;

        go = 0;

        x = where[i].second.first;
        y = where[i].second.second;
        dir = where[i].first;

        for (int j = 0; j < 4; j++) {
            ndir = pri[i][dir][j];
            nx = x + x_[ndir];
            ny = y + y_[ndir];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                continue;

            if (v[nx][ny].first == 2 || v[nx][ny].first == 1)
                continue;

            if (temp[nx][ny].first == 1) {
                total--;
                temp[x][y].first = 2;
                where[i] = { -1,{-1,-1} };
                go++;
                break;
            }

            temp[x][y].first = 2;
            temp[nx][ny] = { 1,{i,k} };
            where[i] = { ndir,{nx,ny} };
            go++;
            break;

        }
        if (go == 0) {
            for (int j = 0; j < 4; j++) {
                ndir = pri[i][dir][j];
                nx = x + x_[ndir];
                ny = y + y_[ndir];

                if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                    continue;

                if (v[nx][ny].first == 2 && v[nx][ny].second.first == i) {
                    temp[x][y].first = 2;
                    temp[nx][ny] = { 1,{i,k} };
                    where[i] = { ndir,{nx,ny} };
                    break;
                }
            }
        }
    }

    v = temp;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b, c, d;

    cin >> n >> m >> k;

    v.resize(n, vector<pair<int,pair<int,int>>>(n));
    pri.resize(m + 1, vector<vector<int>>(5, vector<int>(4)));
    where.resize(m + 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a;
            if (a != 0) {
                where[a] = { 0, {i,j} };
                v[i][j] = { 1,{a,k} };
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        cin >> where[i].first;
    }
   
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= 4; j++) {
            cin >> a >> b >> c >> d;
            pri[i][j] = { a,b,c,d };
        }
    }

    total = m;

    while (total != 1 && cnt <= 1000) {
        cnt++;
        Move();
        Count();


    }

    if (cnt > 1000)
        cout << -1;
    else
        cout << cnt;

    return 0;
}