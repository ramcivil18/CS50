#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg1 = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int avg = round(avg1);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflect[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = width; j > 0; j--)
        {
            reflect[i][width - j] = image[i][j - 1];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reflect[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red1 = 0;
            float green1 = 0;
            float blue1 = 0;
            int counter = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int currentx = i + k;
                    int currenty = j + l;
                    if (currentx < 0 || currentx >= height || currenty < 0 || currenty >= width)
                    {
                        continue;
                    }
                    else
                    {
                        red1 += image[currentx][currenty].rgbtRed;
                        green1 += image[currentx][currenty].rgbtGreen;
                        blue1 += image[currentx][currenty].rgbtBlue;
                        counter++;
                    }

                }
            }


            int red = round(red1 / counter);
            int green = round(green1 / counter);
            int blue = round(blue1 / counter);

            blur[i][j].rgbtRed = red;
            blur[i][j].rgbtGreen = green;
            blur[i][j].rgbtBlue = blue;


        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blur[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redx = 0;
            float greenx = 0;
            float bluex = 0;

            float redy = 0;
            float greeny = 0;
            float bluey = 0;

            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int currentx = i + k;
                    int currenty = j + l;

                    if (currentx < 0 || currentx >= height || currenty < 0 || currenty >= width)
                    {
                        continue;
                    }

                    redx += image[currentx][currenty].rgbtRed * Gx[k + 1][l + 1];
                    greenx += image[currentx][currenty].rgbtGreen * Gx[k + 1][l + 1];
                    bluex += image[currentx][currenty].rgbtBlue * Gx[k + 1][l + 1];

                    redy += image[currentx][currenty].rgbtRed * Gy[k + 1][l + 1];
                    greeny += image[currentx][currenty].rgbtGreen * Gy[k + 1][l + 1];
                    bluey += image[currentx][currenty].rgbtBlue * Gy[k + 1][l + 1];


                }

            }

            int red = round(sqrt((redx * redx) + (redy * redy)));
            int green = round(sqrt((greenx * greenx) + (greeny * greeny)));
            int blue = round(sqrt((bluex * bluex) + (bluey * bluey)));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            edges[i][j].rgbtRed = red;
            edges[i][j].rgbtGreen = green;
            edges[i][j].rgbtBlue = blue;

        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edges[i][j];
        }
    }
    return;
}
