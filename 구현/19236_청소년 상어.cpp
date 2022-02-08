#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int answer = 0;

int x_[8] = { -1,-1,0,1,1,1,0,-1 };
int y_[8] = { 0,-1,-1,-1,0,1,1,1 };

vector<vector<pair<int, int>>>v;
vector<pair<int, int>>where;

void Move() {

    int x, y, dir, nx, ny;

    for (int i = 1; i <= 16; i++) {
        if (where[i].first == -1)
            continue;

        x = where[i].first;
        y = where[i].second;
        dir = v[x][y].second;

        for (int i = 0; i < 8; i++) {
            nx = x + x_[dir];
            ny = y + y_[dir];
            
            if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) {
                dir = (dir + 1) % 8;
                continue;
            }

            if (v[nx][ny].first == 99) {
                dir = (dir + 1) % 8;
                continue;
            }

            where[v[nx][ny].first] = { x,y };
            where[v[x][y].first] = { nx,ny };

            int temp = v[x][y].first;
            v[x][y] = { v[nx][ny].first, v[nx][ny].second };
            v[nx][ny] = { temp,dir };

            break;

        }

    }

}

void Eat(int x, int y, int total) {

    int dir = v[x][y].second, nx, ny;

    where[v[x][y].first] = { -1,-1 };

    total += v[x][y].first;

    v[x][y] = { 99,dir };

    answer = max(answer, total);

    Move();

    for (int i = 1; i < 4; i++) {
        nx = x + x_[dir] * i;
        ny = y + y_[dir] * i;

        if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4)
            continue;

        if (v[nx][ny].first == 0)
            continue;

        vector<vector<pair<int, int>>>tmp_v = v;
        vector<pair<int, int>>tmp_where = where;
        v[x][y] = { 0,0 };
        Eat(nx, ny, total);
        v = tmp_v;
        where = tmp_where;

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b;

    v.resize(4, vector<pair<int, int>>(4));
    where.resize(17);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a >> b;
            v[i][j] = { a,b-1 };
            where[a] = { i,j };
        }
    }

    Eat(0, 0, 0);

    cout << answer;

    return 0;
}