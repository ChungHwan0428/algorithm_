#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;
    
int n, q, cnt = 0;

vector<int>v;
vector<pair<int,int>>vv;
vector<vector<int>>dp;

void sol(int start) {

    int temp = start, total = 0;

    if (vv[start].first != -1) {
        for (int i = vv[temp].second; i < dp[vv[temp].first].size(); i++) {
            dp[cnt].push_back(dp[vv[temp].first][i]);
        }
    }
    else {
        while (true) {

            if (vv[temp].first != -1) {
                if (vv[temp].first == cnt) {
                    dp[cnt].push_back(temp);
                    return;
                }
                else {
                    for (int i = vv[temp].second; i < dp[vv[temp].first].size() ; i++) {
                        dp[cnt].push_back(dp[vv[temp].first][i]);
                    }
                    return ;
                }
            }

            dp[cnt].push_back(temp);
            vv[temp] = { cnt,total };
            total++;
            temp = v[temp];
        }
    }

}

void sol2(int a, int b) {
    
    int total = dp[vv[b].first].size() - 1;

    if()

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b;

    cin >> n;

    v.resize(n + 1);
    vv.resize(n + 1, { -1,-1 });
    dp.resize(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> v[i];

    cin >> q;

    for (int i = 1; i <= n; i++) {
        sol(i);
        cnt++;
    }

    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        sol2(a, b);
    }


    return 0;
}