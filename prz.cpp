#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;

struct Node
{
    int l, r, lbound, rbound, prior;
    ll count;
};

class Treap
{
private:

    const static int TREAP_SIZE = 2097152;
    int size;
    Node nodes[TREAP_SIZE];

public:

    int t_root;

    Treap()
    {
        srand(time(NULL));
        size = -1;
        t_root = -1;
    }

    ll count()
    {
        if (t_root == -1)
            return 0;
        else
            return nodes[t_root].count;
    }

    ll intervals(int lb, int rb)
    {
        int n = rb - lb + 1;
        ll resu = n;
        resu *= (n + 1LL);
        resu /= 2LL;
        return resu;
    }

    void count_update(int subtree, int lb)
    {
        if (lb < nodes[subtree].lbound)
            count_update(nodes[subtree].l, lb);
        else if (lb > nodes[subtree].lbound)
            count_update(nodes[subtree].r, lb);

        if (nodes[subtree].prior != -1)
            nodes[subtree].count = intervals(nodes[subtree].lbound, nodes[subtree].rbound);
        else
            nodes[subtree].count = 0;

        if (nodes[subtree].l != -1)
            nodes[subtree].count += nodes[ nodes[subtree].l ].count;

        if (nodes[subtree].r != -1)
            nodes[subtree].count += nodes[ nodes[subtree].r ].count;
    }

    void rotate_left(int &x)
    {
        int y = nodes[x].r;
		nodes[x].r = nodes[y].l;
		nodes[y].l = x;
		x = y;
		count_update(t_root, nodes[ nodes[x].l ].lbound);
    }

    void rotate_right(int &x)
	{
		int y = nodes[x].l;
		nodes[x].l = nodes[y].r;
		nodes[y].r = x;
		x = y;
		count_update(t_root, nodes[ nodes[x].r ].lbound);
	}

	void insert(int &subtree, int lb, int rb)
	{
		if (subtree == -1)
		{
			subtree = ++size;
			nodes[subtree].l = -1;
			nodes[subtree].r = -1;
			nodes[subtree].lbound = lb;
			nodes[subtree].rbound = rb;
			nodes[subtree].prior = rand();
			count_update(t_root, lb);
		}
		else if (lb < nodes[subtree].lbound)
		{
			insert(nodes[subtree].l, lb, rb);
			if (nodes[ nodes[subtree].l ].prior > nodes[subtree].prior)
				rotate_right(subtree);
		}
		else
		{
			insert(nodes[subtree].r, lb, rb);
			if (nodes[ nodes[subtree].r ].prior > nodes[subtree].prior)
				rotate_left(subtree);
		}
	}

	void interval_remove(ll c, ll nr, int lb, int rb)
	{
	    long long my_nr = nr - c;
	    ll len = rb - lb + 1LL, new_lb, new_rb;

	    unsigned long long a = (2LL*len + 3LL)*(2LL*len + 3LL);
	    ll b = 8LL*(my_nr + len + 1LL);
        long double row = -sqrt(a - b);
        row += (2LL*len + 3LL);
        row /= 2.0L;
        ll row2 = floor(row) + 1;

        // Ugly hack - sprawdzanie 2 przypadkow - niedokladnosc double
        ll tmp = (floor(row)-1LL)*(floor(row)-2LL);
        tmp /= 2LL;
        long long row_begin = len * (floor(row)-1LL);
        row_begin -= tmp;

        tmp = (row2-1LL)*(row2-2LL);
        tmp /= 2LL;
        long long row_begin2 = len * (row2-1LL);
        row_begin2 -= tmp;

        if (my_nr >= row_begin2)
        {
            //printf("-42");
            row_begin = row_begin2;
            row = (long double)row2 + 0.1;
        }

        //printf("row1 = %lld, row2 = %lld\nrow_begin = %lld, row_begin2 = %lld\n", (ll)floor(row), (ll)row2, (ll)row_begin, (ll)row_begin2);

        new_lb = lb + floor(row) - 1;
        new_rb = new_lb - row_begin + my_nr;

        printf("%lld %lld\n", new_lb, new_rb);

        remove(t_root, lb);

        if (new_rb < rb)
            insert(t_root, new_rb + 1, rb);

        if (new_lb > lb)
            insert(t_root, lb, new_lb - 1);
	}

	// zakladam, ze cos znajde
	void find(int &subtree, ll nr, ll prev_count)
	{
	    if (subtree != -1)
        {
	    bool flag = false;

	    if (nodes[subtree].l != -1 && nr < prev_count + nodes[ nodes[subtree].l ].count)
        {
            find(nodes[subtree].l, nr, prev_count);
            flag = true;
        }

	    if (!flag)
        {
            if (nodes[subtree].r != -1)
            {
                ll without_right = nodes[subtree].count - nodes[ nodes[subtree].r ].count + prev_count;
                if (nr >= without_right)
                {
                    find(nodes[subtree].r, nr, without_right);
                    flag = true;
                }
            }
        }

        if (!flag)
        {
            if (nodes[subtree].l == -1)
                interval_remove(prev_count, nr, nodes[subtree].lbound, nodes[subtree].rbound);
            else
            {
                interval_remove(nodes[ nodes[subtree].l ].count + prev_count, nr,
                                nodes[subtree].lbound, nodes[subtree].rbound);
            }
        }
        }
        else
            printf("-42\n");
	}

	void remove(int &subtree, int lb)
	{
		if (subtree != -1)
        {
            if (lb < nodes[subtree].lbound)
                remove(nodes[subtree].l, lb);
            else if (lb > nodes[subtree].lbound)
                remove(nodes[subtree].r, lb);
            else
            {
                if (nodes[subtree].l == -1 && nodes[subtree].r == -1)
                {
                    nodes[subtree].prior = -1;
                    count_update(t_root, nodes[subtree].lbound);
                    subtree = -1;
                }
                else if (nodes[subtree].l == -1)
                {
                    subtree = nodes[subtree].r;
                    count_update(t_root, nodes[subtree].lbound);
                }
                else if (nodes[subtree].r == -1)
                {
                    subtree = nodes[subtree].l;
                    count_update(t_root, nodes[subtree].lbound);
                }
                else if (nodes[ nodes[subtree].l ].prior < nodes[ nodes[subtree].r ].prior)
                {
                    rotate_left(subtree);
                    remove(nodes[subtree].l, lb);
                }
                else
                {
                    rotate_right(subtree);
                    remove(nodes[subtree].r, lb);
                }
            }
        }
	}

	void print(int k)
	{
	    if (k != -1)
        {
            if (nodes[k].l != -1)
                print(nodes[k].l);
            cout << "[" << nodes[k].lbound << " " << nodes[k].rbound << "], count = " << nodes[k].count << endl;
            if (nodes[k].r != -1)
                print(nodes[k].r);
        }
	}

};

Treap t;

// Zwraca ile jest przedziałów zawartych w zbiorze
ll set_init(int n)
{
    t.insert(t.t_root, 1, n);
	return t.count();
}

// Zwraca ile jest przedziałów zawartych w zbiorze
ll display_and_remove(ll l)
{
    t.find(t.t_root, l, 0);
    return t.count();
}

int main()
{
    int n;
	scanf("%d", &n);
	printf("%lld\n", set_init(n));
	/*printf("------\n");
	t.print(t.t_root);
	printf("------\n");*/

	bool finished = false;
	long long l;
	while (!finished)
	{
		scanf("%lld", &l);

		if (l == -1)
			finished = true;
		else
			printf("%lld\n", display_and_remove(l));

        /*printf("------\n");
        t.print(t.t_root);
        printf("------\n");*/
	}

	return 0;
}
