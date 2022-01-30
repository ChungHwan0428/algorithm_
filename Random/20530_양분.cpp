#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, q;
vector<int> adj[200005];
vector<int> visited(200005, 0);
vector<int> cycle_check(200005, 1);
vector<int> group_check(200005, 0);
vector<int> indegree(200005, 0);

//indegree가 1인것을 지워나가면 싸이클에 속하는 정점들만 남는다
void CycleCheck()
{
	queue<int> q;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 1)
		{
			q.push(i);
		}
	}

	while (!q.empty())
	{
		int here = q.front();
		q.pop();

		visited[here] = 1;
		cycle_check[here] = 0; //해당 정점은 싸이클이 아니다

		for (int i = 0; i < adj[here].size(); i++)
		{
			int there = adj[here][i];
			indegree[there]--;

			//방문하지 않았고, indegree가 1일때
			if (visited[there] == 0 && indegree[there] == 1)
			{
				q.push(there);
			}
		}
	}
}

void GroupCheck(int here, int group_num)
{
	group_check[here] = group_num;

	for (int i = 0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];

		//there가 싸이클 정점일때
		if (cycle_check[there] == 1)
			continue;

		if (group_check[there] == 0)
		{
			GroupCheck(there, group_num);
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> q;

	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;

		adj[a].push_back(b);
		indegree[b]++;

		adj[b].push_back(a);
		indegree[a]++;
	}

	//indegree가 1인것을 제외하는 방법으로 싸이클을 구한다
	CycleCheck();

	for (int i = 1; i <= n; i++)
	{
		//싸이클에 속한 정점일때
		if (cycle_check[i] == 1)
		{
			//해당 정점을 루트로 해서 싸이클에 속하지 않은 정점들을 자식 노드로한 트리로 그룹을 만든다
			GroupCheck(i, i);
		}
	}

	for (int i = 0; i < q; i++)
	{
		int a, b;
		cin >> a >> b;

		if (group_check[a] == group_check[b]) //같은 그룹일때
			cout << 1 << "\n";
		else
			cout << 2 << "\n";
	}

	return 0;
}