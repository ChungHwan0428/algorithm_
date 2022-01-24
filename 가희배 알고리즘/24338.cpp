#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, m, answer = 0;

int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

vector<vector<char>>v;
vector<vector<int>>visit;

struct dir {
    int n=0, s=0, e=0, w=0, num;
};

map<pair<int, int>, dir>mm;

void checking() {

    int a, b, nx, ny, px, py;

    for (auto iter = mm.begin(); iter != mm.end(); iter++) {
        a = iter->first.first;
        b = iter->first.second;

        for (int i = 0; i < 4; i++) {
            px = a - x_[i];
            py = b - y_[i];
            nx = a + x_[i];
            ny = b + y_[i];

            if (px<1 || py<1 || px>n || py>m)
                continue;

            if (v[px][py] == '#')
                continue;

            if (nx<1 || ny<1 || nx>n || ny>m)
                continue;

            if (v[nx][ny] == '#')
                continue;

            if ((v[px][py] == '.' && v[nx][ny] == '.') || (v[px][py] == '1' && v[nx][ny] == '1'))
                continue;

            if (v[px][py] == 'P' || v[px][py] == 'B')
                continue;

            if (v[nx][ny] == 'P' || v[nx][ny] == 'B') {
                if (v[px][py] == '.')
                    continue;
                else {
                    if (i == 0) {
                        iter->second.w = 1;
                    }
                    else if (i == 1) {
                        iter->second.e = 1;
                    }
                    else if (i == 2) {
                        iter->second.n = 1;
                    }
                    else {
                        iter->second.s = 1;
                    }
                    continue;
                }
            }

            if (i == 0) {
                if (v[px][py] == '.') {
                    iter->second.e = 1;
                }
                else {
                    iter->second.w = 1;
                }
            }
            else if (i == 1) {
                if (v[px][py] == '.') {
                    iter->second.w = 1;
                }
                else {
                    iter->second.e = 1;
                }
            }
            else if (i == 2) {
                if (v[px][py] == '.') {
                    iter->second.s = 1;
                }
                else {
                    iter->second.n = 1;
                }
            }
            else {
                if (v[px][py] == '.') {
                    iter->second.n = 1;
                }
                else {
                    iter->second.s = 1;
                }
            }

        }
    }
}


void func(int x, int y, int xh) {

    int a, b, h, nx, ny;

    queue<pair<int, pair<int, pair<int,vector<char>>>>>q;
    q.push({ xh,{x,{y,vector<char>(21,' ')}} });

    while (!q.empty()) {
        a = q.front().second.first;
        b = q.front().second.second.first;
        h = q.front().first;

        vector<char>temp = q.front().second.second.second;

        if (v[a][b] == 'P' || v[a][b] == 'B') {
            answer = 1;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if (v[i][j] == '?') {
                        if (temp[mm[{i, j}].num] != ' ') {
                            cout<<temp[mm[{i, j}].num];
                        }
                        else {
                            cout << 'W';
                        }
                    }
                    else
                        cout << v[i][j];
                }
                cout << "\n";
            }
            return;
        }

        for (int i = 0; i < 4; i++) {
            nx = a + x_[i];
            ny = b + y_[i];

            temp = q.front().second.second.second;

            if (nx<1 || ny<1 || nx>n || ny>m)
                continue;

            if (visit[nx][ny] == 1 || v[nx][ny] == '#')
                continue;

            if (v[nx][ny] == '?') {
                if (temp[mm[{nx, ny}].num] != ' ')
                    continue;
                if (i == 0) {
                    if (h == 0 && mm[{nx, ny}].e==1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'E';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 1,{nx+x_[i],{ny+y_[i],temp}} });
                    }
                    else if (h == 1 && mm[{nx, ny}].w == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'W';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 0,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                }
                else if (i == 1) {
                    if (h == 0 && mm[{nx, ny}].w == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'W';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 1,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                    else if (h == 1 && mm[{nx, ny}].e == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'E';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 0,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                }
                else if (i == 2) {
                    if (h == 0 && mm[{nx, ny}].s == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'S';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 1,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                    else if (h == 1 && mm[{nx, ny}].n == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'N';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 0,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                }
                else {
                    if (h == 0 && mm[{nx, ny}].n == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'N';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 1,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                    else if (h == 1 && mm[{nx, ny}].s == 1) {
                        if (visit[nx + x_[i]][ny + y_[i]] == 1)
                            continue;
                        temp[mm[{nx, ny}].num] = 'S';
                        visit[nx + x_[i]][ny + y_[i]] = 1;
                        q.push({ 0,{nx + x_[i],{ny + y_[i],temp}} });
                    }
                }
                continue;
            }

            if (h == 0) {
                if (v[nx][ny] == '.') {
                    visit[nx][ny] = 1;
                    q.push({ h,{nx,{ny,temp}} });
                }
                else if (v[nx][ny] == 'P') {
                    visit[nx][ny] = 1;
                    q.push({ h,{nx,{ny,temp}} });
                }
                else if (v[nx][ny] == 'B') {
                    visit[nx][ny] = 1;
                    q.push({ h,{nx,{ny,temp}} });
                }
            }
            else {
                if (v[nx][ny] == '1') {
                    visit[nx][ny] = 1;
                    q.push({ h,{nx,{ny,temp}} });
                }
            }
            
        }

        q.pop();

    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int cnt = 0;

    cin >> n >> m;

    int a, b;
    string k;
    v.resize(n + 1, vector<char>(m + 1));
    visit.resize(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        cin >> k;
        for (int j = 1; j <= m; j++) {
            v[i][j] = k[j-1];
            if (v[i][j] == '?') {
                cnt++;
                mm[{i, j}] = { 0,0,0,0,cnt };
            }
        }
    }

    cin >> a >> b;

    checking();

    visit[a][b] = 1;

    if (v[a][b] == '1') {
        func(a, b, 1);
    }
    else{
        func(a, b, 0);
    }

    
    if(answer==0)
        cout << -1;


    return 0;
}