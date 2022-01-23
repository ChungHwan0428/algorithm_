#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int cnt = 0;

struct node {
    int start, what, end;
};

map<int, int>m;
map<int, node>mm;
map<int, int>strong;
map<int, int>weak;

vector<vector<vector<int>>>v;
vector<vector<vector<int>>>rv;
vector<int>root;

void Insert(int node, int what) {
    
    int start, k;

    if (what == 0) {
        queue<int>q;
        q.push(node);
        weak[node] = 1;

        while (!q.empty()) {
            start = q.front();
            q.pop();

            for (int i = 0; i < v[start][0].size(); i++) {
                k = v[start][0][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }

            for (int i = 0; i < v[start][1].size(); i++) {
                k = v[start][1][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }
        }
    }
    else {
        queue<int>q;
        q.push(node);
        strong[node] = 1;

        while (!q.empty()) {
            start = q.front();
            q.pop();

            for (int i = 0; i < v[start][0].size(); i++) {
                k = v[start][0][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }

            for (int i = 0; i < v[start][1].size(); i++) {
                k = v[start][1][i];
                if (strong[k] == 1)
                    continue;
                
                if (weak[k] == 1) {
                    weak[k] = 0;
                }

                strong[k] = 1;
                q.push(k);

            }
        }
    }

}

void Insert2(int node, int what) {

    int start, k;

    if (what == 0) {
        queue<int>q;
        q.push(node);
        weak[node] = 1;

        while (!q.empty()) {
            start = q.front();
            q.pop();

            for (int i = 0; i < v[start][0].size(); i++) {
                k = v[start][0][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }

            for (int i = 0; i < v[start][1].size(); i++) {
                k = v[start][1][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }
        }
    }
    else {
        queue<int>q;
        q.push(node);
        weak[node] = 1;

        while (!q.empty()) {
            start = q.front();
            q.pop();

            for (int i = 0; i < v[start][0].size(); i++) {
                k = v[start][0][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }

            for (int i = 0; i < v[start][1].size(); i++) {
                k = v[start][1][i];
                if (strong[k] == 1 || weak[k] == 1)
                    continue;

                weak[k] = 1;
                q.push(k);

            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int o, e;

    cin >> o >> e;

    int a, b, c;
    string d;

    v.push_back(vector<vector<int>>(2, vector<int>()));
    rv.push_back(vector<vector<int>>(2, vector<int>()));

    for (int i = 1; i <= o; i++) {
        cin >> a >> d;
        cnt++;
        m[a] = cnt;
        v.push_back(vector<vector<int>>(2,vector<int>()));
        rv.push_back(vector<vector<int>>(2, vector<int>()));
        if (d == "ROOT") {
            root.push_back(m[a]);
            strong[m[a]] = 1;
        }
    }

    for (int i = 0; i < e; i++) {

        cin >> d;

        if (d == "MADE") {
            cin >> a >> d;
            cnt++;
            m[a] = cnt;
            v.push_back(vector<vector<int>>(2, vector<int>()));
            rv.push_back(vector<vector<int>>(2, vector<int>()));
            if (d == "ROOT") {
                root.push_back(m[a]);
                strong[m[a]] = 1;
            }
        }
        else if (d == "ADD") {
            cin >> a >> b >> d >> c;
            if (d == "->") {
                mm[a] = { m[b],0,m[c] };
                v[m[b]][0].push_back(m[c]);
                rv[m[c]][0].push_back(m[b]);
                if(strong[m[b]]==1)
                    Insert(m[c], 0);
                else if (weak[m[b]] == 1) {
                    Insert2(m[c], 0);
                }
            }
            else {
                mm[a] = { m[b],1,m[c] };
                v[m[b]][1].push_back(m[c]);
                rv[m[c]][1].push_back(m[b]);
                if(strong[m[b]]==1)
                   Insert(m[c], 1);
                else if (weak[m[b]] == 1) {
                    Insert2(m[c], 1);
                }
            }
        }
        else if (d == "REMOVE") {
            cin >> a;
            for (int j = 0; j < v[mm[a].start][mm[a].what].size(); j++) {
                if (v[mm[a].start][mm[a].what][j] == mm[a].end) {
                    v[mm[a].start][mm[a].what][j] = -1;
                    rv[mm[a].start][mm[a].what][j] = -1;
                    break;
                }
            }
        }
        else if (d == "M"){
            cout << strong.size() << "\n";
        }
        else {
            cout << strong.size() + weak.size()<<"\n";
        }
    }

    return 0;
}