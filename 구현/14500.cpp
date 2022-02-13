/*
1) 나는 겹치는 경우 말고 모든 경우의 수를 그냥 배열로 나타내서 구했음.
2) ㅜ 모양을 제외하고는 dfs로 회전, 대칭을 모두 표현가능하다. 따라서 ㅜ는 따로 구현하고, 나머지는 dfs로 진행.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int x_[57] = { 0,0,0,1,2,3 ,0,1,1 ,0,-1,-1,1,1,2  ,0,0,1,1,2,1,0,0,-1,-1,-2,-1 ,0,0,-1,1,2,2,0,0,1,-1,-2,-2  ,0,0,1,1,2,2,0,0,-1,-1,-2,-2 ,0,1,1,-1,-1,-2 };
int y_[57] = { 1,2,3,0,0,0 ,1,0,1 ,1,1,2,0,1,1    ,1,2,1,0,0,-1,-1,-2,-1,0,0,1 ,1,2,2,0,0,1,-1,-2,-2,0,0,-1  ,1,2,2,0,0,-1,-1,-2,-2,0,0,1 ,1,1,2,0,1,1 };
/*
int x1[3] = { 0,1,1 };
int y1[3] = { 1,0,1 };

int x2[6] = { 0,-1,-1,1,1,2 };
int y2[6] = { 1,1,2,0,1,1 };

int x3[12] = { 0,0,1,1,2,1,0,0,-1,-1,-2,-1 };
int y3[12] = { 1,2,1,0,0,-1,-1 - 2,-1,0,0,1 };

int x3[12] = { 0,0,-1,1,2,2,0,0,1,-1,-2,-2 };
int y3[12] = { 1,2,2,0,0,1,-1,-2,-2,0,0,-1 };

*/

int n, m, answer = 0;

vector<vector<int>>v;

void func(int x, int y) {

    int total, nx, ny;

    for (int i = 0; i < 57; i++) {
        nx = x + x_[i];
        ny = y + y_[i];

        if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
            i = ((i / 3) + 1) * 3 - 1;
            total = 0;
            continue;
        }
        
        if (i % 3 == 0) {
            total = v[x][y] + v[nx][ny];
        }
        else {
            total += v[nx][ny];
        }

        if ((i + 1) % 3 == 0)
            answer = max(answer, total);

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    
    v.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            func(i, j);

        }
    }

    cout << answer;

    return 0;
}
