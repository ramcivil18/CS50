#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int i;
        for (i = 0; i < strlen(argv[1]); i++)

        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
            if (strlen(argv[1]) != 26)
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            for (int j = i + 1; j < strlen(argv[1]); j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Usage: ./substitution key\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    string input = get_string("plaintext:  ");
    printf("ciphertext: ");

    int j;
    int c;
    int k;
    for (j = 0; j < strlen(input); j++)
    {
        if (isupper(input[j]))
        {
            k = input[j] - 65;
            if (isupper(argv[1][k]))
            {
                c = argv[1][k];
                printf("%c", c);
            }
            else
            {
                c = (argv[1][k]) - 32;
                printf("%c", c);
            }
        }
        else if (islower(input[j]))
        {
            k = input[j] - 97;
            if (islower(argv[1][k]))
            {
                c = argv[1][k];
                printf("%c", c);
            }
            else
            {
                c = (argv[1][k]) + 32;
                printf("%c", c);
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