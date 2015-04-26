#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAX_N = 200*1000;

int n, m, cn, cvn = 0;
int refuge[MAX_N], groups[MAX_N], sums[MAX_N], VN[MAX_N], VLow[MAX_N], max_paths[MAX_N];
vector<int> neighbours[MAX_N], merged[MAX_N]; // every vertice has its own neighbour vector
stack<int> v_stack;
bool VS[MAX_N], visited[MAX_N];

void add_path(int from, int to)
{
	neighbours[from].push_back(to);
}

void DFS_scc(int v)
{
	cvn++;
	VN[v] = cvn;
	VLow[v] = cvn;
	v_stack.push(v);
	VS[v] = true;

	for (auto u: neighbours[v])
	{
		if (VN[u] == 0)
			goto K11;

		if (!VS[u])
			continue;

		if (VN[u] < VLow[v])
			VLow[v] = VN[u];

		continue;

		K11:

		DFS_scc(u);
		if (VLow[u] < VLow[v])
			VLow[v] = VLow[u];
	}

	if (VLow[v] != VN[v])
		return;

	int u = -1;
	while (u != v)
	{
		u = v_stack.top();
		v_stack.pop();
		VS[u] = false;
		//stworz element do listy
		groups[u] = cn;
	}

	//liste dodajemy do listy list
	cn++;
}

void start()
{
	fill_n(VS, n, false);
	fill_n(VN, n, 0);
	cvn = 0;
	//pusta lista skladowych
	cn = 0;

	for (int i = 0; i < n; i++)
	{
		if (VN[i] == 0)
			DFS_scc(i);
	}

	//wypisz listy
}

void connect(int from, int to)
{
	bool add = true;

	if (from == to)
		add = false;

	for (auto u: merged[from])
	{
		if (u == to)
		{
			add = false;
			break;
		}
	}

	if (add)
		merged[from].push_back(to);
}

void create_graph()
{
	fill_n(sums, cn, 0);

	for (int i = 0; i < n; i++)
	{
		sums[groups[i]] += refuge[i];

		for (auto u: neighbours[i])
			connect(groups[i], groups[u]);
	}
}

int dfs(int ind)
{
	int max_val = 0;

	if (max_paths[ind] == -1)
	{
		for (auto u: merged[ind])
		{
			if (max_paths[u] == -1)
				max_paths[u] = dfs(u);

			if (max_paths[u] > max_val)
				max_val = max_paths[u];
		}

		max_paths[ind] = sums[ind] + max_val;
	}

	return max_paths[ind];
}

int max_pts_route()
{
	int max_pts = 0;

	start();
	create_graph();
	fill_n(max_paths, cn, -1);

	for (int i = 0; i < cn; i++)
	{
		if (max_paths[i] == -1)
			max_paths[i] = dfs(i);

		if (max_paths[i] > max_pts)
			max_pts = max_paths[i];
	}

	return max_pts;
}

int main()
{
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%d", &refuge[i]);

	int from, to;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &from, &to);
		add_path(from-1, to-1); // -1 for conversion 1..N to 0..N-1
	}

	printf("%d\n", max_pts_route());

	return 0;
}