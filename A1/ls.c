#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

// Entry point of the program
int main(int argc, char *argv[])
{
    // Directory path (default to current directory ".")
    char *dir_path = (argc >= 2) ? argv[1] : ".";

    // Open the directory
    DIR *dir = opendir(dir_path);

    // Check if directory was opened successfully
    if (dir == NULL)
    {
        printf("Error opening directory '%s': %s\n", dir_path, strerror(errno));
        return 1;
    }

    // Read directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip hidden files (starting with '.') for simplicity
        if (entry->d_name[0] != '.')
        {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);
    printf("\nDirectory listed successfully\n");
    return 0;
}