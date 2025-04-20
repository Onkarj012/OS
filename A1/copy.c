// This program copies the contents of one file to another.
// It takes two command line arguments: the source file and the destination file.

#include <stdio.h>

// Entry point of the program
int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is provided
    if (argc < 3)
    {
        printf("Enter arguments properly!\n");
        return 0;
    }

    char buf[100];                       // Buffer to store file content temporarily
    char *firstFile = argv[1];           // Source file name
    char *secondFile = argv[2];          // Destination file name
    FILE *rptr = fopen(firstFile, "r");  // Open source file for reading
    FILE *wptr = fopen(secondFile, "w"); // Open destination file for writing

    // Check if the source file was opened successfully
    if (rptr == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    // Read from source file and write to destination file
    while (fscanf(rptr, "%s", buf) == 1)
    {
        fprintf(wptr, "%s ", buf);
    }

    printf("\n!!!!!!!!!File copied successfully!!!!!!!!!\n");

    fclose(rptr); // Close the source file
    return 0;
}
