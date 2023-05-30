#include "DS.h"
/*
  p-ийн зааж буй Stack-т x утгыг оруулна
 */
void s_push(Stack *p, int x)
{
        Elm *e = (Elm *)malloc(sizeof(Elm));
        e->x = x;
        e->next = NULL;
        if (p->len == 0)
        {
                p->top = e;
        }
        else
        {
                e->next = p->top;
                p->top = e;
        }
        p->len++;
}
/*
  p-ийн зааж буй Stack-аас гарах функц
 */
void s_pop(Stack *p)
{
        if (p->len == 0)
        {
                printf("Stack is empty");
                return;
        }
        Elm *e = p->top;
        p->top = p->top->next;
        free(e);
        p->len--;
}
/*
    p-ийн зааж буй Stack-д байгаа элементүүдийг хэвлэх функц.
    Хамгийн сүүлд орсон элементээс эхлэн дарааллаар, нэг мөрөнд
    нэг л элемент хэвлэнэ.
 */
void s_print(Stack *p)
{
        if (p->len == 0)
        {
                printf("Stack is empty");
                return;
        }
        Elm *e = p->top;
        while (e != NULL)
        {
                printf("%d\n", e->x);
                e = e->next;
        }
}
