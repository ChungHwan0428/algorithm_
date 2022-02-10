/*
빈칸은 -2, 나머지는 문제에서 제시한대로 칸을 채움.

func() 함수를 통해서 문제에서 제시한 한 번의 사이클을 돈다.

func()
 -모든 칸에 대해서 Find_group() 함수 실행, 만약 해당 칸을 이전 Find_group()에 의해서 방문했다면 다음 칸으로 이동.
 -2이상의 가장 큰 블록의 수를 가진 그룹이 없다면 더이상 진행할 필요가 없으므로 종료.
 -Remove() -> Gravity() -> Rotation() -> Gravity() 함수 순서로 조건에 있는대로 진행.

Find_group()
 -현재 상태에서 가장 많은 블록의 수를 가진 그룹을 찾는 함수.
 -일반 블록에 대해서만 진행. (무지개는 어떤 블록이든 함께 할 수 있기때문)
 -무지개 블록은 방문표시를 x -> 따라서 visit을 따로 표시해줄 임시 백터 사용.
 -visit백터를 통해서 이미 방문한 위치인지를 표시 -> 무지개 블록, 검정 블록에 대해서는 실행하지 않는다. (무지개 블록은 언제나 방문할 수 있기때문)
 -bfs를 이용해서 인접한 블록중에서 같은 수의 일반 블록, 무지개 블록의 경우에 계속 넓혀가면서 인접한 칸을 찾아간다.
 -인접한 블록들을 모두 찾았다면, 조건에 맞게 삭제해야하는 블록 그룹을 갱신한다.
 
Remove()
 -Find_group()에서 찾는 그룹의 모든 블록을 삭제 -> 빈칸이므로 -2로 표시. 
 
Gravity()
 -검정 블록을 제외한 모든 블록들을 가장 아래칸으로 움직이는 함수.
 -열을 기준으로 진행.
 -가장 위에 있는 행부터 실행하며, 해당 열의 모든 행에 대해서 탐색
 -빈 칸과 블록이 있는 칸의 수를 표시하면서 진행, 만약 검정 블록을 만난다면 검정 블록 위에있는 블록들을 모두 검정 블록을 기준으로 아래로 내린다.
 -만약 중간에 검정 블록이 없다면 가장 마지막 칸을 기준으로 블록들을 아래로 내린다.
 -검정 블록을 만나거나 마지막 칸까지 왔지만 빈 칸이 없다면 블록들을 내리지 않는다.
 
 
Rotation()
 -반시계 방향으로 회전하는 함수.


*/


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
            // ¹Ý½Ã°è¹æÇâ 90µµ
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
