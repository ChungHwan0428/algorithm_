#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, l, answer=99999999;

vector<pair<int,int>>v;

void sol(int h, int t, int nleft, int nright, int ndir) {


    if (h == n) {
        answer = min(answer, t);
        return;
    }

    int len = v[h+1].first, dir = v[h+1].second;
    int change = l - len;
    
    if (change == 0) {
        sol(h + 1, t, 0, l, dir);
        return;
    }

    int p = t / change, q = t % change;
    
    int left, right;

    if (p % 2 == 0) { //방향 변화 x
        if (dir == 0) {
            left = q, right = q + len;
        }
        else {
            left = l - q - len, right = l - q;
        }
    }
    else { //방향 변화 o
        if (dir == 0) {
            left = l - q - len, right = l - q;
        }
        else {
            left = q, right = q + len;
        }
    }

    if (left > nright) {
        if (dir == 1 && ndir == 1) {
            int temp = nleft;
            if ((left - nright) % 2 == 0) {
                sol(h + 1, t + temp + (left - nright) / 2,left - nleft - (left - nright) / 2, right - nleft - (left - nright) / 2, 1);
            }
            else {
                sol(h + 1, t + temp + (left - nright) / 2 + 1, left - nleft - (left - nright) / 2 - 1, right - nleft - (left - nright) / 2 - 1, 1);
            }
        }
        else if (dir == 1 && ndir == 0) {
            int temp = (left - nright) / 2;
            if ((left - nright) % 2 == 0) {
                sol(h + 1, t + temp , left - temp, right - temp, 1);
            }
            else {
                sol(h + 1, t + temp + 1, left  - temp - 1, right - temp - 1, 1);
            }
        }
        else if (dir == 0 && ndir == 1) {
            sol(h, t + (nleft), 0, nright - nleft, 0);
        }
        else if (dir == 0 && ndir == 0) {
            int temp = l - right;
            if ((left - nright) % 2 == 0) {
                sol(h + 1, t + temp + (left - nright) / 2, l - len - (left - nright) / 2, l - (left - nright) / 2, 0);
            }
            else {
                sol(h + 1, t + temp + (left - nright) / 2 + 1, l - len - (left - nright) / 2 - 1, l - (left - nright) / 2 - 1, 0);
            }
        }
    }
    else if (right < nleft) {
        if (dir == 1 && ndir == 1) {
            int temp = left;
            if ((nleft - right) % 2 == 0) {
                sol(h + 1, t + temp + (nleft - right) / 2, (nleft - right) / 2, (nleft - right) / 2 + len, 0);
            }
            else {
                sol(h + 1, t + temp + (nleft - right) / 2 + 1, (nleft - right) / 2 + 1, (nleft - right) / 2 + len + 1, 0);
            }
        }
        else if (dir == 1 && ndir == 0) {
            sol(h, t + (l - nright), l - (nright - nleft), l, 1);
        }
        else if (dir == 0 && ndir == 1) {
            int temp = (nleft-right) / 2;
            if ((nleft - right) % 2 == 0) {
                sol(h + 1, t + temp , left + temp, right + temp, 0);
            }
            else {
                sol(h + 1, t + temp + 1, left + temp + 1, right + temp + 1, 0);
            }
        }
        else if (dir == 0 && ndir == 0) {
            int temp = l - nright;
            if ((nleft - right) % 2 == 0) {
                sol(h + 1, t + temp + (nleft - right) / 2, left + temp + (nleft - right)/2, right + temp + (nleft - right) / 2, 0);
            }
            else {
                sol(h + 1, t + temp + (nleft - right) / 2 + 1, left + temp + (nleft - right) / 2 + 1, right + temp + (nleft - right) / 2 + 1, 0);
            }
        }
    }
    else {
        sol(h + 1, t, left, right, dir);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> l;

    v.resize(n + 1);

    int a, b;

    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        v[i] = { a,b };
    }

    if (v[1].second == 1) {
        sol(1, 0, l - v[1].first, l, 1);
    }
    else {
        sol(1, 0, 0, v[1].first, 0);
    }

    cout << answer;

    return 0;
}