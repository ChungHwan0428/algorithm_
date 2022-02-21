/*
다익스트라 + dp

처음 dp 설정시, dp[node] = {min, total} 형식으로 했음.

나중에는 dp[node][min] = total 로 변경.

처음 방식으로 하면 다익스트라 돌리는 경우, min, total 모두 dp에 있는 값보다 크다면 pq에 들어가지 않음. 너무 많은 경우의 수가 pq에 들어감. -> 너무 많은 시간 소요.

나중 방식으로 변경 후, dp[node][min] 값보다 total이 작은 경우면 pq에 들어간다. -> 시간 괜찮.

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, m;

long long answer = 16000000000;

vector<int>price;
vector<vector<pair<int,int>>>v;
vector<vector<long long>>dp;

void Find() {

	priority_queue<pair<long long, pair<int, int>>>pq;

	int min_, node, nmin_, nnode;
	long long total, ntotal;

	pq.push({0 ,{-price[1],1} });

	dp[1][price[1]] = 0;

	while (!pq.empty()) {
		total = -pq.top().first;
		min_ = -pq.top().second.first;
		node = pq.top().second.second;

		pq.pop();

		if (dp[node][min_] < total)
			continue;

		if (node == n) {
			answer = total;
			break;
		}


		for (int i = 0; i < v[node].size(); i++) {
			nnode = v[node][i].first;

			ntotal = total + min_ * v[node][i].second;

			nmin_ = min(price[nnode], min_);

			if (dp[nnode][nmin_] <= ntotal)
				continue;

			dp[nnode][nmin_] = ntotal;
			pq.push({ -ntotal ,{-nmin_, nnode} });

		}

	}



}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int a, b, c;

	cin >> n >> m;

	price.resize(n + 1);
	v.resize(n + 1);
	dp.resize(n + 1, vector<long long>(2501, 16000000000));

	for (int i = 1; i <= n; i++) {
		cin >> price[i];
	}

	for (int i = 1; i <= m; i++) {
		cin >> a >> b >> c;
		v[a].push_back({ b,c });
		v[b].push_back({ a,c });
	}

	Find();

	cout << answer;

	return 0;
}
