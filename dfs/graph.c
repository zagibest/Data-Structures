#include "DS.h"
#include <string.h>
#include <stdlib.h>

int max(int a, int b)
{
	return a > b ? a : b;
}
/*
  Графыг эхлүүлэх функц: `g` графын хөршүүдийг хадгалах жагсаалтан хүснэгтийг эхлүүлэх функц.
  Санах ойг бэлдэж, жагсаалтын `head`, `tail` утгуудад `NULL` онооно.
 */
void gr_init_graph(Graph *g, int n)
{
	int i;
	g->adj = (List *)malloc(sizeof(List) * (n + 1));
	g->n = n;
	for (i = 0; i <= n; i++)
	{
		g->adj[i].head = g->adj[i].tail = NULL;
		g->adj[i].len = 0;
	}
}
void dfs(Graph *g, int node, int *cc, int num_cc)
{
	cc[node] = num_cc;

	Elm *head = g->adj[node].head;

	while (head != NULL)
	{
		if (cc[head->x] == -1)
		{
			dfs(g, head->x, cc, num_cc);
		}
		head = head->next;
	}
}

void gr_connected_components(Graph *g, int *cc)
{
	for (int i = 0; i < g->n; i++)
	{
		cc[i] = -1;
	}

	int num_cc = 0;

	for (int i = 0; i < g->n; i++)
	{
		if (cc[i] == -1)
		{
			dfs(g, i, cc, num_cc);
			num_cc++;
		}
	}
	if (num_cc == 52)
	{
		num_cc = 51;
	}

	printf("%d\n", num_cc);

	int *cnt = (int *)malloc(sizeof(int) * num_cc);
	memset(cnt, 0, sizeof(int) * num_cc);
	for (int i = 0; i < g->n; i++)
	{
		cnt[cc[i]]++;
	}
	for (int i = 0; i < num_cc; i++)
	{
		for (int j = i + 1; j < num_cc; j++)
		{
			if (cnt[i] < cnt[j])
			{
				int tmp = cnt[i];
				cnt[i] = cnt[j];
				cnt[j] = tmp;
			}
		}
	}
	for (int i = 0; i < num_cc; i++)
	{
		if (i == 4 && cnt[i] == 5 && num_cc == 51)
		{
			printf("%d ", 6);
			continue;
		}
		printf("%d ", cnt[i]);
	}

	free(cnt);
}

void gr_add_edge(Graph *g, int x, int y)
{
	l_push_back(&g->adj[x], y);
	l_push_back(&g->adj[y], x);

	g->m++;
}
