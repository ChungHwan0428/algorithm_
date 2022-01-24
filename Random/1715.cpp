#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

priority_queue<long long>pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long answer = 0;

    int n;

    cin >> n;

    int a;

    for (int i = 0; i < n; i++) {
        cin >> a;
        pq.push(-a);
    }

    if (n == 1) {
        cout << 0;
        return 0;
    }

    long long n1, n2;

    while (!pq.empty()) {
        n1 = pq.top();
        pq.pop();
        n2 = pq.top();
        pq.pop();

        answer += n1 + n2;

        if (pq.empty())
            break;
        else
            pq.push(n1 + n2);
    }

    cout << -answer;

    return 0;
}