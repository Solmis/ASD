/* Micha³ So³tysiak - ms347246 - rozwi¹zanie zadania "Bazarek" */
#include <cstdio>

const int MAX_N = 1000000;
const int MAX_M = 1000000;

int prices[MAX_N];
long long int suffix_sums[MAX_N], next_odd[MAX_N], prev_odd[MAX_N], next_even[MAX_N], prev_even[MAX_N];

int n, m;

inline long long int max(long long int a, long long int b)
{
	return a > b ? a : b;
}

void compute()
{
	suffix_sums[n-1] = prices[n-1];

	for (int i = n-2; i >= 0; i--)
		suffix_sums[i] = suffix_sums[i+1] + prices[i];

	int tmp = -1;
	for (int i = 0; i < n; i++)
	{
		if (prices[i] % 2 == 0)
			tmp = prices[i];
		prev_even[i] = tmp;
	}

	tmp = -1;
	for (int i = 0; i < n; i++)
	{
		if (prices[i] % 2 == 1)
			tmp = prices[i];
		prev_odd[i] = tmp;
	}

	tmp = -1;
	for (int i = n-1; i >= 0; i--)
	{
		if (prices[i] % 2 == 1)
			tmp = prices[i];
		next_odd[i] = tmp;
	}

	tmp = -1;
	for (int i = n-1; i >= 0; i--)
	{
		if (prices[i] % 2 == 0)
			tmp = prices[i];
		next_even[i] = tmp;
	}
}

long long int max_odd_sum(int k)
{
	long long tmp = suffix_sums[n-k];
	if (tmp % 2 == 1)
		return tmp;
	else if (n - k < 1)
		return -1;
	else
	{
		int no = next_odd[n-k];
		int pe = prev_even[n-k-1];
		int ne = next_even[n-k];
		int po = prev_odd[n-k-1];
		long long int a = ((no != -1) && (pe != -1)) ? tmp - no + pe : -1;
		long long int b = ((ne != -1) && (po != -1)) ? tmp - ne + po : -1;
		return ((a != -1) || (b != -1)) ? max(a, b) : -1;
	}
}

int main(int argc, char const *argv[])
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &prices[i]);

	compute();

	scanf("%d", &m);

	int temp;
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &temp);
		printf("%lld\n", max_odd_sum(temp));
	}

	return 0;
}
