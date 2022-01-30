#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <queue>

#define MAX pow(2,31)

using namespace std;

int n, k;

vector<int>v;
map<int, int>m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> k >> n;

    v.resize(k);

    priority_queue<int>pq;

    for (int i = 0; i < k; i++) {
        cin >> v[i];
        pq.push(-v[i]);
    }

    int s, cnt = 0;
    int answer = 0;

    while (!pq.empty()) {
        s = -pq.top();
        pq.pop();

        if (pq.empty())
            cnt++;
        else {
            if (s == -pq.top())
                continue;
            else
                cnt++;
        }

        if (cnt == n) {
            answer = s;
            break;
        }

        for (int i = 0; i < k; i++) {
            long long kk = (long long)v[i] * (long long)s;
            if (kk >= MAX)
                continue;

            pq.push(-(v[i] * s));

        }

    }

    cout << answer;

    return 0;
}