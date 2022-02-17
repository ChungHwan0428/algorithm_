#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include<string>

using namespace std;

int n, k, max_;

vector<string>v;
vector<int>size_;
vector<vector<int>>re;
vector<vector<long long>>dp;

void Find_remain(int node, int remain) {

	int	temp;

	temp = remain;

	for (int i = 0; i < size_[node]; i++) {
		temp = temp * 10 + v[node][i] - '0';
		temp = temp % k;
	}

	re[remain][node] = temp;

	return;
}

long long sol(int state, int remain) {

	int temp ;

	if (dp[state][remain] != -1)
		return dp[state][remain];

	if (state == max_) {
		if (remain == 0)
			dp[state][remain] = 1;
		else
			dp[state][remain] = 0;

		return dp[state][remain];
	}

	dp[state][remain] = 0;

	for (int i = 0; i < n; i++) {
		temp = 1 << i;
		if ((state & temp) == temp)
			continue;
		
		int ns = state | temp, nremain = re[remain][i];
		
		dp[state][remain] += sol(ns, nremain);

	}

	return dp[state][remain];
}

long long gcd(long long a, long long b) {

	if (a % b == 0)
		return b;
	else
		return gcd(b, a % b);

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	max_ = (1 << n) - 1;

	v.resize(n);
	size_.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> v[i];
		size_[i] = v[i].size();
	}

	cin >> k;

	dp.resize((1 << n), vector<long long>(k, -1));
	re.resize(k, vector<int>(n));

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++)
			Find_remain(j, i);
	}

	sol(0, 0);

	if (dp[0][0] == 0) {
		cout << "0/1";
		return 0;
	}

	long long temp1 = 1;

	for (int i = 1; i <= n; i++) {
		temp1 = temp1 * i;
	}

	long long temp = gcd(temp1, dp[0][0]);

	cout << dp[0][0] / temp << "/" << temp1 / temp;

	return 0;

}
