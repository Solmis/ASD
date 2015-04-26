#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 40000;
const int M = 50;
int n, m, liczba;
long long zbiory[N];

bool wszyscy_przeciwko_sobie()
{
  sort(begin(zbiory), zbiory+n);
  bool resu = true;
  
  for (int i = 0; i < n-1; i++)
  {
    if (zbiory[i] == zbiory[i+1])
      resu = false;
  }

  return resu;
}

int main()
{
  scanf("%d %d", &n, &m);
  
  for (int i = 0; i < n; i++)
    zbiory[i] = 0;

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n/2; j++)
    {
      scanf("%d", &liczba);
      zbiory[liczba-1] *= 2;
    }
    for (int j = 0; j < n/2; j++)
    {
      scanf("%d", &liczba);
      zbiory[liczba-1] *= 2;
      zbiory[liczba-1] ++;
    }
  }

  if (wszyscy_przeciwko_sobie())
    printf("TAK\n");
  else
    printf("NIE\n");

  return 0;
}