#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 20*1000;
const int K = 10;
const int MOD = 1000*1000*1000;
const int BASE = 32768;

int n, k, permutacja[N], a[N], tree[2*BASE];

void insert(int i, int k)
{
	int ind = BASE + i;
	while (ind > 0)
	{
		tree[ind] += k;
		tree[ind] = tree[ind] % MOD;
		ind = floor(ind / 2);
	}
}

int getSum(int i)
{
	int ind = BASE + i;
	int resu = 0;

	while (ind > 0)
	{
		if (ind % 2 == 0)
		{
			resu += tree[ind + 1];
			resu = resu % MOD;
		}
		ind = floor(ind / 2);
	}

	return resu;
}

int ile_inw()
{
	fill(a, a+n, 1);

	for (int i = 0; i < k-1; i++)
	{
		fill(tree, tree+2*BASE, 0);

		for (int l = 0; l < n; l++)
		{
			insert(permutacja[l], a[l]);
			a[l] = getSum(permutacja[l]);
		}
	}

	int resu = 0;
	for (int i = 0; i < n; i++)
	{
		resu += a[i];
		resu = resu % MOD;
	}

	return resu;
}

/*int ile_inw()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			tab[i][j] = 0;

	int ind = 0;

	for (int i = 0; i < n; i++)
	{
		ind = permutacja[i]-1;
		tab[ind][0] = 1;

		for (int j = 1; j < k; j++)
		{
			for (int g = ind+1; g < n; g++)
			{
				tab[ind][j] += tab[g][j-1];
				tab[ind][j] = tab[ind][j] % MOD;
			}				
		}
	}

	int sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += tab[i][k-1];
		sum = sum % MOD;  
	}

	return sum;

}*/

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &permutacja[i]);

	printf("%d\n", ile_inw());

	return 0;
}