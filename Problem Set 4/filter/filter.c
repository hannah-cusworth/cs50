#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //for some reason i'm still getting a stupid rounding issue here...............................
            float average = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            average = average / 3;
            int rounded = rintf(average);
            image[i][j].rgbtBlue = roundf(rounded);
            image[i][j].rgbtGreen = roundf(rounded);
            image[i][j].rgbtRed = roundf(rounded);
        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap;
    if (width % 2 != 0)
    {
        for (int i = 0; i < height; i++)
        {
            // printf("[i][0]Before: %i\n[i][width]Before: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            swap = image[i][0];
            image[i][0] = image[i][width - 1];
            image[i][width - 1] = swap;
            // printf("[i][0]After: %i\n[i][width]After: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            for (int j = 1; j < ((width / 2)  + 0.5); j++)
            {
                swap = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = swap;
            }
        }
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            // printf("[i][0]Before: %i\n[i][width]Before: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            swap = image[i][0];
            image[i][0] = image[i][width - 1];
            image[i][width - 1] = swap;
            // printf("[i][0]After: %i\n[i][width]After: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            for (int j = 1; j < (width / 2); j++)
            {
                swap = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = swap;
            }
        }
    }

    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int Red;
        int Blue;
        int Green;
    }
    temp;
    temp image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averageR = image[i][j].rgbtRed;
            float averageG = image[i][j].rgbtGreen;
            float averageB = image[i][j].rgbtBlue;
            int counter = 1;

            // 7
            if (i != 0)
            {
                averageR += image[i - 1][j].rgbtRed;
                averageB += image[i - 1][j].rgbtBlue;
                averageG += image[i - 1][j].rgbtGreen;
                counter++;
            }
            //4
            if (j != 0)
            {
                averageR += image[i][j - 1].rgbtRed;
                averageB += image[i][j - 1].rgbtBlue;
                averageG += image[i][j - 1].rgbtGreen;
                counter++;
            }
            //2
            if (i != (height - 1))
            {
                averageR += image[i + 1][j].rgbtRed;
                averageB += image[i + 1][j].rgbtBlue;
                averageG += image[i + 1][j].rgbtGreen;
                counter++;
            }
            //5
            if (j != (width - 1))
            {
                averageR += image[i][j + 1].rgbtRed;
                averageB += image[i][j + 1].rgbtBlue;
                averageG += image[i][j + 1].rgbtGreen;
                counter++;
            }
            //1
            if ((i != 0) && (j != 0))
            {
                averageR += image[i - 1][j - 1].rgbtRed;
                averageB += image[i - 1][j - 1].rgbtBlue;
                averageG += image[i - 1][j - 1].rgbtGreen;
                counter++;
            }
            //3
            if ((i != 0) && (j != (width - 1)))
            {
                averageR += image[i - 1][j + 1].rgbtRed;
                averageB += image[i - 1][j + 1].rgbtBlue;
                averageG += image[i - 1][j + 1].rgbtGreen;
                counter++;
            }
            //6
            if ((i != (height - 1)) && (j != 0))
            {
                averageR += image[i + 1][j - 1].rgbtRed;
                averageB += image[i + 1][j - 1].rgbtBlue;
                averageG += image[i + 1][j - 1].rgbtGreen;
                counter++;
            }
            //8
            if ((i != (height - 1)) && (j != (width - 1)))
            {
                averageR += image[i + 1][j + 1].rgbtRed;
                averageB += image[i + 1][j + 1].rgbtBlue;
                averageG += image[i + 1][j + 1].rgbtGreen;
                counter++;
            }

            averageR = averageR / counter;
            averageB = averageB / counter;
            averageG = averageG / counter;
            image2[i][j].Red = roundf(averageR);
            image2[i][j].Blue = roundf(averageB);
            image2[i][j].Green = roundf(averageG);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].Red;
            image[i][j].rgbtBlue = image2[i][j].Blue;
            image[i][j].rgbtGreen = image2[i][j].Green;
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int Red;
        int Blue;
        int Green;
    }
    temp;
    temp image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {


            float GxR = 0;
            float GyR = 0;
            float GxG = 0;
            float GyG = 0;
            float GxB = 0;
            float GyB = 0;

            // 2
            if (i != 0)
            {
                GyR += (-2 * image[i - 1][j].rgbtRed);
                GyB += (-2 * image[i - 1][j].rgbtBlue);
                GyG += (-2 * image[i - 1][j].rgbtGreen);
            }
            //4
            if (j != 0)
            {
                GxR += (-2 * image[i][j - 1].rgbtRed);
                GxB += (-2 * image[i][j - 1].rgbtBlue);
                GxG += (-2 * image[i][j - 1].rgbtGreen);
            }
            //7
            if (i != (height - 1))
            {
                GyR += (2 * image[i + 1][j].rgbtRed);
                GyB += (2 * image[i + 1][j].rgbtBlue);
                GyG += (2 * image[i + 1][j].rgbtGreen);
            }
            //5
            if (j != (width - 1))
            {
                GxR += (2 * image[i][j + 1].rgbtRed);
                GxB += (2 * image[i][j + 1].rgbtBlue);
                GxG += (2 * image[i][j + 1].rgbtGreen);
            }
            //1
            if ((i != 0) && (j != 0))
            {
                GxR += (-1 * image[i - 1][j - 1].rgbtRed);
                GxB += (-1 * image[i - 1][j - 1].rgbtBlue);
                GxG += (-1 * image[i - 1][j - 1].rgbtGreen);
                GyR += (-1 * image[i - 1][j - 1].rgbtRed);
                GyB += (-1 * image[i - 1][j - 1].rgbtBlue);
                GyG += (-1 * image[i - 1][j - 1].rgbtGreen);
            }
            //3
            if ((i != 0) && (j != (width - 1)))
            {
                GxR += image[i - 1][j + 1].rgbtRed;
                GxB += image[i - 1][j + 1].rgbtBlue;
                GxG += image[i - 1][j + 1].rgbtGreen;
                GyR += (-1 * image[i - 1][j + 1].rgbtRed);
                GyB += (-1 * image[i - 1][j + 1].rgbtBlue);
                GyG += (-1 * image[i - 1][j + 1].rgbtGreen);
            }
            //6
            if ((i != (height - 1)) && (j != 0))
            {
                GxR += (-1 * image[i + 1][j - 1].rgbtRed);
                GxB += (-1 * image[i + 1][j - 1].rgbtBlue);
                GxG += (-1 * image[i + 1][j - 1].rgbtGreen);
                GyR += image[i + 1][j - 1].rgbtRed;
                GyB += image[i + 1][j - 1].rgbtBlue;
                GyG += image[i + 1][j - 1].rgbtGreen;
            }
            //8
            if ((i != (height - 1)) && (j != (width - 1)))
            {
                GxR += image[i + 1][j + 1].rgbtRed;
                GxB += image[i + 1][j + 1].rgbtBlue;
                GxG += image[i + 1][j + 1].rgbtGreen;
                GyR += image[i + 1][j + 1].rgbtRed;
                GyB += image[i + 1][j + 1].rgbtBlue;
                GyG += image[i + 1][j + 1].rgbtGreen;
            }
            float SobelR = sqrt((GxR * GxR) + (GyR * GyR));
            float SobelB = sqrt((GxB * GxB) + (GyB * GyB));
            float SobelG = sqrt((GxG * GxG) + (GyG * GyG));
            image2[i][j].Red = round(SobelR);
            image2[i][j].Blue = round(SobelB);
            image2[i][j].Green = round(SobelG);

            if (image2[i][j].Red > 255)
            {
                image2[i][j].Red = 255;
            }
            if (image2[i][j].Blue > 255)
            {
                image2[i][j].Blue = 255;
            }
            if (image2[i][j].Green > 255)
            {
                image2[i][j].Green = 255;
            }
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].Red;
            image[i][j].rgbtBlue = image2[i][j].Blue;
            image[i][j].rgbtGreen = image2[i][j].Green;
        }
    }

    return;
}