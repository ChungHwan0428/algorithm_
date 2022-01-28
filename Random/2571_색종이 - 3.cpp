#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, answer = 0;

vector<vector<int>>v;
vector<vector<pair<int,int>>>len;

void sol(int h, int start, int l, int total_h) {

    int ns = start, ne = start + l - 1, ps, pe;

    if (h+1 == 100)
        return;

    for (int i = 0; i < len[h + 1].size(); i++) {
        ps = len[h + 1][i].first;
        pe = len[h + 1][i].first + len[h + 1][i].second - 1;

        if (pe < ns)
            continue;
        if (ne < ps)
            continue;

        if (ps <= ns) {
            if (pe <= ne) {
                answer = max(answer, (pe - ns + 1) * (total_h + 1));
                sol(h + 1, ns, pe - ns + 1, total_h + 1);
            }
            else {
                answer = max(answer, (ne - ns + 1) * (total_h + 1));
                sol(h + 1, ns, ne - ns + 1, total_h + 1);
            }
        }
        else {
            if (pe <= ne) {
                answer = max(answer, (pe - ps + 1) * (total_h + 1));
                sol(h + 1, ps, pe - ps + 1, total_h + 1);
            }
            else {
                answer = max(answer, (ne - ps + 1) * (total_h + 1));
                sol(h + 1, ps, ne - ps + 1, total_h + 1);
            }
        }

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    v.resize(100, vector<int>(100));
    len.resize(100);

    int a, b;

    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                v[b + j][a + k] = 1;
            }
        }
    }

    for (int i = 0; i < 100; i++) {
        int temp = 0;
        for (int j = 0; j < 100; j++) {
            if (v[i][j] == 1) {
                temp++;
            }
            else {
                if (temp != 0) {
                    len[i].push_back({ j - temp,temp });
                    temp = 0;
                }
            }
        }
        if (temp != 0) {
            len[i].push_back({ 100 - temp,temp });
        }
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < len[i].size(); j++) {
            answer = max(answer, (len[i][j].second));
            sol(i, len[i][j].first, len[i][j].second, 1);
        }
    }

    cout << answer;

    return 0;
}