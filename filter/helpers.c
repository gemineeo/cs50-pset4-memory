#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column
        for (int j = 0; j < width; j++)
        {
            int avgColor = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avgColor;
            image[i][j].rgbtGreen = avgColor;
            image[i][j].rgbtRed = avgColor;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // if even width
        if (width % 2 == 0)
        {
            // Iterate over each column
            for (int j = 0; j < (width / 2); j++)
            {
                tmp[i][j] = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = tmp[i][j];
            }
        }
        // if odd width
        else
        {
            // Iterate over each row
            for (int j = 0; j < ((width - 1) / 2); j++)
            {
                tmp[i][j] = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = tmp[i][j];
            }
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare temp variable
    RGBTRIPLE tmp[height][width];

    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column
        for (int j = 0; j < width; j++)
        {
            int avgBlue = 0;
            int avgGreen = 0;
            int avgRed = 0;
            // If top left corner
            if (i == 0 && j == 0)
            {
                avgBlue = round(((float)tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 4);
                avgGreen = round(((float)tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 4);
                avgRed = round(((float)tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 4);
            }
            // If top right corner
            else if (i == 0 && j == (width-1))
            {
                avgBlue = round(((float)tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue) / 4);
                avgGreen = round(((float)tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen) / 4);
                avgRed = round(((float)tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed) / 4);
            }
            // If top row
            else if (i == 0)
            {
                avgBlue = round(((float)tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 6);
                avgGreen = round(((float)tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 6);
                avgRed = round(((float)tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 6);
            }
            // If bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                avgBlue = round(((float)tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue) / 4);
                avgGreen = round(((float)tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen+ tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen) / 4);
                avgRed = round(((float)tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed) / 4);
            }
            // If bottom right corner
            else if (i == (height - 1) && j == (width - 1))
            {
                avgBlue = round(((float)tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue) / 4);
                avgGreen = round(((float)tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen) / 4);
                avgRed = round(((float)tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed) / 4);
            }
            // If bottom line
            else if (i == (height - 1))
            {
                avgBlue = round(((float)tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue) / 6);
                avgGreen = round(((float)tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen) / 6);
                avgRed = round(((float)tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed) / 6);
            }
            // If left colum
            else if (j == 0)
            {
                avgBlue = round(((float)tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 6);
                avgGreen = round(((float)tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 6);
                avgRed = round(((float)tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 6);
            }
            // If right column
            else if (j == (width - 1))
            {
                avgBlue = round(((float)tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue) / 6);
                avgGreen = round(((float)tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen) / 6);
                avgRed = round(((float)tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed) / 6);
            }
            // If inside
            else
            {
                avgBlue = round(((float)tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 9);
                avgGreen = round(((float)tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 9);
                avgRed = round(((float)tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 9);
            }
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
    return;
}