#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;

const int MAX_LEN = 300*1000+1;
const ll P = 70032301;
const ll Q = 1000000007;

int n, m;
string s;
ll hashes[MAX_LEN], powers[MAX_LEN + 1];
int one[2] = {-1, -1}, two[2] = {-1, -1}, three[2] = {-1, -1};

void count_hashes()
{
	hashes[n] = 90;
	for (int i = n-1; i >= 0; i--)
		hashes[i] = (ll)(hashes[i+1]*P + s[i]) % Q;

	powers[0] = 1;
	for (int i = 1; i <= n; i++)
		powers[i] = (ll)(powers[i-1] * P) % Q;
}

ll hash_fn(int l, int r)
{
	int len = r - l + 1;
	//printf("[%d, %d] len: %d\n", l, r, len);
	//cout << s.substr(l, len) << endl;
	/*three[0] = two[0];
	three[1] = two[1];
	two[0] = one[0];
	two[1] = two[1];
	one[0] = l;
	one[1] = r;*/

	//assert(len > 0);
	//assert(r < n);
	//assert(three[0] <= one[0] || three[1] <= one[1]);

	/*ll pN = 1;
	for (int i = 1; i <= len; i++)
		pN = (long long)(pN * P) % Q;*/
	ll pN = powers[len];

	return (ll)(hashes[l] - hashes[r + 1] * pN) % Q;
}

char lex_comp(int a, int b, int c, int d)
{
	a -= 1;
	b -= 1;
	c -= 1;
	d -= 1;

	three[0] = three[1] = two[1] = two[0] = one[0] = one[1] = -1;

	bool greater = false;
	bool equal = true;

	ll h1 = hash_fn(a, a);
	ll h2 = hash_fn(c, c);
	int my_min = min(b - a + 1, d - c + 1); // mniejsza z dlugosci substringow
	int l = 1, r = 1, shift = 0;
	while (true) // r <= my_min
	{
		if (h1 == h2)
		{
			if (r == my_min - shift)
				break;

			r *= 2;

			if (r > my_min - shift)
			{
				shift += (r / 2);
				l = r = 1;
			}
		}
		else
		{
			if (l == r)
			{
				greater = h1 > h2;
				equal = false;
				break;
			}

			shift += (r / 2);
			l = r = 1;
		}

		//assert(a + l + shift - 1 <= b);
		//assert(c + l + shift - 1 <= d);
		h1 = hash_fn(a + l + shift - 1, a + r + shift - 1);
		h2 = hash_fn(c + l + shift - 1, c + r + shift - 1);
	}

	if (equal)
	{
		if (a - b == c - d)
			return '=';
		else if (a - b < c - d)
			return '>';
		else
			return '<';
	}

	if (greater)
		return '>';
	else
		return '<';
}

int main()
{
	scanf("%d %d", &n, &m);
	cin >> s;
	count_hashes();

	int a, b, c, d;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d %d", &a, &b, &c, &d);
		printf("%c\n", lex_comp(a, b, c, d));
	}

	return 0;
}