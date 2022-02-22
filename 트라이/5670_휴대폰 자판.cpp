/*
트라이 이용

TRIE->total을 통해서 현재 node에서 다른 node로 이어지는 알파벳이 있는지 확인 + 현재 node가 마지막 알파벳인지 확인.

root라면 answer 1 증가, 현재 node->total != 1이 아니라면 answer 1증가

answer/n 으로 평균 횟수 출력.


eof 입력에 대해서 + 객체 소멸자에 대한 내용 배움.

root 객체 사용 후, 소멸안해서 메모리 초과... -> 객체 소멸자 추가 이후 해결.

*/


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct TRIE {

    int total;
    TRIE* node[26];

    TRIE(){
        total = 0;
        for (int i = 0; i < 26; i++)
            node[i] = NULL;
    }

    ~TRIE() {
        for (int i = 0; i < 26; i++)
            if (node[i])
                delete node[i];
    }

};

int n;

vector<string>v;
vector<pair<int,int>>answer;

TRIE* root;

void Insert(int node) {

    string now = v[node];

    TRIE* here = root;

    for (int i = 0; i < now.size(); i++) {
        int idx = now[i] - 'a';

        if (here->node[idx] == NULL) {
            here->total++;
            here->node[idx] = new TRIE();
        }
        here = here->node[idx];
    }

    here->total++;

}

int Find() {

    int answer = 0;

    string now;

    TRIE* here;

    for (int i = 0; i < n; i++) {
        now = v[i];
        here = root->node[now[0] - 'a'];
        answer++;

        for (int i = 1; i < now.size(); i++) {
            int idx = now[i] - 'a';

            if (here->total != 1) {
                answer++;
            }

            here = here->node[idx];
        }
    }

    return answer;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   
    while (true) {
        int tmp;

        cin >> tmp;

        if (cin.eof()) 
            return 0;

        n = tmp;

        v.clear();
        v.resize(n);

        root = new TRIE();

        for (int i = 0; i < n; i++) {
            cin >> v[i];
            Insert(i);
        }

        cout << fixed;
        cout.precision(2);
        cout << double(Find()) / (double)n << "\n";

        delete root;
    }



    return 0;
}