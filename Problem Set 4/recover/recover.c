#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    int counter = 0;
    unsigned char buffer[512];
    int read = 1;
    int first = 0;
    char *filename = malloc(10);
    sprintf(filename, "000.jpg");
    FILE *img;
    read = fread(&buffer, 512, 1, file);
    while (read == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer [2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first == 1)
            {
                fclose(img);
                counter++;
                if (counter < 10)
                {
                    sprintf(filename, "00%i.jpg", counter);
                }
                if (counter > 10 || counter == 10)
                {
                    sprintf(filename, "0%i.jpg", counter);
                }

                img = fopen(filename, "w");
                fwrite(&buffer, 512, 1, img);
            }
            if (first == 0)
            {
                img = fopen(filename, "w");
                fwrite(&buffer, 512, 1, img);
                first = 1;

            }

        }
        else if (first == 1)
        {
            fwrite(&buffer, 512, 1, img);
        }
        read = fread(&buffer, 512, 1, file);
    }

    fclose(img);
    fclose(file);
    free(filename);

}