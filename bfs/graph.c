#include "DS.h"

int s_empty(Stack *stack)
{
	return stack->len == 0;
}

int s_len(Stack *stack)
{
	return stack->len;
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

/*
  Төвшний нэвтрэлтийн функц: `g` граф дээр `s` оройгоос эхлэн төвшний нэвтрэлтийг хийнэ.
  `pi`: Төвшний нэвтрэлт хийсний дараа `pi[tmp]` нь `tmp` оройд ямар оройгоос ирснийг хадгална.
 */
void gr_bfs(Graph *g, int s, int pi[])
{
	Queue q;
	int i, tmp, v;
	q.head = NULL;
	q.tail = NULL;
	q.len = 0;

	for (i = 1; i <= g->n; i++)
	{
		pi[i] = -1;
	}
	pi[s] = 0;
	q_push(&q, s);
	while (q.len > 0)
	{
		tmp = q.head->x;
		q_pop(&q);
		for (Elm *e = g->adj[tmp].head; e != NULL; e = e->next)
		{
			v = e->x;
			if (pi[v] == -1)
			{
				pi[v] = tmp;
				q_push(&q, v);
			}
		}
	}
}

// struct Elm {
// 	int x;
//         struct Elm *next;
// };
// typedef struct Elm Elm;

// // Stack
// struct Stack {
//         Elm *top;
//         int len;
// };
// typedef struct Stack Stack;

// void s_push(Stack *, int );
// void s_pop(Stack *);
// void s_print(Stack *);

// // Queue
// struct Queue {
//         Elm *head;
//         Elm *tail;
//         int len;
// };
// typedef struct Queue Queue;

// void q_push(Queue *, int);
// void q_pop(Queue *);
// void q_print(Queue *);

// // List бүтэц
// struct List {
//         Elm *head;
//         Elm *tail;
//         int len;
// };
// typedef struct List List;

// void l_push_back(List *, int);
// void l_push_front(List *, int);
// void l_insert(List *, int, int);
// void l_pop_front(List *);
// void l_pop_back(List *);
// void l_erase(List *, int);
// void l_print(List *);
// Elm *l_search(List *, int);

/*
  Замын оройнуудыг хэвлэх функц: `pi` хүснэгтээс `s`, `t` орой хоорондын замын мэдээллийг хэвлэнэ.
  Хамгийн эхний мөрөнд замын уртыг, дараагийн мөрөнд `s` оройгоос эхлэн ямар оройгоор дамжиж
  очиж байгаа оройнуудыг 1 хоосон зайгаар тусгаарлан хэвлэнэ.
  Хэрэв зам байхгүй бол `-1` гэсэн ганц утга хэвлэнэ.
 */
void gr_print_path(int pi[], int s, int t)
{
	int tmp = t;
	int len = 0;
	Stack stk;
	stk.top = NULL;
	stk.len = 0;
	while (tmp != s)
	{
		if (tmp == -1)
		{
			printf("-1");
			return;
		}
		s_push(&stk, tmp);
		tmp = pi[tmp];
		len++;
	}
	s_push(&stk, s);
	printf("%d\n", len + 1);
	while (stk.len > 0)
	{
		printf("%d ", stk.top->x);
		s_pop(&stk);
	}
}

/*
  Ирмэг нэмэх функц: `g` графын ирмэгүүдийг хадгалах `adj` жагсаалтан хүснэгтэд ирмэг нэмнэ.
  Уг граф нь чиглэлгүй граф тул `x`-с `y`, `y`-с `x` гэсэн хоёр ирмэгийг оруулна.
 */
void gr_add_edge(Graph *g, int x, int y)
{
	l_push_back(&g->adj[x], y);
	l_push_back(&g->adj[y], x);
}
