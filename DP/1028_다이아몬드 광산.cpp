#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int r, c, answer = 0;

int x_[4] = { -1,-1,1,1 };
int y_[4] = { -1,1,-1,1 };

vector<vector<vector<int>>>dp;
vector<vector<int>>v;
vector<vector<int>>visit;

void func(int a, int b) {

	int x, y, nx, ny, dist, dir;

	visit[a][b] = 1;
	
	queue<pair<int, pair<int, pair<int, int>>>>q;

	q.push({ 1,{2,{a,b}} });
	q.push({ 1,{3,{a,b}} });

	while (!q.empty()) {
		x = q.front().second.second.first;
		y = q.front().second.second.second;
		dist = q.front().first;
		dir = q.front().second.first;

		q.pop();

		if (dp[x][y][dir] != -1)
			continue;

		nx = x + x_[dir];
		ny = y + y_[dir];

		if (nx < 0 || ny < 0 || nx >= r || ny >= c || v[nx][ny] == 0) {
			for (int i = 1; i <= dist; i++) {
				nx = nx - x_[dir];
				ny = ny - y_[dir];
				dp[nx][ny][dir] = i;
			}
			continue;
		}
		
		q.push({ dist + 1,{dir,{nx,ny}} });
	}
}

void sol(int a, int b) {
	
	int ax, ay, bx, by;

	int min_ = min(dp[a][b][2], dp[a][b][3]);

	if (min_ == 1)
		answer = max(answer, min_);
	else {
		for (int i = min_ - 1; i >= 1; i--) {
			ax = a + x_[2] * i, ay = b + y_[2] * i;
			bx = a + x_[3] * i, by = b + y_[3] * i;
			if (min(dp[ax][ay][3], dp[bx][by][2]) >= i+1) {
				answer = max(answer, i + 1);
				break;
			}
		}
	}
	

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> r >> c;

	dp.resize(r, vector<vector<int>>(c, vector<int>(4, -1)));
	v.resize(r, vector<int>(c));
	visit.resize(r, vector<int>(c));

	string a;

	for (int i = 0; i < r; i++) {
		cin >> a;
		for (int j = 0; j < c; j++) {
			v[i][j] = a[j] - '0';
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (visit[i][j] == 0 && v[i][j] == 1)
				func(i, j);
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (v[i][j] == 1)
				sol(i, j);
		}
	}

	cout << answer;

	return 0;
}
