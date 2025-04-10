#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
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
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = 0.393 * red + 0.769 * green + 0.189 * blue;
            int sepiaGreen = 0.349 * red + 0.686 * green + 0.168 * blue;
            int sepiaBlue = 0.272 * red + 0.534 * green + 0.131 * blue;

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
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflct;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            reflct = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = reflct;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_rep[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;
            for (int update_i = i - 1; update_i < i + 2; update_i++)
            {
                for (int update_j = j - 1; update_j < j + 2; update_j++)
                {
                    if (update_i >= 0 && update_j >= 0 && update_i < height && update_j < width)
                    {
                        sumRed += image[update_i][update_j].rgbtRed;
                        sumGreen += image[update_i][update_j].rgbtGreen;
                        sumBlue += image[update_i][update_j].rgbtBlue;
                        count++;
                    }
                }
            }

            img_rep[i][j].rgbtRed = round(sumRed / (float)count);
            img_rep[i][j].rgbtGreen = round(sumGreen / (float)count);
            img_rep[i][j].rgbtBlue = round(sumBlue / (float)count);
        }
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = img_rep[i][j];
        }
    }
    return;
}