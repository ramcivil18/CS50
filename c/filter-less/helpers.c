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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float orginalred = image[i][j].rgbtRed;
            float orginalgreen = image[i][j].rgbtGreen;
            float orginalblue = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * orginalred + 0.769 * orginalgreen + 0.189 * orginalblue);
            int sepiaGreen = round(0.349 * orginalred + 0.686 * orginalgreen + 0.168 * orginalblue);
            int sepiaBlue = round(0.272 * orginalred + 0.534 * orginalgreen + 0.131 * orginalblue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
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
