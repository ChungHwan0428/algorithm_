#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

int n, a, b;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> a >> b;

    int left = a - 1, right = b - 1;

    if (left + right + 1 > n) {
        cout << -1;
        return 0;
    }

    if (left == 0 && right == 0) {
        for (int i = 0; i < n; i++) {
            cout << 1 << " ";
        }
    }
    else if (left == 0) {
        cout << b << " ";
        for (int i = 0; i < n-b; i++) {
            cout << 1 << " ";
        }
        for (int i = b-1; i >= 1; i--) {
            cout << i << " ";
        }
    }
    else if (right == 0) {
        cout << 1 << " ";
        for (int i = 0; i < n - a; i++) {
            cout << 1 << " ";
        }
        for (int i = 2; i <= a; i++) {
            cout << i << " ";
        }
    }
    else {
        int temp = n - left - right - 1;
        cout << 1 << " ";
        for (int i = 0; i < temp; i++)
            cout << 1 << " ";
        if (left >= right) {
            for (int i = 2; i <= left + 1; i++) {
                cout << i << " ";
            }
            for (int i = right; i >= 1; i--) {
                cout << i << " ";
            }
        }
        else {
            for (int i = 2; i <= left; i++) {
                cout << i << " ";
            }
            for (int i = right +1; i >= 1; i--) {
                cout << i << " ";
            }
        }
    }

    return 0;
}