#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == 0)
    {
        printf("Could not open file.\n");
        return 1;
    }

    unsigned char buffer[512];

    FILE *output = 0;

    char *filename = malloc(8 * sizeof(char));

    int count = 0;

    while (fread(buffer, sizeof(char), 512, input))
    {
        if (buffer[0] == 255 && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(count ==0)
            {
                sprintf(filename, "%03i.jpg",count);
                output = fopen(filename, "w");
                count++;
            }
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", count);
                output = fopen(filename, "w");

                count++;
            }
        }

        if (output != 0)
        {
            fwrite(buffer, sizeof(char), 512, output);

        }

    }

    free(filename);
    fclose(input);
    fclose(output);

}

//if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)