#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, q;

vector<pair<int, pair<int, int>>>v;
vector<int>parent;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> q;

    v.resize(n + 1);
    parent.resize(n + 1);

    int a, b, c;

    v[0] = { 2000000000,{2000000000,2000000000} };

    for (int i = 1; i <= n; i++) {
        cin >> a >> b >> c;
        v[i] = { a,{b,i} };
    }

    sort(v.begin(), v.end());

    int low = v[0].first, high = v[0].second.first, p = 1;
    parent[v[0].second.second] = 1;

    for (int i = 1; i < n; i++) {
        if (v[i].first <= high) {
            if (v[i].second.first <= high) {
                parent[v[i].second.second] = p;
            }
            else {
                high = v[i].second.first;
                parent[v[i].second.second] = p;
            }
        }
        else {
            p++;
            parent[v[i].second.second] = p;
            low = v[i].first, high = v[i].second.first;
        }
    }

    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        if (parent[a] == parent[b])
            cout << 1 << "\n";
        else
            cout << 0 << "\n";
    }

    return 0;
}