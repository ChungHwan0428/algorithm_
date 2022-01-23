#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct node {
    string a, b;
};

int n, q;

map<string, node>m;
map<string, double>p;

void sol(string start, string end) {

    int s_hour = stoi(m[start].b.substr(0, 2)), s_min = stoi(m[start].b.substr(3, 2));
    int e_hour = stoi(m[end].a.substr(0, 2)), e_min = stoi(m[end].a.substr(3, 2));

    int ans_hour, ans_min, total;

    if (s_hour > e_hour) {
        e_hour += 24;
    }

        if (s_min > e_min) {
            ans_hour = e_hour - s_hour - 1;
            ans_min = abs(s_min - e_min - 60);
        }
        else {
            ans_hour = e_hour - s_hour;
            ans_min = abs(s_min - e_min);
        }


    total = ans_min + (ans_hour * 60);

    cout << fixed;
    cout.precision(10);
    cout << ((double)(abs(p[end] - p[start]))* 60) / (double)total <<"\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> q;

    string a, b, c;

    p["Seoul"] = 0;
    p["Yeongdeungpo"] = 9.1;
    p["Anyang"] = 23.9;
    p["Suwon"] = 41.5;
    p["Osan"] = 56.5;
    p["Seojeongri"] = 66.5;
    p["Pyeongtaek"] = 75.0;
    p["Seonghwan"] = 84.4;
    p["Cheonan"] = 96.6;
    p["Sojeongni"] = 107.4;
    p["Jeonui"] = 114.9;
    p["Jochiwon"] = 129.3;

    p["Bugang"] = 139.8;
    p["Sintanjin"] = 151.9;
    p["Daejeon"] = 166.3;
    p["Okcheon"] = 182.5;
    p["Iwon"] = 190.8;
    p["Jitan"] = 196.4;
    p["Simcheon"] = 200.8;
    p["Gakgye"] = 204.6;
    p["Yeongdong"] = 211.6;
    p["Hwanggan"] = 226.2;
    p["Chupungnyeong"] = 234.7;
    p["Gimcheon"] = 253.8;

    p["Gumi"] = 276.7;
    p["Sagok"] = 281.3;
    p["Yangmok"] = 289.5;
    p["Waegwan"] = 296.0;
    p["Sindong"] = 305.9;
    p["Daegu"] = 323.1;
    p["Dongdaegu"] = 326.3;
    p["Gyeongsan"] = 338.6;
    p["Namseonghyeon"] = 353.1;
    p["Cheongdo"] = 361.8;
    p["Sangdong"] = 372.2;
    p["Miryang"] = 381.6;

    p["Samnangjin"] = 394.1;
    p["Wondong"] = 403.2;
    p["Mulgeum"] = 412.4;
    p["Hwamyeong"] = 421.8;
    p["Gupo"] = 425.2;
    p["Sasang"] = 430.3;
    p["Busan"] = 441.7;

    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c;
        m[a] = { b,c };
    }

    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        sol(a, b);
    }

    return 0;
}