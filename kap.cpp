#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

const int MAX_N = 200*1000;
const int MAX_LONG = 2147483647;

int N, a, b;
vector<pair<int, int>> weights[MAX_N]; //tablica - kazdy wierzcholek ma swoj wektor sasiadow
vector<tuple<int, int, int>> island_pos;
int dist[MAX_N];

int weight(int v, int i)
{
	return min(abs(get<1>(island_pos[v]) - get<1>(island_pos[i])), abs(get<2>(island_pos[v]) - get<2>(island_pos[i])));
}

bool ind_comp(tuple<int, int, int> t1, tuple<int, int, int> t2)
{
	return get<0>(t1) < get<0>(t2);
}

bool x_comp(tuple<int, int, int> t1, tuple<int, int, int> t2)
{
	return get<1>(t1) < get<1>(t2);
}

bool y_comp(tuple<int, int, int> t1, tuple<int, int, int> t2)
{
	return get<2>(t1) < get<2>(t2);
}

int lazy_captain()
{
	priority_queue<pair<int, int>> Q;

	for (int i = 1; i < N; i++)
	{
		Q.push(make_pair(-dist[i], i));
	}

	while (!Q.empty())
	{
		int v = Q.top().second;
		Q.pop();

		int i, w;
		for (auto x: weights[v])
		{
			i = x.first;
			w = x.second;
			if (dist[i] > dist[v] + w)
			{
				dist[i] = dist[v] + w;
				Q.push(make_pair(-dist[i], i));
			}
		}
	}

	return dist[N-1];
}

void count_dw()
{
	for (int i = 0; i < N; i++)
		dist[i] = weight(i, 0);

	sort(island_pos.begin(), island_pos.end(), x_comp);
	for (int i = 1; i < N; i++)
	{
		weights[get<0>(island_pos[i-1])].push_back(make_pair(get<0>(island_pos[i]), weight(i-1, i)));
		weights[get<0>(island_pos[i])].push_back(make_pair(get<0>(island_pos[i-1]), weight(i-1, i)));
	}

	sort(island_pos.begin(), island_pos.end(), y_comp);
	for (int i = 1; i < N; i++)
	{
		weights[get<0>(island_pos[i-1])].push_back(make_pair(get<0>(island_pos[i]), weight(i-1, i)));
		weights[get<0>(island_pos[i])].push_back(make_pair(get<0>(island_pos[i-1]), weight(i-1, i)));
	}
	//weights[get<0>(island_pos[i-1])].push_back(make_pair(get<0>(island_pos[i]), weight(get<0>(island_pos[i-1]), get<0>(island_pos[i]))));
	//weights[island_pos[i-1]].push_back(make_pair(island_pos[i], weight(island_pos[i-1], island_pos[i])));

	sort(island_pos.begin(), island_pos.end(), ind_comp);
}

int main()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &a, &b);
		island_pos.push_back(make_tuple(i, a, b));
	}

	count_dw();

	printf("%d\n", lazy_captain());

	return 0;
}