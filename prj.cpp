#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
typedef unsigned int uint;

const int MAX_N = 100*1000+1;
const int MAX_M = 500*1000+1;
const int MAX_K = MAX_N;

vector<int> t[MAX_N];
uint n, m, k;
int weight[MAX_N];
int indeg[MAX_N];

// n projektow
// k zaleznosci
// m - minimalna liczba projektow do realizacji

int solution()
{
	priority_queue<pair<int, int>> Q;
	int maximum = 0;

	for (uint i = 1; i <= n; i++)
	{
		if (!indeg[i])
			Q.push(make_pair(-weight[i], i));
	}

	while (k--)
	{
		int v = Q.top().second;
		Q.pop();
		maximum = max(maximum, weight[v]);
		uint size = t[v].size();

		for (uint i = 0; i < size; i++)
		{
			--indeg[t[v][i]];
			if (!indeg[t[v][i]])
				Q.push(make_pair(-weight[t[v][i]], t[v][i]));
		}
	}

	return maximum;
}

int main()
{
	scanf("%d %d %d", &n, &m, &k);

	for (uint i = 1; i <= n; i++)
		scanf("%d", &weight[i]);

	for (uint i = 1; i <= n; i++)
		indeg[i] = 0;

	int a, b;
	for (uint i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		t[b].push_back(a);
		indeg[a]++;
	}

	printf("%d\n", solution());

	return 0;
}