#include <stdio.h>
#include "get_next_line.h"

int main()
{
    // This is a placeholder for the main function.
    // The actual implementation of get_next_line will be tested here.
    // You can call get_next_line with a file descriptor to read lines from a file.
    int fd = open("text_prueba.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}