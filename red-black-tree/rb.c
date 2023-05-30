#include "DS.h"
/*
  Хоёр оюутны мэдээллийн хооронд нь харьцуулах функц
*/
int less(const Student *a, const Student *b)
{
        return strcmp(a->id, b->id) < 0;
}
/*
  `pointerTree`-ийн зааж байгаа модонд `x` утгыг оруулна.
  Мод хоосон байсан бол `pointerTree->root` хаяг өөрчлөгдөж шинээр орсон оройг заана.
  Хэрэв мод тэнцвэрээ алдсан бол тохирох тэнцвэржүүлэх үйлдлүүдийг хийнэ.
 */
void _rb_put(Elm **pointerTree, const Student *x)
{
        if (*pointerTree == NULL)
        {
                *pointerTree = (Elm *)malloc(sizeof(Elm));
                (*pointerTree)->x = *x;
                (*pointerTree)->color = 1;
                (*pointerTree)->L = (*pointerTree)->R = NULL;
                return;
        }
        if (less(x, &(*pointerTree)->x))
        {
                _rb_put(&(*pointerTree)->L, x);
        }
        else
        {
                _rb_put(&(*pointerTree)->R, x);
        }
}

void rb_put(RBT *pointerTree, const Student *px)
{
        _rb_put(&pointerTree->root, px);
}

/*
  `pointerTree`-ийн зааж байгаа модноос `x` утгыг хайн олдсон оройн `Elm*` хаягийг буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
  Мод дандаа ялгаатай элементүүд хадгална гэж үзэж болно.
 */
Elm *_rb_get(Elm *pointerTree, const char x[])
{
        if (pointerTree == NULL)
                return NULL;

        if (strcmp(x, pointerTree->x.id) == 0)
                return pointerTree;

        if (strcmp(x, pointerTree->x.id) < 0)
        {
                return _rb_get(pointerTree->L, x);
        }
        else
        {
                return _rb_get(pointerTree->R, x);
        }
}

Elm *rb_get(const RBT *pointerTree, const char id[])
{
        return _rb_get(pointerTree->root, id);
}

/*
  Устгах функц: ТМноос `x` утгыг хайж олоод устгана.
  Олдохгүй бол юу ч хийхгүй.
  Хэрэв мод тэнцвэрээ алдсан бол тохирох тэнцвэржүүлэх үйлдлүүдийг хийнэ.
 */
void _rb_del(Elm **pointerTree, const char x[])
{
        if (*pointerTree == NULL)
                return;

        if (strcmp(x, (*pointerTree)->x.id) < 0)
        {
                _rb_del(&(*pointerTree)->L, x);
        }
        else if (strcmp(x, (*pointerTree)->x.id) > 0)
        {
                _rb_del(&(*pointerTree)->R, x);
        }
        else
        {
                if ((*pointerTree)->L == NULL && (*pointerTree)->R == NULL)
                {
                        free(*pointerTree);
                        *pointerTree = NULL;
                }
                else if ((*pointerTree)->L == NULL)
                {
                        Elm *tmp = *pointerTree;
                        *pointerTree = (*pointerTree)->R;
                        free(tmp);
                }
                else if ((*pointerTree)->R == NULL)
                {
                        Elm *tmp = *pointerTree;
                        *pointerTree = (*pointerTree)->L;
                        free(tmp);
                }
                else
                {
                        Elm *tmp = (*pointerTree)->R;
                        while (tmp->L != NULL)
                        {
                                tmp = tmp->L;
                        }
                        (*pointerTree)->x = tmp->x;
                        _rb_del(&(*pointerTree)->R, tmp->x.id);
                }
        }
}
void rb_del(RBT *pointerTree, const char id[])
{
        _rb_del(&pointerTree->root, id);
}

void print(Elm *p)
{
        if (p)
        {
                printf("%s %s %d %.1f\n", p->x.name, p->x.id, p->x.age, p->x.gpa);
        }
        else
        {
                printf("None\n");
        }
}