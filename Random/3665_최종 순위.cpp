#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, m;

vector<int>v;
vector<int>next_v;
vector<int>answer;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc, a, b, ans;

    cin >> tc;

    for (int kk = 0; kk < tc; kk++) {

        cin >> n;

        ans = 0;
        v.clear();
        v.resize(n + 1);
        next_v.clear();
        answer.clear();
        answer.resize(n + 1);

        for (int i = n; i >= 1; i--) {
            cin >> a;
            v[a] = i;
        }

        cin >> m;

        next_v = v;

        for (int i = 1; i <= m; i++) {
            cin >> a >> b;
            if (v[a] > v[b]) {
                next_v[a]--;
                next_v[b]++;
            }
            else {
                next_v[a]++;
                next_v[b]--;
            }
        }

        for (int i = 1; i <= n; i++) {
            if (next_v[i] <= 0 || answer[next_v[i]] != 0) {
                cout << "IMPOSSIBLE";
                ans++;
                break;
            }
            answer[next_v[i]] = i;
        }

        if (ans == 0) {
            for (int i = n; i >= 1; i--) {
                cout << answer[i] << " ";
            }
        }

        cout << "\n";

    }

    return 0;
}