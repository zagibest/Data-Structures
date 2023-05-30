#include "DS.h"

int is_space(int x)
{
	switch (x)
	{
	case ' ':
	case '\t':
	case '\n':
	case '\r':
	case '\f':
	case '\v':
	case '\0':
		return 1;
	default:
		return 0;
	}
	return 0;
}

int convert_to_int(const char s[])
{
	int len = strlen(s);
	int t = 0, i;
	for (i = 0; i < len; i++)
		t = t * 10 + s[i] - '0';
	return t;
}

void tokenize(const char s[], List *p_list)
{
	char tmp[EQUATION_LENGTH];
	int i, j, k, len;
	j = 0;
	struct Token x;
	len = strlen(s);
	for (i = 0; i <= len; i++)
	{
		if ('0' <= s[i] && s[i] <= '9')
		{
			/* цифр орж ирлээ */
			tmp[j] = s[i];
			j++;
		}
		else
		{
			/* тэмдэгт орж ирлээ */
			if (j != 0)
			{ /* Хөрвүүлэх тоо байгаа эсэх */
				tmp[j] = '\0';
				j = 0;
				/* хадгалсан цифрийн цувааг int-рүү хөрвүүл */
				k = convert_to_int(tmp);
				x.flag = 1;
				x.val = k;
				/*
				  Жагсаалтанд x элемнтийг оруулах
				  Жагсаалтын push_back функцыг дуудна
				*/
				l_push_back(p_list, x);
			}
			/*
			  тэмдэгтийг жагсаалтанд оруулах
			  Жагсаалтын push_back функцыг дуудна
			 */
			if (is_space(s[i])) /* хоосон зай, шинэ мөрийг хаяна. */
				continue;

			/*
			  Энд +, -, *, /, (, ) тэмдэгтүүдийг жагсаалтад оруулна.
			 */
			x.flag = 0;
			x.op = s[i];
			l_push_back(p_list, x);
		}
	}

	/* Тэмдэгтэн цуваанаас салгасан тэгшитгэлийг хэвлэх
	   Жагсаалтын print функцыг дуудна.
	 */
	/* l_print(p_list); */
}

// struct Elm {
//         int x;
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

// struct Token {
// 	int flag;    /*
// 				  flag = 1 бол уг объект тооны мэдээлэл val-д хадгална
// 				  flag = 0 бол уг объект op-д тэмдэгт хадгална
// 				 */
// 	int val;
// 	char op;
// };
// typedef struct Token Token;

// struct TokenElm {
//         Token x;
//         struct TokenElm *next;
// };
// typedef struct TokenElm TokenElm;

// // List бүтэц
// struct List {
//         TokenElm *head;
//         TokenElm *tail;
//         int len;
// };
// typedef struct List List;

// void l_push_back(List *, Token);
// void l_push_front(List *, Token);
// void l_insert(List *, Token, int);
// void l_pop_front(List *);
// void l_pop_back(List *);
// void l_erase(List *, int);
// void l_print(List *);

// // Postfix functions
// int convert_to_int(const char[]);
// void tokenize(const char[], List *);
// void convert_to_postfix(List *, List *);
// int solve(List *);
/*
  p_token - жагсаалтад байгаа тэгштгэлийг postfix-рүү хөрвүүлнэ
 */
void convert_to_postfix(List *p_token, List *p_post)
{
	if (p_token->len == 0)
		return;
	if (p_token->head == NULL)
		return;
	Stack s;
	s.top = NULL;
	s.len = 0;
	TokenElm *p = p_token->head;
	while (p != NULL)
	{
		if (p->x.flag == 1)
		{
			/* Тоо байгаа бол түүнийг postfix-д оруулна */
			l_push_back(p_post, p->x);
		}
		else
		{
			/* Тэмдэгт байгаа бол */
			if (p->x.op == '(')
			{
				/* ( байгаа бол */
				s_push(&s, p->x.op);
			}
			else if (p->x.op == ')')
			{
				/* ) байгаа бол */
				while (s.top->x != '(')
				{
					Token x;
					x.flag = 0;
					x.op = s.top->x;
					l_push_back(p_post, x);
					s_pop(&s);
				}
				s_pop(&s);
			}
			else
			{
				// * / % are higher than + -
				if (p->x.op == '*' || p->x.op == '/' || p->x.op == '%')
				{
					while (s.top != NULL && (s.top->x == '*' || s.top->x == '/' || s.top->x == '%'))
					{
						Token x;
						x.flag = 0;
						x.op = s.top->x;
						l_push_back(p_post, x);
						s_pop(&s);
					}
					s_push(&s, p->x.op);
				}
				else
				{
					while (s.top != NULL && (s.top->x == '*' || s.top->x == '/' || s.top->x == '%' || s.top->x == '+' || s.top->x == '-'))
					{
						Token x;
						x.flag = 0;
						x.op = s.top->x;
						l_push_back(p_post, x);
						s_pop(&s);
					}
					s_push(&s, p->x.op);
				}
			}
		}
		p = p->next;
	}
	while (s.len != 0)
	{
		Token x;
		x.flag = 0;
		x.op = s.top->x;
		l_push_back(p_post, x);
		s_pop(&s);
	}
}

int solve(List *p_post)
{
	if (p_post == NULL)
		return 0;
	Stack s;
	s.len = 0;
	s.top = NULL;
	TokenElm *p = p_post->head;
	while (p != NULL)
	{
		if (p->x.flag == 1)
		{
			s_push(&s, p->x.val);
		}
		else
		{
			int a = s.top->x;
			s_pop(&s);
			int b = s.top->x;
			s_pop(&s);
			if (p->x.op == '+')
			{
				s_push(&s, a + b);
			}
			else if (p->x.op == '-')
			{
				s_push(&s, b - a);
			}
			else if (p->x.op == '*')
			{
				s_push(&s, a * b);
			}
			else if (p->x.op == '/')
			{
				s_push(&s, b / a);
			}
			else if (p->x.op == '%')
			{
				s_push(&s, b % a);
			}
		}
		p = p->next;
	}
	return s.top->x;
}
