#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int cnt = 0;

struct node {
    int start, what, end, total_;
};

map<int, int>m;
map<int, node>mm;

vector<vector<vector<int>>>v;
vector<int>root;
vector<vector<int>>total;
vector<int>ans;
vector<int>alive;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    total.resize(400002, vector<int>(2,0));
    ans.resize(400002);
    alive.resize(400002);

    int o, e;

    cin >> o >> e;

    int a, b, c;
    string d;

    v.push_back(vector<vector<int>>(2, vector<int>()));

    for (int i = 1; i <= o; i++) {
        cin >> a >> d;
        cnt++;
        m[a] = cnt;
        alive[m[a]] = 1;
        v.push_back(vector<vector<int>>(2, vector<int>()));
        if (d == "ROOT") {
            root.push_back(m[a]);
        }
    }

    for (int i = 0; i < e; i++) {

        cin >> d;

        if (d == "MADE") {
            cin >> a >> d;
            cnt++;
            m[a] = cnt;
            alive[m[a]] = 1;
            v.push_back(vector<vector<int>>(2, vector<int>()));
            if (d == "ROOT") {
                root.push_back(m[a]);
            }
        }
        else if (d == "ADD") {
            cin >> a >> b >> d >> c;
            if (d == "->") {
                mm[a] = { m[b],0,m[c],total[m[b]][0] };
                v[m[b]][0].push_back(m[c]);
                total[m[b]][0]++;
            }
            else {
                mm[a] = { m[b],1,m[c],total[m[b]][1] };
                v[m[b]][1].push_back(m[c]);
                total[m[b]][1]++;
            }
        }
        else if (d == "REMOVE") {
            cin >> a;
            v[mm[a].start][mm[a].what][mm[a].total_] = -1;
        }
        else if (d == "M") {
            int answer = 0;
            queue<int>q;
            for (int k = 0; k < root.size(); k++) {
                q.push(root[k]);
                ans[root[k]] = 1;
            }

            int node;

            while (!q.empty()) {
                node = q.front();
                q.pop();

                if (ans[node] == -1 || ans[node] == 3)
                    continue;

                if (alive[node] == 0)
                    continue;

                for (int j = 0; j < total[node][1]; j++) {
                    if (v[node][1][j] == -1 || alive[v[node][1][j]] == 0)
                        continue;

                    if (ans[v[node][1][j]] != 1 && ans[v[node][1][j]] != 2) {
                        ans[v[node][1][j]] = 2;
                        q.push(v[node][1][j]);
                    }
                }

                for (int j = 0; j < total[node][0] ; j++) {
                    if (v[node][0][j] == -1 || alive[v[node][0][j]] == 0)
                        continue;

                    if (ans[v[node][0][j]] != 2 && ans[v[node][0][j]] != 1) {
                        ans[v[node][0][j]] = -1;
                    }
                }
            }

            vector<int>temp_alive(400002);

            for (int iter = 0 ; iter < 400002; iter++) {
                if (ans[iter] == 1 || ans[iter] == 2) {
                    answer++;
                    temp_alive[iter] = 1;
                }
            }

            alive = temp_alive;

            cout << answer << "\n";
            ans.clear();
            ans.resize(400002);

        }
        else {
            int answer = 0;
            queue<int>q;
            for (int k = 0; k < root.size(); k++) {
                q.push(root[k]);
                ans[root[k]] = 1;
            }

            int node;

            while (!q.empty()) {
                node = q.front();
                q.pop();

                if (ans[node] == -1)
                    continue;

                if (alive[node] == 0)
                    continue;

                for (int j = 0; j < total[node][1]; j++) {
                    if (v[node][1][j] == -1 || alive[v[node][1][j]] == 0)
                        continue;

                    if (ans[v[node][1][j]] != 1 && ans[v[node][1][j]] != 2 && ans[v[node][1][j]] != 3) {
                        ans[v[node][1][j]] = 2;
                        q.push(v[node][1][j]);
                    }
                }

                for (int j = 0; j < total[node][0]; j++) {
                    if (v[node][0][j] == -1 || alive[v[node][0][j]] == 0)
                        continue;

                    if (ans[v[node][0][j]] != 1 && ans[v[node][0][j]] != 2 && ans[v[node][0][j]] != 3) {
                        ans[v[node][0][j]] = 3;
                        q.push(v[node][0][j]);
                    }
                }
            }
            vector<int>temp_alive(400002);

            for (int iter = 0; iter < 400002; iter++) {
                if (ans[iter] == 1 || ans[iter] == 2 || ans[iter] == 3) {
                    answer++;
                    temp_alive[iter] = 1;
                }
            }
            alive = temp_alive;

            cout << answer << "\n";
            ans.clear();
            ans.resize(400002);

        }
    }

    return 0;
}