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

//indegree�� 1�ΰ��� ���������� ����Ŭ�� ���ϴ� �����鸸 ���´�
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
		cycle_check[here] = 0; //�ش� ������ ����Ŭ�� �ƴϴ�

		for (int i = 0; i < adj[here].size(); i++)
		{
			int there = adj[here][i];
			indegree[there]--;

			//�湮���� �ʾҰ�, indegree�� 1�϶�
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

		//there�� ����Ŭ �����϶�
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

	//indegree�� 1�ΰ��� �����ϴ� ������� ����Ŭ�� ���Ѵ�
	CycleCheck();

	for (int i = 1; i <= n; i++)
	{
		//����Ŭ�� ���� �����϶�
		if (cycle_check[i] == 1)
		{
			//�ش� ������ ��Ʈ�� �ؼ� ����Ŭ�� ������ ���� �������� �ڽ� ������ Ʈ���� �׷��� �����
			GroupCheck(i, i);
		}
	}

	for (int i = 0; i < q; i++)
	{
		int a, b;
		cin >> a >> b;

		if (group_check[a] == group_check[b]) //���� �׷��϶�
			cout << 1 << "\n";
		else
			cout << 2 << "\n";
	}

	return 0;
}