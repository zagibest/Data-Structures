#include "sort.h"
void read(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
}

void print(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void insertion_sort(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = i; j > 0 && a[j] < a[j - 1]; j--)
		{
			int tmp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = tmp;
		}
	}
}

void selection_sort(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		int m = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[m])
				m = j;
		int tmp = a[i];
		a[i] = a[m];
		a[m] = tmp;
	}
}

void bubble_sort(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n - i - 1; j++)
			if (a[j] > a[j + 1])
			{
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
}
