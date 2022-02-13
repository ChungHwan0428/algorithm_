#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, answer = 0;

vector<pair<int, int>>v;
vector<int>dp;

void func(int start) {
    
    int nnode = start + v[start].first, ntotal;

    if (nnode < n) {
        ntotal = dp[start] + v[start].second;
        for (int i = nnode; i < n; i++) {
            if (dp[i] < ntotal) {
                dp[i] = ntotal;
                answer = max(answer, ntotal);
                func(i);
            }
        }
    }
    else if (nnode == n) {
        ntotal = dp[start] + v[start].second;
        answer = max(answer, ntotal);
    }


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    v.resize(n);
    dp.resize(n + 1);

    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    for (int i = 0; i < n; i++) {
        if(dp[i]==0)
            func(i);
    }

    cout << answer;

    return 0;
}