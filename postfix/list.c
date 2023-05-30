#include "DS.h"

/* p-ийн зааж буй List-д x утгыг төгсгөлд хийнэ */
void l_push_back(List *p, Token x)
{
  TokenElm *q = (TokenElm *)malloc(sizeof(TokenElm));
  q->x = x;
  q->next = NULL;
  if (p->head == NULL)
  {
    p->head = q;
    p->tail = q;
  }
  else
  {
    p->tail->next = q;
    p->tail = q;
  }
  p->len++;
}

/* p-ийн зааж буй List-д x утгыг эхэнд хийнэ
   Бүх элементүүд нэг нэг байрлал хойшилно.
 */
void l_push_front(List *p, Token x)
{
  TokenElm *q = (TokenElm *)malloc(sizeof(TokenElm));
  q->x = x;
  q->next = p->head;
  p->head = q;
  if (p->tail == NULL)
  {
    p->tail = q;
  }
  p->len++;
}

/*
  p-ийн зааж буй List-д x утгыг pos байрлалд хийнэ
  pos болон түүнээс хойшхи элементүүд нэг байрлал ухарна.
  Тухайн байрлал List-ийн сүүлийн индексээс их бол төгсгөлд орно.
 */
void l_insert(List *p, Token x, int pos)
{
  if (pos == 0)
  {
    l_push_front(p, x);
    return;
  }
  if (pos >= p->len)
  {
    l_push_back(p, x);
    return;
  }
  TokenElm *q = (TokenElm *)malloc(sizeof(TokenElm));
  q->x = x;
  TokenElm *r = p->head;
  for (int i = 0; i < pos - 1; i++)
  {
    r = r->next;
  }
  q->next = r->next;
  r->next = q;
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
  TokenElm *q = p->head;
  p->head = p->head->next;
  free(q);
  p->len--;
  if (p->len == 0)
  {
    p->tail = NULL;
  }
}

/* p-ийн зааж буй List-н төгсгөлөөс гаргана */
void l_pop_back(List *p)
{
  if (p->tail == NULL)
  {
    return;
  }
  if (p->head == p->tail)
  {
    free(p->head);
    p->head = NULL;
    p->tail = NULL;
    p->len = 0;
    return;
  }
  TokenElm *q = p->head;
  while (q->next != p->tail)
  {
    q = q->next;
  }
  free(p->tail);
  p->tail = q;
  q->next = NULL;
  p->len--;
}

/* p-ийн зааж буй List-н pos байрлалаас гаргана.
   pos болон түүнээс хойшхи элементүүд нэг байрлал урагшилна.
   pos байрлалаас гарах боломжгүй бол юу ч хийхгүй.
 */
void l_erase(List *p, int pos)
{
  if (pos < 0 || pos >= p->len)
  {
    return;
  }
  if (pos == 0)
  {
    l_pop_front(p);
    return;
  }
  TokenElm *q = p->head;
  for (int i = 0; i < pos - 1; i++)
  {
    q = q->next;
  }
  TokenElm *r = q->next;
  q->next = r->next;
  free(r);
  p->len--;
  if (p->len == 0)
  {
    p->tail = NULL;
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
  TokenElm *e;
  e = p->head;
  while (e != NULL)
  {
    if (e->x.flag == 1)
    {
      printf("%d", e->x.val);
    }
    else
    {
      printf("%c", e->x.op);
    }
    e = e->next;
  }
  printf("\n");
}
