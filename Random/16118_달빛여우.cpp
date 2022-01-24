#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, m, answer = 0;

vector<vector<pair<int,int>>>v;
vector<int>fox;
vector<vector<double>>wolf;

void sol1() {

    priority_queue<pair<int, int>>pq;
    int node, dist, nnode, ndist;

    fox[1] = 0;

    pq.push({ 0,1 });

    while (!pq.empty()) {
        dist = -pq.top().first;
        node = pq.top().second;

        pq.pop();

        if (fox[node] < dist)
            continue;

        for (int i = 0; i < v[node].size(); i++) {
            nnode = v[node][i].first;
            ndist = dist + v[node][i].second;

            if (fox[nnode] > ndist) {
                fox[nnode] = ndist;
                pq.push({ -ndist,nnode });
            }
        }
    }
}

void sol2() {

    priority_queue<pair<double, pair<int,int>>>pq;
    int node, state, nnode, nstate;
    double dist, ndist;

    wolf[1][1] = 0;

    pq.push({ 0,{1,1} });

    while (!pq.empty()) {
        dist = -pq.top().first;
        node = pq.top().second.first;
        state = pq.top().second.second;

        pq.pop();

        if (wolf[node][state] < dist)
            continue;
        
        if (state == 0) {
            for (int i = 0; i < v[node].size(); i++) {
                nnode = v[node][i].first;
                ndist = dist + (double)v[node][i].second * 2;

                if (wolf[nnode][1] > ndist) {
                    wolf[nnode][1] = ndist;
                    pq.push({ -ndist,{nnode,1 } });
                }
            }
        }
        else {
            for (int i = 0; i < v[node].size(); i++) {
                nnode = v[node][i].first;
                ndist = dist + (double)v[node][i].second / 2;

                if (wolf[nnode][0] > ndist) {
                    wolf[nnode][0] = ndist;
                    pq.push({ -ndist,{nnode,0 } });
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    v.resize(n + 1);
    fox.resize(n + 1,900000000);
    wolf.resize(n + 1, vector<double>(2, 900000000));

    int a, b, c;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        v[a].push_back({ b,c });
        v[b].push_back({ a,c });
    }

    sol1();
    sol2();

    for (int i = 1; i <= n; i++) {
        if ((double)fox[i] < min(wolf[i][0], wolf[i][1]))
            answer++;
    }

    cout << answer;

    return 0;
}

//우선순위 큐를 이용한 다익스트라
//여우, 늑대 따로 계산해주고 마지막에 모든 도착지점들마다 여우가 더 빠르다면 total++
//늑대 계산할때는 2개로 나눠서 계산 -> 해당 지점에 2배 빠르게 왔는지 or 2배 느리게 왔는지
//늑대 처음 시작 지점에서 2배 빠르게 온 경우는 0으로 초기화 x -> 이러면 한 바퀴 돌아서 다시 시작지점으로 오는 것이 최단경로를
//만드는 경우가 있기때문에 2배 빠르게 온 경우는 0으로 초기화 x 하지만 2배 느리게 온 경우는 0으로 초기화한다.
