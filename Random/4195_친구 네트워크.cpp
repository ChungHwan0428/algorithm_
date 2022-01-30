#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, total = 1;

map<string, int>m;
vector<int>parent;
vector<int>cnt;

int find_parent(int node) {

    if (parent[node] == node)
        return node;
    else {
        return find_parent(parent[node]);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc;
    string a, b;

    cin >> tc;

    for (int i = 0; i < tc; i++) {
        cin >> n;
        total = 1;
        m.clear();
        parent.clear();
        parent.resize(200001);
        cnt.clear();
        cnt.resize(200001);

        for (int j = 0; j < n; j++) {
            cin >> a >> b;
            if (m[a] == 0 && m[b] == 0) {
                m[a] = total;
                m[b] = total;
                parent[total] = total;
                cnt[total] = 2;
                total++;
                cout << 2 << "\n";
            }
            else if (m[a] == 0 && m[b] != 0) {
                int temp = find_parent(m[b]);
                m[a] = temp;
                cnt[temp]++;
                cout << cnt[temp] << "\n";
            }
            else if (m[a] != 0 && m[b] == 0) {
                int temp = find_parent(m[a]);
                m[b] = temp;
                cnt[temp]++;
                cout << cnt[temp] << "\n";
            }
            else if (m[a] != 0 && m[b] != 0) {
                int temp1 = find_parent(m[a]), temp2 = find_parent(m[b]);
                if (temp1 == temp2) {
                    cout << cnt[temp1] << "\n";
                }
                else {
                    parent[temp2] = temp1;
                    cnt[temp1] += cnt[temp2];
                    cout << cnt[temp1] << "\n";
                }
            }
        }
    }

    return 0;
}