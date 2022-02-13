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