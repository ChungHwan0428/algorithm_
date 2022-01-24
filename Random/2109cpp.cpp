#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, max_ = 0, answer = 0;

priority_queue<pair<int,int>>pq;
vector<int>v;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    int a, b;

    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        pq.push({ a,-b });
        max_ = max(max_, b);
    }

    v.resize(max_ + 1);

    int d, p;

    while (!pq.empty()) {
        p = pq.top().first;
        d = -pq.top().second;
        pq.pop();

        if (v[d] == 0) {
            answer += p;
            v[d] = 1;
        }
        else {
            for (int i = d - 1; i >= 1; i--) {
                if (v[i] == 0) {
                    answer += p;
                    v[i] = 1;
                    break;
                }
            }
        }
    }

    cout << answer;

    return 0;
}