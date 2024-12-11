#include "parsing.h"

int validate_and_open_file(char *filename)
{
    int fd;
    char *extention;

    extention = ft_strrchr(filename, '.');
    if (!extention || ft_strncmp(extention, ".cub", 4) != 0 || extention[4] != '\0')
    {
        write(1, "Invalid file extention!", 23);
        exit(1);
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }
    return (fd);
}