#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int n, m, answer = 51;

vector<int>visit;
vector <vector<int>>v;

void sol() {

    int check = 0, cnt = 0;

    for (int i = 0; i < m; i++) {
        check = 0;
        for (int j = 0; j < v[i].size(); j++) {
            if (visit[v[i][j]] == 1) {
                check = 1;
                break;
            }
        }

        if (check == 1) {
            for (int j = 0; j < v[i].size(); j++) {
                visit[v[i][j]] = 1;
            }
        }
        else {
            cnt++;
        }
    }

    answer = min(answer, cnt);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b;

    cin >> n >> m;
    visit.resize(n + 1);
    v.resize(m);

    cin >> a;

    for (int i = 0; i < a; i++) {
        cin >> b;
        visit[b]++;
    }

    for (int i = 0; i < m; i++) {
        cin >> a;
        v[i].resize(a);
        for (int j = 0; j < a; j++) {
            cin >> v[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        sol();
    }

    cout << answer;

    return 0;
}