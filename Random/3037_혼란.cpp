#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int n, c;

vector<vector<int>>dp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> c;

    dp.resize(1001, vector<int>(10001));

    dp[1][0] = 1;
        
    for (int i = 2; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= min(10000,i*(i-1)/2); j++) {
            int temp = j - i;
            if (temp < 0)
                dp[i][j] = (dp[i][j - 1] + dp[i - 1][j])%1000000007;
            else
                dp[i][j] = (dp[i][j - 1] + (1000000007 + dp[i - 1][j] - dp[i - 1][j - i]) % 1000000007) % 1000000007;

        }
    }


    cout << dp[n][c];


    return 0;
}