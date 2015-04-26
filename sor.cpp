#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000;
const int MOD = 1000000000;

int n;
int tab[N];
int ile_ciagow[N][N][2];
int pom[N]; //odwrocona kolejnosc
int last_ind;

int rek(int l, int p);
int rek(int l, int p, bool ostatni);


int rek(int l, int p)
{
	if (l == p)
		return 1;
	else if (p == l + 1)
	{
		if (tab[l] < tab[p])
			return 2;
		else
			return 0;
	}
	else
	{
	    last_ind = 0;
	    pom[last_ind] = tab[l];
	    int ile1 = rek(l+1, p, false);
	    last_ind = 0;
	    pom[last_ind] = tab[p];
	    int ile2 = rek(l, p-1, true);

	    return (ile1 + ile2) % MOD;
	}
}

int rek(int l, int p, bool ostatni)
{
	if (p == l)
	{
		last_ind++;
		pom[last_ind] = tab[l];
		last_ind--;
		if ((ostatni) && (pom[last_ind] > tab[l]))
		  return 1;
		else if ((!ostatni) && (pom[last_ind] < tab[l]))
		  return 1;
		else
		  return 0;
	}
	else
	{
		int ile1 = 0, ile2 = 0;
		
		if (ile_ciagow[l][p][ostatni] > -1)
		  return ile_ciagow[l][p][ostatni];
		else
		{
		  if (ostatni)
		  {
			  if (pom[last_ind] > tab[l])
			  {
				  last_ind++;
				  pom[last_ind] = tab[l];
			          ile1 = rek(l+1, p, false);
				  last_ind--;
			  }

			  if (pom[last_ind] > tab[p])
			  {
				  last_ind++;
				  pom[last_ind] = tab[p];
				  ile2 = rek(l, p-1, true);
				  last_ind--;
			  }
			  
			  ile_ciagow[l][p][1] = (ile1 + ile2) % MOD;
			  return (ile1 + ile2) % MOD;
		  }
		  else
		  {
			  if (pom[last_ind] < tab[l])
			  {
				  last_ind++;
				  pom[last_ind] = tab[l];
				  ile1 = rek(l+1, p, false);
				  last_ind--;
			  }

			  if (pom[last_ind] < tab[p])
			  {
				  last_ind++;
				  pom[last_ind] = tab[p];
				  ile2 = rek(l, p-1, true);
				  last_ind--;
			  }
			  
			  ile_ciagow[l][p][0] = (ile1 + ile2) % MOD;
			  return (ile1 + ile2) % MOD;
		  }
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &tab[i]);
	
	for (int i = 0; i < n; i++)
	  for (int j = 0; j < n; j++)
	  {
	    ile_ciagow[i][j][0] = -1;
	    ile_ciagow[i][j][1] = -1;
	}
	
	printf("%d\n", rek(0, n-1));

	return 0;
}