#include "DS.h"

// struct WeightedUF
// {
// 	int N;
// 	int *id;
// 	int *sz;
// };
// typedef struct WeightedUF WeightedUF;

void uf_init(WeightedUF *p_uf, int n)
{
	p_uf->N = n;
	p_uf->id = (int *)malloc(sizeof(int) * n);
	p_uf->sz = (int *)malloc(sizeof(int) * n);
	int first;
	for (first = 0; first < n; first++)
	{
		p_uf->id[first] = first;
		p_uf->sz[first] = 1;
	}
}

int uf_connected(WeightedUF *p_uf, int p, int q)
{
	return uf_find(p_uf, p) == uf_find(p_uf, q);
}

int uf_find(WeightedUF *p_uf, int p)
{
	while (p != p_uf->id[p])
	{
		p_uf->id[p] = p_uf->id[p_uf->id[p]];
		p = p_uf->id[p];
	}
	return p;
}

void uf_union(WeightedUF *p_uf, int p, int q)
{
	int i = uf_find(p_uf, p);
	int j = uf_find(p_uf, q);
	if (i == j)
		return;
	if (p_uf->sz[i] < p_uf->sz[j])
	{
		p_uf->id[i] = j;
		p_uf->sz[j] += p_uf->sz[i];
	}
	else
	{
		p_uf->id[j] = i;
		p_uf->sz[i] += p_uf->sz[j];
	}
}
