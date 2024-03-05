#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int n = 10;
    n = (argc > 1) ? atoi(argv[1]) : n;
    printf("n = %d\n", n);

    int flag = 1;
    flag = (argc > 2) ? atoi(argv[2]) : flag;
    srand((unsigned)getpid());

    switch (flag)
    {
    /* Random Sequence */
    case 1:
        for (int i = 0; i < n; i++)
        {
            printf(" %d ", 1 + rand() % 500);
        }
        break;
    case 2:
        for (int i = 0; i < n; i++)
        {
            printf(" %d ", (n - i));
        }
        break;
    default:
        for (int i = 0; i < n; i++)
        {
            printf(" %d ", (i + 1));
        }
        break;
    }
    printf("\n");
    return 0;
}