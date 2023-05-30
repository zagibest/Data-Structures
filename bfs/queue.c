#include "DS.h"

//
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

// // List
// struct List {
//         Elm *head;
//         Elm *tail;
//         int len;
// };
// typedef struct List List;

/* p-ийн зааж буй Queue-д x утгыг хийнэ */
void q_push(Queue *p, int x)
{
        Elm *e = (Elm *)malloc(sizeof(Elm));
        e->x = x;
        e->next = NULL;
        if (p->len == 0)
        {
                p->head = e;
                p->tail = e;
        }
        else
        {
                p->tail->next = e;
                p->tail = e;
        }
        p->len++;
}

/* p-ийн зааж буй Queue-с гаргана */
void q_pop(Queue *p)
{
        // pop p queue

        if (p->len == 0)
        {
                printf("Queue is empty");
        }
        else
        {
                Elm *e = p->head;
                p->head = p->head->next;
                free(e);
                p->len--;
        }
}

/*
  p-ийн зааж буй Queue-н утгуудыг хэвлэнэ.
  Хамгийн эхний элементээс эхлэн дарааллаар, нэг мөрөнд
  нэг л элемент хэвлэнэ.
 */
void q_print(Queue *p)
{
        // print p queue
        Elm *e = p->head;
        while (e != NULL)
        {
                printf("%d\n", e->x);
                e = e->next;
        }
}
