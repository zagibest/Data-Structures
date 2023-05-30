#include "sort.h"
/*
  Нийлүүлэн эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
 */
#define CUTOFF 10
/*
  a, b хаяганд хадгалагдсан сурагчдыг нэрээр жиших функц.
  a->name, b->name-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
*/
int nereer(const Student *a, const Student *b)
{
  return strcmp(a->name, b->name) < 0;
}
/*
  a, b хаяганд хадгалагдсан сурагчдыг насаар нь жиших функц.
  a->age, b->age-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
*/
int nasaar(const Student *a, const Student *b)
{
  if (a->age < b->age)
    return 1;
  else
    return 0;
}
/*
  a, b хаяганд хадгалагдсан сурагчдыг голчоор  нь жиших функц.
  a->gpa, b->gpa-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
*/
int golchoor(const Student *a, const Student *b)
{
  if (a->gpa < b->gpa)
    return 1;
  else
    return 0;
}
/*
  Оруулан эрэмбэлэх функц.
  Жиших үйлдлийг less функцэн заагчийг ашиглан хийнэ.
  Уг функц нь эрэмбэлэхдээ a хүснэгтийн lo-оос
  hi завсыг л зөвхөн эрэмбэлнэ.
*/
void insertion_sort(Student a[],
                    int lo, int hi,
                    int (*less)(const Student *, const Student *))
{
  int i, j;
  Student v;
  for (i = lo; i <= hi; i++)
  {
    v = a[i];
    j = i;
    while (j > lo && less(&v, &a[j - 1]))
    {
      a[j] = a[j - 1];
      j--;
    }
    a[j] = v;
  }
}
/*
  Нийлүүлсэн эрэмбэлэх аргын mege үйлдэл.
  Уг функц нь a хүснэгтэд [lo; mid], [mid+1; hi] завсарт
  эрэмбэлэгдсэн хүснэгтийг нийлүүлэн [lo; hi] завсарт эрэмбэлэгдсэн хүснэгт болгоно.
  aux хүснэгт нь нэмэлтээр ашиглах хүснэгт. Оюутнуудыг хооронд нь жишихдээ less функцэн
  заагчийг ашиглана.
*/
void merge(Student a[],
           Student aux[],
           int lo,
           int mid,
           int hi,
           int (*less)(const Student *, const Student *))
{
  int i, j, k;
  for (k = lo; k <= hi; k++)
    aux[k] = a[k];
  i = lo;
  j = mid + 1;
  for (k = lo; k <= hi; k++)
  {
    if (i > mid)
      a[k] = aux[j++];
    else if (j > hi)
      a[k] = aux[i++];
    else if (less(&aux[j], &aux[i]))
      a[k] = aux[j++];
    else
      a[k] = aux[i++];
  }
}
/*
  Нийлүүлсэн эрэмбэлэх функц.
  hi - lo <= CUTOFF бол оруулан эрэмбэлэх аргыг хэрэглэнэ.
  Жиших үйлдлийг less функцэн заагчийг ашиглан хийнэ.
  Уг функц нь merge, insertion_sort функцүүдийг дуудан ашиглах ёстой.
*/
void mergesort(Student a[],
               Student aux[],
               int lo,
               int hi,
               int (*less)(const Student *, const Student *))
{
  int mid = lo + (hi - lo) / 2;
  if (hi - lo <= CUTOFF)
  {
    insertion_sort(a, lo, hi, less);
    return;
  }
  mergesort(a, aux, lo, mid, less);
  mergesort(a, aux, mid + 1, hi, less);
  merge(a, aux, lo, mid, hi, less);
}