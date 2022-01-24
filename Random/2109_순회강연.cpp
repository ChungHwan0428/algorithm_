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

//Greedy algorithm?
//vector v[] -> 해당 순서에 몇 번재 일을 실행했는지(여기서는 그냥 1로 표시만 했지만, 일의 순서를 알아야한다면 몇 번째 일을 했는지 표시한다.)
//우선순위 큐를 사용. 
//가중치가 가장 큰 값일 수록 앞에 오도록 넣는다.
//우선순위 큐에서 하나씩 빼서 해당 day에 이미 일을 했는지 확인 후, 안했다면 해당 day에 했다고 표시를 해주고, 총 가중치의 합을 업데이트한다.
//만약 다른 일을 했다면, 해당 day에서 1일 까지 일을 안한 날을 찾아서 일을 진행시킨다. 만약 모두 일을 했다면 그냥 넘어간다.
