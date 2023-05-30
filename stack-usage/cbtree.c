#include "DS.h"

/*
  p-ийн зааж буй CBTree-д x утгыг оруулна
*/
void cb_push(CBTree *p, int x)
{
        p->cb_arr[p->cb_len] = x;
        p->cb_len++;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны зүүн хүүгийн индексийг буцаана.
  Зүүн хүү байхгүй бол -1 буцаана.
*/
int cb_left(const CBTree *p, int idx)
{
        int left = 2 * idx + 1;
        if (left < p->cb_len)
                return left;
        return -1;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны баруун хүүгийн индексийг буцаана.
  Баруун хүү байхгүй бол -1 буцаана.
*/
int cb_right(const CBTree *p, int idx)
{
        int right = 2 * idx + 2;
        if (right < p->cb_len)
                return right;
        return -1;
}

/*
  p-ийн зааж буй CBTree-с x тоог хайн
  хамгийн эхэнд олдсон индексийг буцаана.
  Олдохгүй бол -1 утгыг буцаана.
*/
int cb_search(const CBTree *p, int x)
{
        for (int i = 0; i < p->cb_len; i++)
                if (p->cb_arr[i] == x)
                        return i;
        return -1;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй зангилаанаас дээшхи бүх өвөг эцэгийг олох үйлдлийг хийнэ.
  Тухайн орой өөрөө өвөг эцэгт орохгүй.
  Өвөг эцэг бүрийг нэг шинэ мөрөнд хэвлэнэ. Өвөг эцэгийг доороос дээшхи дарааллаар хэвлэнэ.
*/
void cb_ancestors(const CBTree *p, int idx)
{
        // don't use recursion
        int i = idx;
        while (i > 0)
        {
                i = (i - 1) / 2;
                printf("%d\n", p->cb_arr[i]);
        }
}

/*
  p-ийн зааж буй CBTree-ийн өндрийг буцаана
*/
int cb_height(const CBTree *p)
{
        int height = 0;
        int i = 0;
        while (i < p->cb_len)
        {
                i = 2 * i + 1;
                height++;
        }
        return height;
}

/*
  p-ийн зааж буй CBTree-д idx оройны ах, дүү оройн дугаарыг буцаана.
  Тухайн оройн эцэгтэй адил эцэгтэй орой.
  Ах, дүү нь байхгүй бол -1-г буцаана.
*/
int cb_sibling(const CBTree *p, int idx)
{
        int parent = (idx - 1) / 2;
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        if (left == idx)
                return right;
        if (right == idx)
                return left;
        return -1;
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн preorder-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/

// struct Array {
//         int a[100];
//         int len;
// };

// // Стак
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
// // ...
// // List
// // ...

// // Complete Binary Tree
// struct CBTree {
//         struct Array tree;
// };
// typedef struct CBTree CBTree;
// #define cb_arr tree.a
// #define cb_len tree.len

// void cb_push(CBTree *, int);
// void cb_preorder(const CBTree *, int);
// void cb_inorder(const CBTree *, int);
// void cb_postorder(const CBTree *, int);
void cb_preorder(const CBTree *p, int idx)
{
        // complete binary tree preorder using stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        s_push(&s, idx);
        while (s.len > 0)
        {
                int i = s.top->x;
                s_pop(&s);
                printf("%d\n", p->cb_arr[i]);
                int right = cb_right(p, i);
                if (right >= 0)
                        s_push(&s, right);
                int left = cb_left(p, i);
                if (left >= 0)
                        s_push(&s, left);
        }
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн in-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_inorder(const CBTree *p, int idx)
{
        // complete binary tree inorder using stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        int i = idx;
        while (i >= 0 || s.len > 0)
        {
                while (i >= 0)
                {
                        s_push(&s, i);
                        i = cb_left(p, i);
                }
                i = s.top->x;
                s_pop(&s);
                printf("%d\n", p->cb_arr[i]);
                i = cb_right(p, i);
        }
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн post-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
 */
void cb_postorder(const CBTree *p, int idx)
{
        // complete binary tree postorder using stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        int i = idx;
        int last = -1;
        while (i >= 0 || s.len > 0)
        {
                while (i >= 0)
                {
                        s_push(&s, i);
                        i = cb_left(p, i);
                }
                i = s.top->x;
                int right = cb_right(p, i);
                if (right >= 0 && right != last)
                        i = right;
                else
                {
                        printf("%d\n", p->cb_arr[i]);
                        last = i;
                        s_pop(&s);
                        i = -1;
                }
        }
}

/*
  p-ийн зааж буй CBTree-с idx дугаартай зангилаанаас доошхи бүх навчийг олно.
  Навч тус бүрийн утгыг шинэ мөрөнд хэвлэнэ.
  Навчыг зүүнээс баруун тийш олдох дарааллаар хэвлэнэ.
*/
void cb_leaves(const CBTree *p, int idx)
{
        // use Stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        s_push(&s, idx);
        while (s.len > 0)
        {
                int i = s.top->x;
                s_pop(&s);
                int left = cb_left(p, i);
                int right = cb_right(p, i);
                if (left < 0 && right < 0)
                        printf("%d\n", p->cb_arr[i]);
                if (right >= 0)
                        s_push(&s, right);
                if (left >= 0)
                        s_push(&s, left);
        }
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройноос доошхи бүх үр садыг хэвлэнэ.
  Тухайн орой өөрөө үр сад болохгүй.
  Үр, сад бүрийг нэг шинэ мөрөнд хэвлэнэ. Үр садыг pre-order дарааллаар хэлэх ёстой.
*/
void cb_descendants(const CBTree *p, int idx)
{
        // use Stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        s_push(&s, idx);
        while (s.len > 0)
        {
                int i = s.top->x;
                s_pop(&s);
                printf("%d\n", p->cb_arr[i]);
                int right = cb_right(p, i);
                if (right >= 0)
                        s_push(&s, right);
                int left = cb_left(p, i);
                if (left >= 0)
                        s_push(&s, left);
        }
}

/*
  p-ийн зааж буй Tree-д хэдэн элемент байгааг буцаана.
  CBTree-д өөрчлөлт оруулахгүй.
*/
int cb_size(const CBTree *p)
{
        // use Stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        int i = 0;
        s_push(&s, i);
        int count = 0;
        while (s.len > 0)
        {
                i = s.top->x;
                s_pop(&s);
                count++;
                int right = cb_right(p, i);
                if (right >= 0)
                        s_push(&s, right);
                int left = cb_left(p, i);
                if (left >= 0)
                        s_push(&s, left);
        }
        return count;
}

/*
  p-ийн зааж буй CBTree-д x утгаас үндэс хүртэлх оройнуудын тоог буцаана.
  x тоо олдохгүй бол -1-г буцаана.
*/
int cb_level(const CBTree *p, int x)
{
        // use Stack
        Stack s;
        s.top = NULL;
        s.len = 0;
        s_push(&s, 0);
        int level = 0;
        while (s.len > 0)
        {
                int i = s.top->x;
                s_pop(&s);
                if (p->cb_arr[i] == x)
                        return level;
                int right = cb_right(p, i);
                if (right >= 0)
                        s_push(&s, right);
                int left = cb_left(p, i);
                if (left >= 0)
                        s_push(&s, left);
                if (i == 0)
                        level++;
        }
        return -1;
}
