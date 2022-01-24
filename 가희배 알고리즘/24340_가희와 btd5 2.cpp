#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

int r, u, e;

struct node {
    int level;
    int idx, route;
};

struct node2 {
    int level;
    int time, route, cnt;
};

vector<int>len_path;
vector<vector<pair<int,int>>>path;
vector<pair<string,string>>monkey;
vector<vector<node>>ballon;
vector<node2>ballon_info;
vector<int>ballon_cnt;

map<pair<double,pair<int,int>>, int>first_; //시간은 양수
map<pair<double, pair<int, int>>, int>last_; //시간은 음수
map<pair<int,int>, int>strong_; // 레벨은 음수

void sol(double start, double end) {

    int istart = (int)(start * 1000);
    int iend = (int)(end * 1000);

    for (int ii = istart; ii <= iend; ii++) {
        for (int i = ii - 1000; i >= 0; i = i - 1000) {
            for (int j = 0; j < ballon[i].size(); j++) {
                if (len_path[ballon[i][j].route] <= (istart - i) / 1000) {
                    
                    ballon[i][j] = { -1,-1,-1 };

                }
                else {
                    int route_ = ballon[i][j].route, where = (istart - i) / 1000;
                    double dist = (path[route_][where].first * path[route_][where].first + path[route_][where].second * path[route_][where].second);
                    double prev_dist = (path[route_][where - 1].first * path[route_][where - 1].first + path[route_][where - 1].second * path[route_][where - 1].second);

                    first_.erase({ prev_dist, { i - 1000, ballon[i][j].idx } });
                    last_.erase({ prev_dist, { -(i - 1000), ballon[i][j].idx } });
                    strong_.erase({ -ballon[i][j].level, ballon[i][j].idx });

                    first_[{dist, { i, ballon[i][j].idx }}] = 1;
                    last_[{dist, { -i, ballon[i][j].idx }}] = 1;
                    strong_[{-ballon[i][j].level, ballon[i][j].idx}] = 1;
                }
            }
        }

        for (int i = ii ; i >= 0; i = i - 1000) {
            if (monkey[i].first == "" && monkey[i].second == "")
                continue;
            if (monkey[i].second == "FIRST") {
                auto iter = first_.begin();
                int idx_ = iter->first.second.second;
                int le = ballon_info[idx_].level;
                int t_ = ballon_info[idx_].time;
                int indx_ = ballon_info[idx_].cnt;

                if (monkey[i].first == "-") {
                    if (le == 1) {
                        cout << idx_ << " " << i << "\n";
                        first_.erase(first_.begin());
                        ballon[t_][indx_] = { -1,-1,-1 };
                    }
                }
                else if (monkey[i].first == "L1") {
                    if (le <= 2) {
                        cout << idx_ << " " << i << "\n";
                        first_.erase(first_.begin());
                        ballon[t_][indx_] = { -1,-1,-1 };

                    }
                }
                else if (monkey[i].first == "R1") {
                    if (le == 1 || le == 3) {
                        cout << idx_ << " " << i << "\n";
                        first_.erase(first_.begin());
                        ballon[t_][indx_] = { -1,-1,-1 };

                    }
                }
                else if (monkey[i].first == "L1R1") {
                    cout << idx_ << " " << i << "\n";
                    first_.erase(first_.begin());
                    ballon[t_][indx_] = { -1,-1,-1 };

                }
            }
            else if (monkey[i].second == "LAST") {

            }
            else if (monkey[i].second == "STRONG") {

            }
        }

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> r >> u;

    len_path.resize(r + 1);
    path.resize(r + 1);
    monkey.resize(1001, { "","" });
    ballon.resize(180001);
    ballon_info.resize(1000001);
    ballon_cnt.resize(180001);

    for (int i = 1; i <= r; i++) {
        cin >> len_path[i];
    }

    string a;

    for (int i = 1; i <= r; i++) {
        for (int j = 0; j < len_path[i]; j++) {
            cin >> a;
            int temp = 1, first, second;
            string temps = "";
            while (true) {
                if (a[temp] == ',') {
                    first = stoi(temps);
                    temps = "";
                    temp++;
                    continue;
                }
                if (a[temp] == ')') {
                    second = stoi(temps);
                    break;
                }
                temps += a[temp];
                temp++;
            }
            path[i].push_back({ first,second });
        }
    }

    int a1, idx, route_id;
    double t;
    string skill, pri, kkk;

    for (int i = 0; i < u; i++) {
        cin >> a1 >> skill >> pri;
        monkey[a1] = { skill,pri };
    }

    cin >> e;

    double tmp_t = 0;

    for (int i = 0; i < e; i++) {
        cin >> t >> a;
        
        if (tmp_t != t) {
            sol(tmp_t, t - 1);
        }

        if (a == "ADD") {
            cin >> idx;
            monkey[idx] = { "-","FIRST" };
        }
        else if (a == "UPGRADE") {
            cin >> idx >> skill;
            if (monkey[idx].first == "L1R1")
                continue;
            else if (monkey[idx].first == "-")
                monkey[idx].first = skill;
            else {
                if (monkey[idx].first == skill)
                    continue;
                else {
                    monkey[idx].first = "L1R1";
                }
            }
        }
        else if (a == "REMOVE") {
            cin >> idx;
            monkey[idx] = { "","" };
        }
        else if (a == "CHANGEPRIORITY") {
            cin >> idx >> pri;
            monkey[idx].second = pri;
        }
        else if (a == "BALLOON") {
            string tmp="";
            int ppp;
            while (true) {
                cin >> kkk;
                tmp += kkk;
                if (kkk == "Balloon")
                    break;  
            }
            cin >> idx >> route_id;
            if (kkk == "RedBalloon")
                ppp = 1;
            else if (kkk == "CamoRedBalloon")
                ppp = 2;
            else if (kkk == "LeadBalloon")
                ppp = 3;
            else if (kkk == "CamoLeadBalloon")
                ppp = 4;

            ballon[(int)(t * 1000)].push_back({ ppp,idx,route_id });
            ballon_cnt[(int)(t * 1000)]++;
            ballon_info[idx] = { ppp,(int)(t * 1000),route_id, ballon_cnt[(int)(t * 1000)] };
            double dist = (path[route_id][0].first * path[route_id][0].first + path[route_id][0].second * path[route_id][0].second);
            first_[{dist, { (int)(t * 1000), idx }}] = 1;
            last_[{dist, { -(int)(t * 1000), idx }}] = 1;
            strong_[{-ppp, idx}] = 1;
        }
    }

    return 0;
}