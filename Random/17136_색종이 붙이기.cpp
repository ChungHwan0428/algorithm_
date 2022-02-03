#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int total = 0, answer = 99999999, tt = 0;

vector<int>cnt;
vector<vector<int>>v;
vector<vector<pair<int,int>>>where;

bool func(int x, int y, int len) {

    if (cnt[len] <= 0)
        return false;

    int nx = x + len - 1, ny = y + len - 1;

    if (nx >= 10 || ny >= 10)
        return false;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (v[x+i][y+j] == 0)
                return false;
        }
    }
    return true;
}

void check() {

    where.clear();
    where.resize(6);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (v[i][j] == 1) {
                for (int k = 5; k >=1; k--) {
                    if (func(i, j, k)) {
                        where[k].push_back({ i,j });
                        break;
                    }
                }
            }
        }
    }
}

void Remove(int x, int y, int len) {

    cnt[len]--;
    total -= len * len;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            v[x + i][y + j] = 0;
        }
    }

}

void Recover(int x, int y, int len) {

    cnt[len]++;
    total += len * len;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            v[x + i][y + j] = 1;
        }
    }

}

void sol(int x,int y) {

    if (y >= 10) {
        x++, y = 0;
    }

    if (x == 10) {
        if (total == 0)
            answer = min(answer, tt);
        return;
    }

    if (v[x][y] == 0) {
        sol(x, y + 1);
        return;
    }

    for (int i = 1; i <= 5; i++) {
        if (func(x, y, i)) {
            tt++;
            Remove(x, y, i);
            sol(x, y + 1);
            tt--;
            Recover(x, y, i);
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cnt.resize(6, 5);
    v.resize(10, vector<int>(10));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> v[i][j];
            if (v[i][j] == 1)
                total++;
        }
    }

    if (total == 0) {
        cout << 0;
        return 0;
    }

    sol(0, 0);

    if (answer == 99999999)
        cout << -1;
    else
        cout << answer;

   /*
   while (true) {


        if (temp == 1) {
            temp = 0;
        }
        else {
            if (total == 0) {
                int answer = 0;
                for (int i = 1; i <= 5; i++) {
                    answer += (5 - cnt[i]);
                }
                cout << answer;
                break;
            }
            else {
                cout << -1;
                break;
            }
        }

        check();
 
        for (int i = 5; i >= 1; i--) {
            if (cnt[i] <= 0) {
                continue;
            }
            for (int j = 0; j < where[i].size(); j++) {
                Remove(where[i][j].first, where[i][j].second, i);
                temp = 1;
                break;
            }
            if (temp == 1)
                break;
        }
    }
    */

    return 0;
}