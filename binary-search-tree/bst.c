#include "DS.h"

/*
  `ptree`-ийн зааж байгаа модонд `x` утгыг оруулна.
  Оруулахдаа хоёртын хайлтын модны зарчмаар оруулах бөгөөд оруулсан
  байрлалаас дээшхи өвөг эцгийн `len`, `height` утгууд өөрчлөгдөнө.
  Мод хоосон байсан бол `ptree->root` хаяг өөрчлөгдөж шинээр орсон оройг заана.
 */

Elm *elmCreate(int x)
{
        Elm *p = (Elm *)malloc(sizeof(Elm));
        p->x = x;
        p->height = p->len = 1;
        p->R = p->L = NULL;
        return p;
}

void sertBro(Elm *p, int x)
{
        if (p == NULL)
        {
                p = (Elm *)malloc(sizeof(Elm));
                p->x = x;
                p->L = p->R = NULL;
        }
        if (p->x > x)
        {
                if (p->L == NULL)
                {
                        p->L = elmCreate(x);
                }
                else
                        sertBro(p->L, x);
        }
        else
        {
                if (p->R == NULL)
                {
                        p->R = elmCreate(x);
                }
                else
                        sertBro(p->R, x);
        }

        int leftc = p->L == NULL ? 1 : p->L->height + 1;
        int rightc = p->R == NULL ? 1 : p->R->height + 1;
        p->height = leftc > rightc ? leftc : rightc;
        p->len++;
}

void bs_put(BST *ptree, int x)
{

        if (ptree->root == NULL)
        { // hervee root null buyu hooson mod bol x ni root bolno.
                ptree->root = elmCreate(x);
                return;
        }
        sertBro(ptree->root, x);
}

/*
  `ptree`-ийн зааж байгаа модноос `x` утгыг хайн олдсон оройн `Elm*` хаягийг буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
  Мод дандаа ялгаатай элементүүд хадгална гэж үзэж болно.
 */

Elm *getThat(Elm *p, int x)
{
        if (p == NULL || x == p->x)
                return p;
        if (x > p->x)
                return getThat(p->R, x);
        else
                return getThat(p->L, x);
}

Elm *bs_get(const BST *ptree, int x)
{
        getThat(ptree->root, x);
}

/*
  Устгах функц: ХХМноос `x` утгыг хайж олоод устгана.
  Олдохгүй бол юу ч хийхгүй.
 */

Elm *delete(Elm *p, int x)
{
        Elm *temp;
        if (p == NULL)
                return p;

        if (x < p->x)
                p->L = delete (p->L, x);

        else if (x > p->x)
                p->R = delete (p->R, x);
        else
        {
                if (p->L == NULL)
                {
                        temp = p->R;
                        return temp;
                }
                else if (p->R == NULL)
                {
                        temp = p->L;
                        return temp;
                }
                temp = p->R;
                while (temp->L != NULL)
                        temp = temp->L;

                p->x = temp->x;
                p->R = delete (p->R, p->x);
        }
        int leftc = p->L == NULL ? 1 : p->L->height + 1;
        int rightc = p->R == NULL ? 1 : p->R->height + 1;
        p->height = leftc > rightc ? leftc : rightc;
        p->len--;
        return p;
}

void bs_del(BST *ptree, int x)
{

        ptree->root = delete (ptree->root, x);
}

/*
  Хамгийн багыг устгах функц: ХХМноос хамгийг бага утгыг нь устгах функц.
  Устгасан утгыг буцаана.
 */
Elm *delmin(Elm *p)
{
        if (p->L == NULL)
        {
                return p->R;
        }
        p->L = delmin(p->L);
        p->len--;
        return p;
}

int bs_delMin(BST *ptree)
{
        Elm *p = ptree->root;
        Elm *q = NULL;
        while (p->L != NULL)
        {
                q = p;
                p = p->L;
        }
        int x = p->x;
        if (p->R == NULL)
        {
                if (q == NULL)
                {
                        ptree->root = NULL;
                }
                else
                {
                        q->L = NULL;
                }
        }
        else
        {
                if (q == NULL)
                {
                        ptree->root = p->R;
                }
                else
                {
                        q->L = p->R;
                }
        }
        free(p);
        p = ptree->root;
        while (p != NULL)
        {
                int lefth = (p->L == NULL) ? 0 : p->L->height;
                int rightL = (p->R == NULL) ? 0 : p->R->height;
                p->height = (lefth > rightL ? lefth : rightL) + 1;
                lefth = (p->L == NULL) ? 0 : p->L->len;
                rightL = (p->R == NULL) ? 0 : p->R->len;
                p->len = lefth + rightL + 1;
                p = (x < p->x) ? p->L : p->R;
        }
        return x;
}

/*
  ХХМыг inorder дарааллаар, нэг мөрөнд нэг утга хэвлэнэ.
 */
void _bs_inorder(Elm *p)
{
        if (p == NULL)
        {
                return;
        }
        _bs_inorder(p->L);
        printf("%d %d %d\n", p->x, p->len, p->height);
        _bs_inorder(p->R);
}

void bs_inorder(const BST *ptree)
{

        _bs_inorder(ptree->root);
}

/*
  ХХМноос `x` утгаас эрс бага буюу тэнцүү байх хэдэн орой байгааг олж буцаана.
  Өөрөөр хэлбэл хоёртын хайлтын модны утгуудыг өсөх дарааллаар байрлуулбал
  `x`-ийг оролцуулаад өмнө хэдэн тоо байх вэ? гэсэн үг.
  `x` утга заавал модонд байх албагүй.
 */

int _bs_rank(Elm *p, int x)
{
        if (p == NULL)
        {
                return 0;
        }
        if (p->x > x)
        {
                return _bs_rank(p->L, x);
        }
        int l = p->L == NULL ? 1 : p->L->len + 1;
        return l + _bs_rank(p->R, x);
}

int bs_rank(const BST *ptree, int x)
{

        if (ptree->root != NULL)
        {
                return _bs_rank(ptree->root, x);
        }
}

/*
  ХХМноос `x` утгатай оройг хайж олоод, тухайн оройд суурилсан
  дэд модонд хэдэн орой байгааг олж буцаана.
  Олдохгүй бол -1-ийг буцаана.
 */
int bs_size(const BST *ptree, int x)
{

        Elm *p = bs_get(ptree, x);
        return p == NULL ? -1 : p->len;
}

/*
  XXMноос `x`-ээс бага буюу тэнцүү байх хамгийн их утгын `Elm *` хаягийг олж буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
 */
Elm *bs_floor(const BST *ptree, int x)
{
        // binary searightch tree floor
        Elm *p = ptree->root;
        Elm *q = NULL;
        while (p != NULL)
        {
                if (x < p->x)
                {
                        p = p->L;
                }
                else if (x > p->x)
                {
                        q = p;
                        p = p->R;
                }
                else
                {
                        q = p;
                        break;
                }
        }
        return q;
}

/*
  XXMноос `x`-ээс их буюу тэнцүү байх хамгийн бага утгын `Elm *` хаягийг олж буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
 */
Elm *bs_ceiling(const BST *ptree, int x)
{
        // binary searightch tree ceiling
        Elm *p = ptree->root;
        Elm *q = NULL;
        while (p != NULL)
        {
                if (x < p->x)
                {
                        q = p;
                        p = p->L;
                }
                else if (x > p->x)
                {
                        p = p->R;
                }
                else
                {
                        q = p;
                        break;
                }
        }
        return q;
}

/*
  ХХМноос `x` утгатай оройг хайж олоод, тухайн оройд суурилсан
  дэд модны өндөр хэд байгааг олж буцаана. Олдохгүй бол -1-ийг буцаана.
 */
int bs_height(const BST *ptree, int x)
{

        Elm *p = bs_get(ptree, x);
        return p == NULL ? -1 : p->height;
}