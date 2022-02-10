#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int n, answer = 0;

int x_[4] = { 0,0,1,-1 };
int y_[4] = { 1,-1,0,0 };

vector<vector<int>>v;
vector<vector<int>>node;

void Find(int a) {

    int nx, ny, cnt, ncnt;
    int ax, ay, acnt = -1, ancnt = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j] != 0)
                continue;
            cnt = 0, ncnt = 0;
            for (int k = 0; k < 4; k++) {
                nx = i + x_[k];
                ny = j + y_[k];

                if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                    continue;

                for (int p = 0; p < 4; p++) {
                    if (v[nx][ny] == node[a][p])
                        cnt++;
                    else if (v[nx][ny] == 0) {
                        ncnt++;
                    }
                }
            }
            if (acnt < cnt) {
                acnt = cnt;
                ancnt = ncnt;
                ax = i;
                ay = j;
            }
            else if (acnt == cnt) {
                if (ancnt < ncnt) {
                    acnt = cnt;
                    ancnt = ncnt;
                    ax = i;
                    ay = j;
                }
            }
        }
    }
    
    v[ax][ay] = a;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a;

    cin >> n;

    v.resize(n, vector<int>(n));
    node.resize(n * n + 1, vector<int>(4));

    for (int i = 0; i < n * n; i++) {
        cin >> a;
        for (int j = 0; j < 4; j++) {
            cin >> node[a][j];
        }
        Find(a);
    }


    int nx, ny, now, cnt;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            now = v[i][j];
            cnt = 0;
            for (int k = 0; k < 4; k++) {
                nx = i + x_[k];
                ny = j + y_[k];

                if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                    continue;

                for (int p = 0; p < 4; p++) {
                    if (v[nx][ny] == node[now][p])
                        cnt++;
                }
            }

            if (cnt == 0)
                continue;
            else
                answer += (int)pow(10, cnt - 1);
        }
    }

    cout << answer;

    return 0;
}