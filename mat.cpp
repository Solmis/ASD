#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LENGTH = 10000001;
const char EVERY_COLOUR = '*';

int n;
char zamowienie[MAX_LENGTH];

// Ile zgadzających się znaków dla pozycji od [pos] do [pos + n - k]. K to max.
// Zwraca liczbę zgadzających się znaków.
int ile_zgodnych(int k, int pos)
{
	char tmp_colour = EVERY_COLOUR;

	for (int i = 1; i < (k + 1); i++)
	{
		if (zamowienie[pos] != zamowienie[pos + i])
		{
			if (zamowienie[pos + i] != EVERY_COLOUR)
			{
				if (zamowienie[pos] == EVERY_COLOUR)
				{
					if (tmp_colour == EVERY_COLOUR)
						tmp_colour = zamowienie[pos + i];
					else if (tmp_colour != zamowienie[pos + i])
						return i;
				}
				else
					return i;
			}
		}
	}

	return k;
}

int znajdz_min_dl()
{
	int pos = 0;
	int k = ile_zgodnych(n, pos);

	while ((n >= (k + pos + 1)) && (pos < n - 1))
	{
		pos++; //?
		k = ile_zgodnych(k, pos);
	}

	return (n - k + 1);
}

int znajdz_min_dl_2()
{
	int min_odl = n-1, tmp_odl = 0;
	char last_znak = zamowienie[0];

	for (int i = 1; i < n; i++)
	{
		if (zamowienie[i] == last_znak)
			tmp_odl = 0;
		else if (zamowienie[i] == '*')
			tmp_odl++;
		else
		{
			if (last_znak != '*')
			{
				min_odl = (tmp_odl < min_odl ? tmp_odl : min_odl);
				tmp_odl = 0;
			}
			last_znak = zamowienie[i];
		}
	}

	return (n - min_odl);
}

int main()
{
	scanf("%s", zamowienie);
	n = strlen(zamowienie);
	printf("%d\n", znajdz_min_dl_2());

	return 0;
} 