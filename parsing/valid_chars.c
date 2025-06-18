
#include "../parsing.h"

int valid_char(char *line)
{
    int i;
    i = 0;
    while(line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != '4' && line[i] != '\0' && line[i] != '\n')

            return (0);
        i++;
    }
    return (1);
}

int has_valid_char(char **map)
{
    int i;
    i = 0;
    while(map && map[i])
    {
        if (!valid_char(map[i]))
        {
            write(2, "invalid char\n", 14);
            free_map(map);
            return (0);
        }
        i++;
    }
    return (1);
}