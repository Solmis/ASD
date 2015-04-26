#include <cstdio>
#include <algorithm>

using namespace std;

const int BASE = 1048576;

const int CZARNY = 0;
const int BIALY = 1;
const int MIESZANY = 2;

int n, m, a, b, big_sum;
int tree[2 * BASE];
char c;

void ins_rek(int l, int r, int a, int b, int ind)
{
	int tmp1, tmp2;

	if (tree[ind] == BIALY)
	{
		return;
	}
	else if ((l <= b) && (r >= a)) // przeciecie niepuste
	{
		if (l == r)
		{
			if (tree[ind] != BIALY)
				big_sum++;
			tree[ind] = BIALY;
		}
		else if ((l >= a) && (r <= b)) // [l, r] wewnatrz [a, b] => pomaluj caly [l, r]
		{
			if (tree[ind] == CZARNY)
			{
				tree[ind] = BIALY;
				big_sum += (r - l + 1);
			}
			else if (tree[ind] == MIESZANY)
			{
				int ind2 = ind << 1;
				int lr = (l+r) >> 1;

				ins_rek(l, lr, a, b, ind2);
				ins_rek(lr + 1, r, a, b, ind2 + 1);
				tmp1 = tree[ind2];
				tmp2 = tree[ind2 + 1];

				if (tmp1 == tmp2)
				{
					if (tmp1 == BIALY)
						tree[ind] = BIALY;
					else if (tmp1 == CZARNY)
						tree[ind] = CZARNY;
				}
			}
		}
		else
		{
			int ind2 = ind << 1;
			int lr = (l+r) >> 1;

			if (tree[ind] == CZARNY)
			{
				tree[ind] = MIESZANY;
				tree[ind2] = CZARNY;
				tree[ind2 + 1] = CZARNY;
			}

			ins_rek(l, lr, a, b, ind2);
			ins_rek(lr + 1, r, a, b, ind2 + 1);

			tmp1 = tree[ind2];
			tmp2 = tree[ind2 + 1];

			if (tmp1 == tmp2)
			{
				if (tmp1 == BIALY)
					tree[ind] = BIALY;
				else if (tmp1 == CZARNY)
					tree[ind] = CZARNY;
			}
		}
	}
}

void rem_rek(int l, int r, int a, int b, int ind)
{
	int tmp1, tmp2;

	if (tree[ind] == CZARNY)
	{
		return;
	}
	else if ((l <= b) && (r >= a)) // przeciecie niepuste
	{
		if (l == r)
		{
			if (tree[ind] != CZARNY)
				big_sum--;
			tree[ind] = CZARNY;
		}
		else if ((l >= a) && (r <= b)) // [l, r] wewnatrz [a, b] => pomaluj caly [l, r]
		{
			if (tree[ind] == BIALY)
			{
				tree[ind] = CZARNY;
				big_sum -= (r - l + 1);
			}
			else if (tree[ind] == MIESZANY)
			{
				int ind2 = ind << 1;
				int lr = (l+r) >> 1;

				rem_rek(l, lr, a, b, ind2);
				rem_rek(lr + 1, r, a, b, ind2 + 1);
				tmp1 = tree[ind2];
				tmp2 = tree[ind2 + 1];

				if (tmp1 == tmp2)
				{
					if (tmp1 == BIALY)
						tree[ind] = BIALY;
					else if (tmp1 == CZARNY)
						tree[ind] = CZARNY;
				}
			}
		}
		else
		{
			int ind2 = ind << 1;
			int lr = (l+r) >> 1;

			if (tree[ind] == BIALY)
			{
				tree[ind] = MIESZANY;
				tree[ind2] = BIALY;
				tree[ind2 + 1] = BIALY;
			}

			rem_rek(l, lr, a, b, ind2);
			rem_rek(lr + 1, r, a, b, ind2 + 1);

			tmp1 = tree[ind2];
			tmp2 = tree[ind2 + 1];

			if (tmp1 == tmp2)
			{
				if (tmp1 == BIALY)
					tree[ind] = BIALY;
				else if (tmp1 == CZARNY)
					tree[ind] = CZARNY;
			}
		}
	}
}

void insert(int a, int b)
{
	ins_rek(1, BASE, a, b, 1);
}

void remove(int a, int b)
{
	rem_rek(1, BASE, a, b, 1);
}

int getSum(int l, int r, int ind)
{
	if (l == r)
	{
		if (tree[ind] == BIALY)
			return 1;
		else
			return 0;
	}
	else
	{
		if (tree[ind] == BIALY)
			return (r - l + 1);
		else if (tree[ind] == CZARNY)
			return 0;
		else
		{
			return getSum(l, (l+r)/2, ind * 2) + getSum((l+r)/2 + 1, r, ind * 2 + 1);
		}
	}
}

//maluje i zwraca sumę
int paint(int a, int b, char c)
{
	if (c == 'B') /* Profesor maluje */
		insert(a, b);
	else
		remove(a, b);

	return big_sum;//getSum(1, BASE, 1);
}

int main()
{
	scanf("%d", &n);
	fill(tree, tree+(2*BASE), CZARNY);
	big_sum = 0;
	scanf("%d", &m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %c", &a, &b, &c);
		printf("%d\n", paint(a, b, c));
	}

	return 0;
}