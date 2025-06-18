
#include "../parsing.h"


//skip the texture part and goes to map part
static int is_map_line(char *line)
{
    while (*line)
    {
        if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
            return (1);
        line++;
    }
    return (0);
}

//malloc of new line in **tab, 1 for line 1 for \0
static char **add_line(char **map, char *line, int *count)
{
    int i;
    i = 0;
    char **new_map = malloc(sizeof(char *) * (*count + 2));
    if (!new_map)
        return (NULL);
    // copy what was already in map
    while (i < *count)
    {
        new_map[i] = map[i];
        i++;
    }
    // copy the new line
    new_map[*count] = line;
    new_map[*count + 1] = '\0';
    //free what was in the old map
    if (map)
        free(map);
    (*count)++;
    return (new_map);
}

//skip the textures lines and then copy into a **tab starting from the first valid char found (1 / 0 / N / S etc)
char **get_map(char *filename)
{
    int fd;
    int map_found;
    int count;
    char    *line;
    char    **map;
    line = NULL;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "error opening map\n", 19);
        return (NULL);
    }
    map = NULL;
    map_found = 0;
    count = 0;

    line = get_next_line(fd);
    while (line)
    {
        if (map_found == 0 && is_map_line(line))
            map_found = 1;
        if (map_found)
        {
            if (line[0] == '\n' || line[0] == '\0')
            {
                free(line);
                line = NULL;
                break;
            }
            map = add_line(map, line, &count);
        }
        //free the texture lines of the beggining
        else if (line)
        {
            free(line);
            line = NULL;
        }
        line = get_next_line(fd);
    }
    if (line)
    {
        free(line);
        line = NULL;
    }
    close(fd);
    return (map);
}
