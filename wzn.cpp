#include <cstdio>
#include <vector>
#include <algorithm>

typedef unsigned long long ull;

using namespace std;

const int MAX_N = 500*1000;

int n, m;
vector<pair<int, int>> sasiedzi[MAX_N]; // każdy wierzchołek ma listę sąsiadów <sasiad, waga>
//bool odwiedzony[MAX_N];

void dodaj_krawedz(int v1, int v2, int w)
{
  sasiedzi[v1].push_back(make_pair(v2, w));
  sasiedzi[v2].push_back(make_pair(v1, w));
}

/*int spr_sasiadow(int ind, int waga)
{
  int ilu = 0;
  
  for (auto v: sasiedzi[ind])
  {
    if (v.second > waga)
      ilu++;
  }
  
  return ilu;
}*/

/*int wzn_z_v(int ind)
{
  int wzn = 0;
  
  for (auto v: sasiedzi[ind])
  {
    wzn += spr_sasiadow(v.first, v.second);
  }

  return wzn;
}*/

/*1
2
3
1

sasiedzi[ind].size()
rosnace pary

1 2
2 3
1 3
1 2
1 3


1
1
2
3

0 - 4 pary
1 - 2 pary
1 - 2 pary
2 - 1 para
3 - 0 par

ostatni - wiadomo
pary - suma par
wieksze - liczba wiekszych ode mnie wierzcholkow
rowne - liczba rownych wierzcholkow

3:
pary += 0;
wieksze = 0;
rowne - tylko ja

2:
 pary += 1;
 wieksze = 1; //=2
 rowne - tylko ja

*/

bool komparator(const pair<int, int> &p1, const pair<int, int> &p2)
{
  return p1.second < p2.second;
}

ull wzn_z_v(int ind)
{
  sort(sasiedzi[ind].begin(), sasiedzi[ind].end(), komparator);
  
  ull pary = 0;
  int wieksze = 0;
  int rowne = 0;
  int koniec = sasiedzi[ind].size() - 1;
  
  int ostatni;
  if (koniec >= 0)
    ostatni = sasiedzi[ind][koniec].second;
  
  for (int i = koniec; i >= 0; i--)
  {
    
    if (ostatni > sasiedzi[ind][i].second)
    {
      wieksze += rowne;
      rowne = 0;
      pary += wieksze;
      //printf("[v = %d] <nierownosc>: wieksze_dodane = %d", i, rowne, wieksze);
      rowne++;
    }
    else
    {
      rowne++;
      pary += wieksze;
      //printf("[v = %d] <rownosc>: rowne = %d, wieksze = %d\n", i, rowne, wieksze);
    }
    
    ostatni = sasiedzi[ind][i].second;
  }
  
  return pary;
}

ull wzniesienia()
{
  ull suma_wzn = 0;
  
  //fill_n(odwiedzony, n, false);
  
  for (int i = 0; i < n; i++)
  {
    suma_wzn += wzn_z_v(i);
  }
  
  return suma_wzn;
}

int main()
{
  scanf("%d %d", &n, &m);
  
  int u, v, w;
  for (int i = 0; i < m; i++)
  {
    scanf("%d %d %d", &u, &v, &w);
    dodaj_krawedz(u - 1, v - 1, w);
  }
  
  printf("%llu\n", wzniesienia());
  
  return 0;
}