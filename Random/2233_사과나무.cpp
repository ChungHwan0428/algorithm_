#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;

struct node {
    int p, in, out;
};

int n, x1, x2, s1, s2;
string a;

vector<node>parent;
vector<int>m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    cin >> a;

    cin >> x1 >> x2;

    parent.resize(n + 1);

    stack<int>st;

    int temp = 0, total = 1,  here = 0;

    for (int i = 0; i < a.size(); i++) {


        if (a[i] == '0') {
            parent[total] = { here ,i + 1,0 };
            here = total;
            total++;
            if (i == x1 - 1) {
                s1 = here;
            }
            if (i == x2 - 1) {
                s2 = here;
            }
        }
        else {
            if (i == x1 - 1) {
                s1 = here;
            }
            if (i == x2 - 1) {
                s2 = here;
            }
            parent[here].out = i + 1;
            here = parent[here].p;

        }

    }

    m.resize(n + 1);

    temp = s1;

    while (temp!=0) {
        m[temp] = 1;
        temp = parent[temp].p;
    }

    temp = s2;

    while (true) {
        if (m[temp]==1)
            break;
        else {
            temp = parent[temp].p;
        }
    }


    cout << parent[temp].in << " " << parent[temp].out;

    return 0;
}