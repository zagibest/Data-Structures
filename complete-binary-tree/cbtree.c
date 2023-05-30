#include "DS.h"
#include <math.h>

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
        if (left >= p->cb_len)
                return -1;
        return left;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны баруун хүүгийн индексийг буцаана.
  Баруун хүү байхгүй бол -1 буцаана.
*/
int cb_right(const CBTree *p, int idx)
{
        int right = 2 * idx + 2;
        if (right >= p->cb_len)
                return -1;
        return right;
}

/*
  p-ийн зааж буй CBTree-с x тоог хайн
  хамгийн эхэнд олдсон индексийг буцаана.
  Олдохгүй бол -1 утгыг буцаана.
*/
int cb_search(const CBTree *p, int x)
{
        int i;
        for (i = 0; i < p->cb_len; i++)
        {
                if (p->cb_arr[i] == x)
                {
                        return i;
                }
        }
        return -1;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй зангилаанаас дээшхи бүх өвөг эцэгийг олох үйлдлийг хийнэ.
  Тухайн орой өөрөө өвөг эцэгт орохгүй.
  Өвөг эцэг бүрийг нэг шинэ мөрөнд хэвлэнэ. Өвөг эцэгийг доороос дээшхи дарааллаар хэвлэнэ.
*/
void cb_ancestors(const CBTree *p, int idx)
{
        // print ancestors
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
        int i = 0;
        int height = 0;
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
        if (idx == 0)
                return -1;
        int parent = (idx - 1) / 2;
        int left = 2 * parent + 1;
        int right = 2 * parent + 2;
        if (left == idx)
        {
                if (right >= p->cb_len)
                        return -1;
                return right;
        }
        else
        {
                if (left >= p->cb_len)
                        return -1;
                return left;
        }
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн preorder-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_preorder(const CBTree *p, int idx)
{
        // preorder traversal of the complete binary tree
        if (idx < p->cb_len)
        {
                printf("%d\n", p->cb_arr[idx]);
                cb_preorder(p, 2 * idx + 1);
                cb_preorder(p, 2 * idx + 2);
        }
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн in-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_inorder(const CBTree *p, int idx)
{
        // inorder traversal of the complete binary tree
        if (idx < p->cb_len)
        {
                cb_inorder(p, 2 * idx + 1);
                printf("%d\n", p->cb_arr[idx]);
                cb_inorder(p, 2 * idx + 2);
        }
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн post-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
 */
void cb_postorder(const CBTree *p, int idx)
{
        // postorder traversal of the complete binary tree
        if (idx < p->cb_len)
        {
                cb_postorder(p, 2 * idx + 1);
                cb_postorder(p, 2 * idx + 2);
                printf("%d\n", p->cb_arr[idx]);
        }
}

/*
  p-ийн зааж буй CBTree-с idx дугаартай зангилаанаас доошхи бүх навчийг олно.
  Навч тус бүрийн утгыг шинэ мөрөнд хэвлэнэ.
  Навчыг зүүнээс баруун тийш олдох дарааллаар хэвлэнэ.
*/
void cb_leaves(const CBTree *p, int idx)
{
        // print all leaves from node at index idx in the complete binary tree
        if (idx < p->cb_len)
        {
                if (2 * idx + 1 >= p->cb_len && 2 * idx + 2 >= p->cb_len)
                {
                        printf("%d\n", p->cb_arr[idx]);
                }
                cb_leaves(p, 2 * idx + 1);
                cb_leaves(p, 2 * idx + 2);
        }
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройноос доошхи бүх үр садыг хэвлэнэ.
  Тухайн орой өөрөө үр сад болохгүй.
  Үр, сад бүрийг нэг шинэ мөрөнд хэвлэнэ. Үр садыг pre-order дарааллаар хэлэх ёстой.
*/
void cb_descendants(const CBTree *p, int idx)
{
        // print all descendants of node at index idx in the complete binary tree
        if (idx < p->cb_len)
        {
                if (2 * idx + 1 < p->cb_len)
                {
                        printf("%d\n", p->cb_arr[2 * idx + 1]);
                        cb_descendants(p, 2 * idx + 1);
                }
                if (2 * idx + 2 < p->cb_len)
                {
                        printf("%d\n", p->cb_arr[2 * idx + 2]);
                        cb_descendants(p, 2 * idx + 2);
                }
        }
}

/*
  p-ийн зааж буй Tree-д хэдэн элемент байгааг буцаана.
  CBTree-д өөрчлөлт оруулахгүй.
*/
int cb_size(const CBTree *p)
{
        // return the number of elements in the complete binary tree
        return p->cb_len;
}

/*
  p-ийн зааж буй CBTree-д x утгаас үндэс хүртэлх оройнуудын тоог буцаана.
  x тоо олдохгүй бол -1-г буцаана.
*/
int cb_level(const CBTree *p, int x)
{
        int i;
        for (i = 0; i < p->cb_len; i++)
        {
                if (p->cb_arr[i] == x)
                {
                        return (int)log2(i + 1);
                }
        }
        return -1;
}