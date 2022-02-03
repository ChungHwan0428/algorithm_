#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, l, p, answer = 100000;

vector<pair<int, int>>v;

void sol() {

    int cnt, node, oil;

    priority_queue<pair<int, pair<int, int>>>pq;

    pq.push({ 0,{0,p} });

    while (!pq.empty()) {
        node = pq.top().first;
        cnt = pq.top().second.first;
        oil = pq.top().second.second;

        pq.pop();

        if (l - v[node].first <= oil) {
            answer = min(answer,cnt);
            break;
        }

        for (int i = node + 1; i <= n; i++) {
            int temp = v[i].first - v[node].first;
            if (temp > oil)
                continue;

            pq.push({ i,{cnt+1,oil - temp + v[i].second} });

        }


    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    int a, b;

    v.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        v[i] = { a,b };
    }

    cin >> l >> p;

    sort(v.begin(), v.end());

    sol();

    if (answer == 100000)
        cout << -1;
    else
        cout << answer;

    return 0;
}