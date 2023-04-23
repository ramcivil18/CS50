#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("positive number: ");

    }
    while ((n < 1 || n > 8));

    int i, j, z, k;
    z = n - 2;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (j > z)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }

        }
        z--;
        printf("  ");
        while (k <= i)
        {
            printf("#");
            k++;
        }
        k = 0;
        printf("\n");

    }


}