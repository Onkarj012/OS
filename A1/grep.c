#include <stdio.h>
#include <string.h>

// ./grep grep option pattern FILE

void grep(char *pattern, char *file)
{
    char buf[100];
    FILE *rptr = fopen(file, "r");

    if (rptr == NULL)
    {
        printf("Error opening file");
        return;
    }

    int found = 0;
    while (fscanf(rptr, "%s", buf) != EOF)
    {
        if (strstr(buf, pattern) != NULL)
        {
            found = 1;
        }
    }

    if (found == 1)
        printf("%s Found\n", pattern);
    else
        printf("%s Not Found\n", pattern);

    fclose(rptr);
    return;
}

void grepOption(char *pattern, char *file, char *option)
{
    char buf[100];
    FILE *rptr = fopen(file, "r");

    if (rptr == NULL)
    {
        perror("Error opening file\n");
        return;
    }

    int found = 0;
    int count = 0;
    while (fscanf(rptr, "%s", buf) != EOF)
    {
        if (strstr(buf, pattern) != NULL)
        {
            count++;
            found = 1;
        }
    }

    if (found == 1)
    {
        printf("%s Found\n", pattern);
        printf("In %d lines\n", count);
    }
    else
        printf("%s Not Found\n", pattern);

    fclose(rptr);
    return;
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Enter arguments properly!\n");
        return 0;
    }

    if (strcmp(argv[2], "-c") == 0)
    {
        char *option = argv[1];
        char *pattern = argv[2];
        char *readFile = argv[3];
        grepOption(pattern, readFile, option);
    }
    else
    {
        char *pattern = argv[1];
        char *readFile = argv[2];
        grep(pattern, readFile);
    }
    return 0;
}
