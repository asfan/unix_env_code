/**
 * code for gdb practice
 *
 * author:  asfan
 * date:    2018-03-20
 */

#include <stdio.h>

int func(int n)
{
    int sum = 0, i = 0;

    for (; i < n; i++)
    {
        sum += i;
    }

    return sum;
}


int main (int argc, char* argv[])
{
    int i;
    long result = 0;

    for (i = 0; i <= 100; i++)
    {
        result += i;
    }

    printf("result[1-100] = %ld \n", result);
    printf("result[1-250] = %d \n", func(250));

    return 0;
}
