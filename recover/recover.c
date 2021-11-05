#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
#define FINE_NAME_SIZE 8

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // If no argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    // Variables declaration
    BYTE buffer[BLOCK_SIZE];
    int index = 0;
    FILE *img = NULL;

    // Repeat until end of card:
    // Red 512 bytes into a buffer
    while (fread(buffer, BLOCK_SIZE, 1, file) != 0)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If JPEG already found in the past
            if (index != 0)
            {
                // Close the file we've just writing to
                fclose(img);
            }
            else
            {
                index++;
            }
            // Create new img
            char filename[FINE_NAME_SIZE];
            sprintf(filename, "%03i.jpg", index - 1);
            index++;
            img = fopen(filename, "w");
            if (img == NULL)
            {
                return 1;
            }
            // Write data
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
        // ELSE If not start of new JPEG and JPEG already found
        else if (index > 0)
        {
            // Keep writing to img
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    // Close any remaining files
    fclose(img);
    fclose(file);

    // Success
    return 0;
}