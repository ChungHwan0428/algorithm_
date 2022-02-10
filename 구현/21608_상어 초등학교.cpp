/*학생 번호 순서대로 배치 시작
학생을 배치할때마다 모든 위치를 탐색한다.
1)만약 해당 위치에 다른 학생이 있으면 다음 위치로.
2)해당 위치에서 선호도 수를 조사한다.
3)만약 이전까지 탐색한 위치에서의 조건보다 현재 위치에서의 조건이 좋다면 현재 위치를 가장 좋은 것으로 갱신한다.
4)모든 위치를 탐색한 경우, 최종적으로 조건에 맞는 위치에 학생을 배치한다.

5)모든 학생에 대해서 인접한 칸에 선호도 조사 이후, 조건에 맞게 반환값을 설정한다.

*/


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
