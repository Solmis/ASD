#include <cstdio>
#include <algorithm>

using namespace std;

const int K = 5001;
const int N = 5000;
int n, k;
int my_input[3][N];
int tab[2][3][K];

void fill_with_zeros()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < K; k++)
			{
				tab[i][j][k] = 0;
			}
		}
	}
}

int excavation()
{
	int ver[2], resu[3];
	ver[0] = 0;
	ver[1] = 1;

	for (int a = 0; a < 3; a++)
	{
		fill_with_zeros();

		if (a == 0)
		{
			tab[ver[1]][0][1] = max(my_input[1][0], my_input[2][0]);
			tab[ver[1]][1][1] = my_input[2][0];
			tab[ver[1]][0][2] = my_input[1][0] + my_input[2][0];
		}
		else if (a == 1)
		{
			tab[ver[1]][0][1] = my_input[2][0];
			tab[ver[1]][2][1] = my_input[0][0];
			tab[ver[1]][1][1] = max(my_input[2][0], my_input[0][0]);
			tab[ver[1]][1][2] = my_input[2][0] + my_input[0][0];
		}
		else
		{
			tab[ver[1]][1][1] = my_input[0][0];
			tab[ver[1]][2][1] = max(my_input[0][0], my_input[1][0]);
			tab[ver[1]][2][2] = my_input[0][0] + my_input[1][0];
		}

		if ((n == 1) && (k > 2))
			tab[ver[1]][a][k] = tab[ver[1]][a][2];

		for (int i = 1; i < n; i++)
		{
			ver[0]++;
			ver[0] %= 2;
			ver[1]++;
			ver[1] %= 2;

			if (k > 0)
			{
				tab[ver[1]][0][1] = max({my_input[1][i], my_input[2][i], tab[ver[0]][0][1], tab[ver[0]][1][1], tab[ver[0]][2][1]});
				tab[ver[1]][1][1] = max({my_input[0][i], my_input[2][i], tab[ver[0]][0][1], tab[ver[0]][1][1], tab[ver[0]][2][1]});
				tab[ver[1]][2][1] = max({my_input[0][i], my_input[1][i], tab[ver[0]][0][1], tab[ver[0]][1][1], tab[ver[0]][2][1]});
			}

			for (int j = 2; j <= k; j++)
			{
				tab[ver[1]][0][j] = max({tab[ver[0]][0][j-1] + max(my_input[1][i], my_input[2][i]),
						                 tab[ver[0]][0][j-2] + my_input[1][i] + my_input[2][i],
						                 tab[ver[0]][1][j-1] + my_input[2][i],
						                 tab[ver[0]][0][j],
						                 tab[ver[0]][1][j],
						                 tab[ver[0]][2][j]});


				tab[ver[1]][1][j] = max({tab[ver[0]][1][j-2] + my_input[0][i] + my_input[2][i],
					                     tab[ver[0]][1][j-1] + max(my_input[0][i], my_input[2][i]),
					                     tab[ver[0]][0][j-1] + my_input[2][i],
					                     tab[ver[0]][2][j-1] + my_input[0][i],
					                     tab[ver[0]][0][j],
					                     tab[ver[0]][1][j],
					                     tab[ver[0]][2][j]});


				tab[ver[1]][2][j] = max({tab[ver[0]][2][j-2] + my_input[0][i] + my_input[1][i],
				                         tab[ver[0]][2][j-1] + max(my_input[0][i], my_input[1][i]),
				                         tab[ver[0]][1][j-1] + my_input[0][i],
				                         tab[ver[0]][0][j],
				                         tab[ver[0]][1][j],
				                         tab[ver[0]][2][j]});
			}
		}

		resu[a] = tab[ver[1]][a][k];
	}

	return max(max(resu[0], resu[1]), resu[2]);
}

int main()
{
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &my_input[0][i], &my_input[1][i], &my_input[2][i]);
	}

	printf("%d\n", excavation());

	return 0;
}