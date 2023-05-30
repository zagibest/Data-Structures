#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int case_insensitive = 0;

char arr(char a)
{
        if (case_insensitive == 1 && a >= 'A' && a <= 'Z')
                return a + 32;
        else
                return a;
}

int hash(const char *s)
{
        int i, k = 0;
        for (i = 0; i < strlen(s); i++)
                k = (arr(s[i]) + (k * 256)) % 999997;
        return k;
}

int find(const char *buf, int n, int index, const char *pattern, int m, int pat_hash, int *pline)
{
        int i, j;
        int buf_h = 0;
        int k = 1;

                for (i = index; i < index + m; i++)
        {
                buf_h = (arr(buf[i]) + (buf_h * 256)) % 999997;
        }

        for (i = index; i <= n - m; i++)
        {
                for (j = 0; j < m; j++)
                {
                        if (arr(buf[i + j]) != arr(pattern[j]))
                        {
                                break;
                        }
                }

                if (j == m)
                {
                        return i;
                }
                if (i < n - m)
                {
                        buf_h = (256 * (buf_h - arr(buf[i]) * k) + arr(buf[i + m])) % 999997;
                        if (buf_h < 0)
                        {
                                buf_h = (buf_h + 999997);
                        }
                }

                if (buf[i] == '\n')
                {
                        (*pline)++;
                }
        }

        // Return -1 if the pattern was not found.
        return -1;
}

int main(int argc, char *argv[])
{
        // Аргументийн тоо ядаж 3 байх ёстой.
        if (argc < 3)
        {
                printf("%s [-i] pattern FILE", argv[0]);
                exit(-1);
        }

        const char *pattern;
        if (argc > 3 && strcmp("-i", argv[1]) == 0)
        {
                case_insensitive = 1; // Том жижгийг хайхрахгүй адил гэж үзнэ.
                pattern = argv[2];
        }
        else
                pattern = argv[1];

        FILE *fin;
        fin = fopen(argv[argc - 1], "r");
        if (fin == NULL)
        {
                printf("Error openning %s file", argv[argc - 1]);
                exit(-1);
        }
        int len = 0;
        char ch;
        while (!feof(fin))
        {
                ch = fgetc(fin);
                len++; // Файлд доторх тэмдэгтүүдийг тоолъё.
        }
        char *buf;
        buf = (char *)malloc(sizeof(char) * (len + 1)); // Энд тэмдэгтүүдийг хадгална
        fseek(fin, 0, SEEK_SET);                        // Файл заагчийг буцаад эхлэлд нь аваачна.
        int i = 0;
        while (!feof(fin))
                buf[i++] = fgetc(fin); // Өгөгдлийг уншиж байна.
        buf[len - 1] = 0;              /* тэмдэгт мөр төгсгөл заагч */

        int ret = -1;
        int line = 0;
        int pat_hash = hash(pattern); // hash кодыг тооцоолно
        int m = strlen(pattern);

        do
        {
                ret = find(buf, len - 1, ret + 1, pattern, m, pat_hash, &line);
                if (ret != -1)
                {
                        printf("%d: ", line);
                        /*
                          Олдсон газраас доошоо 5
                          дээшээ 5 тэмдэгтийг хэвлэнэ.
                         */
                        int L = ret - 5;
                        int R = ret + strlen(pattern) + 5;
                        if (L < 0)
                                L = 0;
                        if (R >= len)
                                R = len - 1;
                        for (i = L; i <= R; i++)
                                printf("%c", buf[i]);
                        printf("\n");
                }
        } while (ret != -1);

        free(buf);
        return 0;
}