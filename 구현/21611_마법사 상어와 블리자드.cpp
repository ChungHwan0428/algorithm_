#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, m, here;

vector<int>v;
vector<int>v2;
vector<int>answer;
vector<vector<int>>tmp;

int x_[4] = { 1,0,-1,0 };
int y_[4] = { 0,-1,0,1 };

void func(int x, int y, int dir, int len) {

    if (len == 0)
        return;

    x += x_[dir];
    y += y_[dir];

    for (int i = 0; i < len; i++) {
        v[here] = tmp[x][y];
        here++;
        x += x_[dir];
        y += y_[dir];
    }

    x -= x_[dir];
    y -= y_[dir];

    dir = (dir + 1) % 4;

    x += x_[dir];
    y += y_[dir];

    for (int i = 0; i < len; i++) {
        v[here] = tmp[x][y];
        here++;
        x += x_[dir];
        y += y_[dir];
    }

    x -= x_[dir];
    y -= y_[dir];

    dir = (dir + 1) % 4;

    func(x, y, dir, len - 1);
    
}

void func2() {

    v2[0] = 1;

    int idx = 1, temp = 2;

    while (idx < v2.size()) {
        v2[idx] = v2[idx-1] + temp * 3 + temp + 1;
        temp += 2;
        idx++;
    }

}

void sol2() {

    int temp = 0;

    for (int i = 1; i < n * n; i++) {
        if (i + temp >= n * n) {
            for (int j = i; j < n * n; j++)
                v[j] = 0;
            break;
        }

        while (i + temp < n * n && v[i + temp] == -1) {
            temp++;
        }

        if (i + temp >= n * n) {
            for (int j = i; j < n * n; j++)
                v[j] = 0;
            break;
        }

        v[i] = v[i + temp];
    }

}

bool sol3() {

    int prev = 0, cnt = 1;
    bool re = false;

    for (int i = 1; i < n * n; i++) {
        if (v[i] == 0)
            break;

        if (v[prev] == v[i]) {
            cnt++;
        }
        else {
            if (cnt >= 4) {
                re = true;
                answer[v[prev]] += cnt;
                for (int j = prev; j < prev + cnt; j++)
                    v[j] = -1;
            }
            cnt = 1;
            prev = i;
        }
    }

    if (cnt >= 4) {
        re = true;
        answer[v[prev]] += cnt;
        for (int j = prev; j < prev + cnt; j++)
            v[j] = -1;
    }

    return re;

}

void sol4() {

    int prev = 1, cnt = 1, here_ = 1;

    vector<int>temp(n * n);

    if (v[1] == 0)
        return;

    for (int i = 2; i < n * n; i++) {
        if (v[i] == 0 ) {
            temp[here_] = cnt;
            if (here_ + 1 >= n * n)
                break;
            temp[here_ + 1] = v[prev];
            break;
        }

        if (here_ >= n * n)
            break;

        if (v[prev] == v[i]) {
            cnt++;
        }
        else {

            temp[here_] = cnt;
            if (here_ + 1 >= n * n)
                break;
            temp[here_ + 1] = v[prev];

            here_ += 2;

            prev = i;
            cnt = 1;
        }
    }

    if (v[n * n - 1] != 0) {
        if (here_ < n * n) {
            temp[here_] = cnt;
            if (here_ + 1 < n * n)
                temp[here_ + 1] = v[prev];
        }
    }

    v = temp;

}

void sol(int d, int s) {

    if (d == 1) {
        for (int i = 0; i < s; i++) {
            if (v[v2[i] + i * 6 + 6] == 0)
                break;
            v[v2[i] + i * 6 + 6] = -1;
        }

        sol2();

        while (true) {
            if (sol3())
                sol2();
            else
                break;

        }

    }
    else if (d == 2) {
        for (int i = 0; i < s; i++) {
            if (v[v2[i]+i*2+2] == 0)
                break;
            v[v2[i] + i * 2 + 2] = -1;
        }

        sol2();

        while (true) {
            if (sol3())
                sol2();
            else
                break;
        }


    }
    else if (d == 3) {
        for (int i = 0; i < s; i++) {
            if (v[v2[i]] == 0)
                break;
            v[v2[i]] = -1;
        }
        sol2();
        while (true) {
            if (sol3())
                sol2();
            else
                break;
        }
    }
    else {
        for (int i = 0; i < s; i++) {
            if (v[v2[i] + i * 4 + 4] == 0)
                break;
            v[v2[i] + i * 4 + 4] = -1;
        }
        sol2();
        while (true) {
            if (sol3())
                sol2();
            else
                break;
        }
    }

    sol4();

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b;

    cin >> n >> m;

    v2.resize((n - 1) / 2);
    tmp.resize(n, vector<int>(n));
    answer.resize(4);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp[i][j];
        }
    }

    v.resize(n * n);

    for (int i = 0; i < n; i++) {
        v[i] = tmp[0][i];
    }

    here = n;

    func(0, n-1, 0, n-1);

    reverse(v.begin(), v.end());

    func2();

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        sol(a, b);

    }

    cout << answer[1] + answer[2] * 2 + answer[3] * 3;

    return 0;
}