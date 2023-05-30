#include "DS.h"

/* p-ийн зааж буй List-д x утгыг төгсгөлд хийнэ */
void l_push_back(List *p, int x)
{
  Elm *a;
  a = malloc(sizeof(struct Elm));
  a->x = x;
  if (p->head == NULL)
  {
    p->head = a;
    p->tail = a;
    p->tail->next = NULL;
  }
  else
  {
    p->tail->next = a;
    p->tail = a;
    p->tail->next = NULL;
  }
  p->len++;
}

/* p-ийн зааж буй List-д x утгыг эхэнд хийнэ
   Бүх элементүүд нэг нэг байрлал хойшилно.
 */
void l_push_front(List *p, int x)
{
  Elm *temp;
  temp = malloc(sizeof(struct Elm));
  temp->x = x;
  if (p->head == NULL)
  {
    p->head = temp;
    p->tail = temp;
  }
  else
  {
    temp->next = p->head;
    p->head = temp;
  }
  p->tail->next = NULL;
  p->len++;
}

/*
  p-ийн зааж буй List-д x утгыг pos байрлалд хийнэ
  pos болон түүнээс хойшхи элементүүд нэг байрлал ухарна.
  Тухайн байрлал List-ийн сүүлийн индексээс их бол төгсгөлд орно.
 */
void l_insert(List *p, int x, int pos)
{
  Elm *a;
  if (pos > p->len - 1)
  {
    l_push_back(p, x);
    return;
  }
  if (pos == 0)
  {
    l_push_front(p, x);
    return;
  }
  Elm *e = malloc(sizeof(struct Elm));
  e->x = x;
  a = p->head;
  int i = 0;
  while (i < pos - 1)
  {
    i++;
    a = a->next;
  }
  e->next = a->next;
  a->next = e;
  p->len++;
}
/*
  p-ийн зааж буй List-н эхлэлээс гаргана.
  List-ийн бүх элементүүд нэг нэг байрлал урагшилна
 */
void l_pop_front(List *p)
{
  if (p->head == NULL)
  {
    return;
  }
  else
  {
    Elm *e = p->head;
    e = e->next;
    free(p->head);
    p->head = e;
    p->len--;
  }
}

/* p-ийн зааж буй List-н төгсгөлөөс гаргана */
void l_pop_back(List *p)
{
  if (p->len == 1)
  {
    l_pop_front(p);
    return;
  }
  if (p->head == NULL)
  {
    return;
  }
  else
  {
    Elm *e;
    e = p->head;
    while (e->next != p->tail)
    {
      e = e->next;
    }
    free(p->tail);
    p->tail = e;
    p->tail->next = NULL;
  }
  p->len--;
}

/* p-ийн зааж буй List-н pos байрлалаас гаргана.
   pos болон түүнээс хойшхи элементүүд нэг байрлал урагшилна.
   pos байрлалаас гарах боломжгүй бол юу ч хийхгүй.
 */
void l_erase(List *p, int pos)
{
  if (pos == 0)
  {
    l_pop_front(p);
    return;
  }
  if (pos == p->len - 1)
  {
    l_pop_back(p);
    return;
  }
  if (p->len == 1)
  {
    l_pop_front(p);
  }

  if (pos > p->len - 1)
  {
    return;
  }

  if (p->head == NULL)
  {
    return;
  }
  else
  {
    Elm *e, *b;
    e = p->head;
    int i = 0;
    while (i < pos - 1)
    {
      i++;
      e = e->next;
    }
    b = e;
    b = b->next;
    e->next = b->next;
    free(b);
    p->len--;
  }
}

/*
  p-ийн зааж буй List-н утгуудыг хэвлэнэ.
  Хамгийн эхний элементээс эхлэн дарааллаар, нэг мөрөнд
  нэг л элемент хэвлэнэ.
 */
void l_print(List *p)
{
  if (p->head == NULL)
  {
    return;
  }
  else
  {
    Elm *a;
    a = p->head;
    while (a != NULL)
    {
      printf("%d\n", a->x);
      a = a->next;
    }
  }
}

/*
  p-ийн зааж буй List-с x тоог хайн олдсон хаягийг буцаана.
  Олдохгүй бол NULL хаяг буцаана.
 */
Elm *l_search(List *p, int x)
{
  if (p->head == NULL)
  {
    return NULL;
  }
  else
  {
    Elm *e;
    e = p->head;
    while (e != NULL)
    {
      if (e->x == x)
      {
        return e;
      }
      e = e->next;
    }
    return NULL;
  }
}