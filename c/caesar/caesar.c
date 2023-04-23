#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int i;
        for (i = 0; i < strlen(argv[1]); i++)

        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    else
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }

    string input = get_string("plaintext:  ");

    int k = atoi(argv[1]) % 26;
    printf("ciphertext: ");

    int j;
    int l;
    for (j = 0; j < strlen(input); j++)
    {
        if (isupper(input[j]))
        {
            l = ((input[j] - 64 + k) % 26);
            if (l == 0)
            {
                l = 26 + 64;
                printf("%c", l);
            }
            else
            {
                l += 64;
                printf("%c", l);
            }
        }
        else if (islower(input[j]))
        {
            l = ((input[j] - 96 + k) % 26);
            if (l == 0)
            {
                l = 26 + 96;
                printf("%c", l);
            }
            else
            {
                l += 96;
                printf("%c", l);
            }
        }
        else
        {
            printf("%c", input[j]);
        }
    }
    printf("\n");
    return 0;
}