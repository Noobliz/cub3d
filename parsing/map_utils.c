

#include "parsing.h"

int is_player(char c)
{
    return (((c) == 'N' || (c) == 'S' || (c) == 'E' || (c) == 'W'));
}

int valid_char(char *line)
{
    int i;
    i = 0;

    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != HOLE && line[i] != '\0' && line[i] != '\n')

            return (0);
        i++;
    }
    return (1);
}

void    print_map(char **map)
{
    int i;

    i = 0;
    while (map && map[i])
    {
        ft_printf("%s", map[i]);
        i++;
    }
}