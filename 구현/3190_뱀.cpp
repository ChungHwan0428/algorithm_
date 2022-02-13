#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int x_[4] = { 0,1,0,-1 };
int y_[4] = { 1,0,-1,0 };

int n, k, l, nowx, nowy, nowdir, nowsec, end_=0;

vector<vector<int>>v;

queue<pair<int, int>>q;

bool Turn(int sec, int dir) {

    if (end_ == 1)
        return true;

    int nx, ny;

    for (nowsec; nowsec <= sec; nowsec++) {
        nowx = nowx + x_[nowdir];
        nowy = nowy + y_[nowdir];

        if (nowx < 1 || nowy < 1 || nowx > n || nowy > n)
            return true;

        if (v[nowx][nowy] == 1) {
            return true;
        }
        else if (v[nowx][nowy] == 2) {
            v[nowx][nowy] = 1;
            q.push({ nowx,nowy });
        }
        else {
            nx = q.front().first;
            ny = q.front().second;

            q.pop();

            v[nx][ny] = 0;
            v[nowx][nowy] = 1;
            q.push({ nowx,nowy });
        }
    }

    nowdir = (dir + nowdir) % 4;

    return false;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b;
    char c;

    cin >> n >> k;

    v.resize(n + 1, vector<int>(n + 1));
    
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        v[a][b] = 2;
    }

    cin >> l;

    nowx = 1, nowy = 1, nowdir = 0, nowsec = 1;
    v[1][1] = 1;
    q.push({ 1,1 });

    for (int i = 0; i < l; i++) {
        cin >> a >> c;

        if (c == 'D')
            b = 1;
        else
            b = 3;

        if (Turn(a, b)) {
            end_ = 1;
        }

    }

    Turn(11111, 0);

    cout << nowsec;

    return 0;
}