#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 10

int load_file(char *buffer, FILE *file)
{
    for (int i = 0; i < BUFLEN; i++)
        buffer[i] = 0;

    int i = 0;
    char c;
    while ((c = getc(file)) != EOF)
    {
        buffer[i] = c;
        i++;
    }

    return i;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int min(int a, int b, int c)
{
    int mi;

    mi = a;
    if (b < mi)
    {
        mi = b;
    }
    if (c < mi)
    {
        mi = c;
    }
    return mi;
}

int levenstein(int len_a, int len_b, char *a, char *b)
{

    // Output matrix
    int dm[len_a + 1][len_b + 1];

    for (int i = 0; i <= len_a; i++)
        dm[i][0] = i;

    for (int i = 0; i <= len_b; i++)
        dm[0][i] = i;

    for (int y = 1; y <= len_a; y++)
    {
        char j = a[y - 1];

        for (int x = 1; x <= len_b; x++)
        {
            char t = b[x - 1];
            int c = t == j ? 0 : 1;
            dm[y][x] = min(dm[y - 1][x] + 1, dm[y][x - 1] + 1, dm[y - 1][x - 1] + c);
        }
    }

    return dm[len_a][len_b];
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Wrong input please use it as 'levenstein <fileA> <fileB>'\n");
        exit(1);
    }

    char *path_a = argv[1];
    char *path_b = argv[2];

    FILE *file_a = fopen(path_a, "r");
    FILE *file_b = fopen(path_b, "r");

    char buffer_a[BUFLEN + 1];
    char buffer_b[BUFLEN + 1];

    int len_a = load_file(buffer_a, file_a);
    int len_b = load_file(buffer_b, file_b);

    printf("Levenstein dist %i", levenstein(len_a, len_b, buffer_a, buffer_b));
}