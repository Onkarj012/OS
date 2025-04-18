#include <stdio.h>

// ./copy first second

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Enter arguments properly!\n");
        return 0;
    }

    char buf[100];
    char *firstFile = argv[1];
    char *secondFile = argv[2];
    FILE *rptr = fopen(firstFile, "r");
    FILE *wptr = fopen(secondFile, "w");

    if (rptr == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    while (fscanf(rptr, "%s", buf) == 1)
    {
        fprintf(wptr, "%s ", buf);
    }

    printf("\n!!!!!!!!!File copied successfully!!!!!!!!!\n");

    fclose(rptr);
    return 0;
}
