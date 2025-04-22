// This program simulates the grep command to search for patterns in a file.
// It supports an optional '-c' flag to count occurrences.

#include <stdio.h>
#include <string.h>

// Function to search for a pattern in a file
void grep(char *pattern, char *file)
{
    char buf[100];
    FILE *rptr = fopen(file, "r");

    // Check if the file was opened successfully
    if (rptr == NULL)
    {
        printf("Error opening file");
        return;
    }

    int found = 0; // Flag to indicate if pattern is found
    // Read file word by word
    while (fscanf(rptr, "%s", buf) != EOF)
    {
        // Check if the current word contains the pattern
        if (strstr(buf, pattern) != NULL)
        {
            found = 1;
        }
    }

    // Print result based on whether pattern was found
    if (found == 1)
        printf("%s Found\n", pattern);
    else
        printf("%s Not Found\n", pattern);

    fclose(rptr); // Close the file
    return;
}

// Function to search for a pattern with an option
void grepOption(char *pattern, char *file, char *option)
{
    char buf[100];
    FILE *rptr = fopen(file, "r");

    // Check if the file was opened successfully
    if (rptr == NULL)
    {
        perror("Error opening file\n");
        return;
    }

    int found = 0; // Flag to indicate if pattern is found
    int count = 0; // Counter for occurrences
    // Read file word by word
    while (fscanf(rptr, "%s", buf) != EOF)
    {
        // Check if the current word contains the pattern
        if (strstr(buf, pattern) != NULL)
        {
            count++;
            found = 1;
        }
    }

    // Print result based on whether pattern was found
    if (found == 1)
    {
        printf("%s Found\n", pattern);
        printf("In %d places\n", count);
    }
    else
        printf("%s Not Found\n", pattern);

    fclose(rptr); // Close the file
    return;
}

// Entry point of the program
int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is provided
    if (argc < 3)
    {
        printf("Enter arguments properly!\n");
        return 0;
    }

    // Check if the '-c' option is used
    if (strcmp(argv[1], "-c") == 0)
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
