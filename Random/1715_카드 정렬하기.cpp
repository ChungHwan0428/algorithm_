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

//Greedy algorithm
//작은 것들끼리 합치는 것이 가장 효율적이므로 priority_queue 사용해서 가장 작은 두 카드를 합치고, 다시 우선순위 큐에 넣어준다.
//이 과정을 마지막 하나의 카드가 될 때까지 반복한다.
//처음에 1개의 카드만 주어진다면 합칠 필요가 없으므로 0 출력.
