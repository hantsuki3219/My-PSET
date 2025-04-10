#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("fck %s cnt open\n", argv[1]);
        return 1;
    }
    // Create a buffer
    uint8_t buffer[512];
    int counter = 0;
    char filename[8];
    FILE *img = NULL; // For the jpeg that will be created after recovery
    // While there's still data left
    while (fread(buffer, sizeof(buffer), 1, card) == 1) // ตรวจสอบการอ่านบล็อก
    {
        // Create jpegs from the data
        // Check start point if jpeg or not
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If found new jpeg close for new one
            if (img != NULL)
            {
                fclose(img);
            }

            // Create file name for new jpeg
            sprintf(filename, "%03i.jpg", counter);
            // Open new jpeg file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create %s\n", filename);
                return 1;
            }
            counter++;
        }
        // Write jpeg file
        if (img != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }
    // Close any remaining jpeg file
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}