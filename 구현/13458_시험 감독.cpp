/*
int 자료형을 넘어간다. long long으로 문제를 해결해야함...
주 감독관을 무조건 들어가므로 주 감독관이 감독할 수 있는 인원을 제외하고 남은 인원수 / 부 감독관이 감독가능한 인원수를 해서 구해준다.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

long long n, b, c, answer = 0;

vector<long long>v;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long temp;

    cin >> n;

    v.resize(n);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    cin >> b >> c;

    for (int i = 0; i < n; i++) {
        temp = v[i];
        temp -= b;
        answer++;
        if (temp > 0) {
            if (temp % c == 0)
                answer += (temp / c);
            else
                answer += (temp / c) + 1;
        }
    }

    cout << answer;

    return 0;
}
