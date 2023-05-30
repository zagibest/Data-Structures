#include "DS.h"

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);

	WeightedUF uf;
	uf_init(&uf, n * n + 2);

	int i;

	for (i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);

		int p = uf_find(&uf, x);
		int q = uf_find(&uf, y);

		if (p != q)
		{
			uf_union(&uf, p, q);

			if (uf_find(&uf, n * n) == uf_find(&uf, n * n + 1))
			{
				printf("%d\n", i + 1);
				break;
			}
		}
	}

	if (uf_find(&uf, n * n) != uf_find(&uf, n * n + 1))
	{
		printf("-1\n");
	}

	return 0;
}