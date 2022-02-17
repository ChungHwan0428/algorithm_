#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;

vector<vector<vector<long long>>>dp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int l, r;

    cin >> n >> l >> r;

    dp.resize(n+1, vector<vector<long long>>(n + 1, vector<long long>(n + 1)));

    dp[1][1][1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= r; j++) {
            for (int k = 1; k <= l; k++) {
                dp[i][k][j] = dp[i - 1][k][j] * (i - 2) + dp[i - 1][k - 1][j] + dp[i - 1][k][j - 1];
                dp[i][k][j] %= 1000000007;
            }
        }
    }

    cout << dp[n][l][r];

    return 0;
}