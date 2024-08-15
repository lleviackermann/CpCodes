#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int a = -7;
    a = ~a;
    printf("%d\n", a);
    return 0;
}