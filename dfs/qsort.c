#include "my_qsort.h"

/*
  quicksort эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
*/
#ifndef CUTOFF
#define CUTOFF 10
#endif

static int init_seed = 0; // Random seed 1 удаа эхлүүлнэ

/*
  Оруулан эрэмбэлэх функц.
  [lo, hi] завсрах тоонуудыг оруулан эрэмбэлэх аргаар эрэмбэлнэ.
*/
static void insertion_sort(int a[], int lo, int hi)
{
        int i, j, x;
        for (i = lo + 1; i <= hi; i++)
        {
                x = a[i];
                for (j = i - 1; j >= lo && a[j] > x; j--)
                        a[j + 1] = a[j];
                a[j + 1] = x;
        }
}

/*
  Хоёр утгыг хооронд солих функц
*/
static void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

/*
  [lo, hi] завсрыг санамсаргүйгээр холих функц.
*/
static void random_shuffle(int a[], int lo, int hi)
{
        if (init_seed == 0)
        {
                srand(time(NULL));
                init_seed = 1;
        }
        int i, j;
        for (i = lo; i <= hi; i++)
        {
                j = rand() % (hi - lo) + lo;
                swap(&a[i], &a[j]);
        }
}

/*
  1-pivot хурдан эрэмбэлэх функц.
*/
static void _single_pivot_qsort(int a[], int lo, int hi)
{
        int i, j, pivot;

        if (hi - lo + 1 <= CUTOFF)
        {
                insertion_sort(a, lo, hi);
                return;
        }

        random_shuffle(a, lo, hi);
        pivot = a[lo];
        i = lo;
        j = hi + 1;
        while (1)
        {
                while (a[++i] < pivot)
                        if (i == hi)
                                break;
                while (a[--j] > pivot)
                        if (j == lo)
                                break;
                if (i >= j)
                        break;
                swap(&a[i], &a[j]);
        }
        swap(&a[lo], &a[j]);
        _single_pivot_qsort(a, lo, j - 1);
        _single_pivot_qsort(a, j + 1, hi);
}

/*
  wrapper function for _single_pivot_qsort
  _single_pivot_qsort-ыг дуудахад ашиглах функц
 */
void single_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _single_pivot_qsort(a, lo, hi);
}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi)
{
        int i, j, k, p, q, tmp;

        if (hi - lo + 1 <= CUTOFF)
        {
                insertion_sort(a, lo, hi);
                return;
        }

        random_shuffle(a, lo, hi);

        if (a[lo] > a[hi])
                swap(&a[lo], &a[hi]);
        p = a[lo];
        q = a[hi];

        i = lo + 1;
        j = hi - 1;
        k = lo + 1;

        while (k <= j)
        {
                if (a[k] < p)
                {
                        swap(&a[i], &a[k]);
                        i++;
                        k++;
                }
                else if (a[k] >= q)
                {
                        while (a[j] > q && k < j)
                                j--;
                        swap(&a[k], &a[j]);
                        j--;
                        if (a[k] < p)
                        {
                                swap(&a[i], &a[k]);
                                i++;
                        }
                        k++;
                }
                else
                        k++;
        }
        i--;
        j++;
        swap(&a[lo], &a[i]);
        swap(&a[hi], &a[j]);

        _dual_pivot_qsort(a, lo, i - 1);
        _dual_pivot_qsort(a, i + 1, j - 1);
        _dual_pivot_qsort(a, j + 1, hi);
}
/*
  wrapper function for _dual_pivot_qsort
  _dual_pivot_qsort-ыг дуудахад ашиглах функц
*/
void dual_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _dual_pivot_qsort(a, lo, hi);
}
