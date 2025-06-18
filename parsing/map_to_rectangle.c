#include "../parsing.h"

int get_height(char **map)
{
    int i;
    i = 0;
    while (map && map[i])
        i++;
    return(i);
}


int get_biggest_line(char **map)
{
    size_t max;
    max = 0;
    int i;
    i = 0;
    while (map && map[i])
    {
        if (ft_strlen(map[i]) > max)
        {
            max = ft_strlen(map[i]);
        }
        i++;
    }
    printf("max = %ld\n", max);
    return (max);
}

void rm_newline(char **map)
{
    size_t len;
    int i;
    i = 0;
    while (map && map[i])
    {
        len = ft_strlen(map[i]);
        if (len > 0 && map[i][len - 1] == '\n')
            map[i][len - 1] = '\0';
        i++;
    }
}


char **map_to_rectangle(char **map)
{
    int max_width;
    int height;
    int i;
    int j;
    i = 0;
    j = 0;

    rm_newline(map);
    max_width = get_biggest_line(map);
    height = get_height(map);

    char    **new_map;
    new_map = ft_calloc((height + 1), sizeof(char *));
    if (!new_map)
    {
        write(2, "error allocating map\n", 22);
        free_map(map);
        return (NULL);
    }
    while(i < height)
    {
        new_map[i] = ft_calloc(max_width + 2, sizeof(char));
        if (!new_map[i])
        {
            write(2, "error allocating line\n", 23);
            free_map(new_map);
            free_map(map);
            return (NULL);
        }
        ft_strlcpy(new_map[i], map[i], ft_strlen(map[i]) + 1);
        j = ft_strlen(map[i]);
        while(j < max_width)
        {
            new_map[i][j] = '4';
            j++;
        }
        new_map[i][max_width] = '\n';
        new_map[i][max_width + 1] = '\0';
        i++;
    }
    new_map[height] = NULL;
    free_map(map);
    return (new_map);
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("please enter a map name\n");
        return (1);
    }
    char **map;
    map = NULL;
    map = get_map(argv[1]);
    int i = 0;
    while (map && map[i])
    {
        ft_printf("%s", map[i]);
        i++;
    }
    ft_printf("\n-----------\n");
    if (!map)
    {
        ft_printf("invalid map\n");
        return (1);
    }
    char **map_rect = map_to_rectangle(map);
    if (!map_rect)
        return (1);
    i = 0;
    while (map_rect && map_rect[i])
    {
        ft_printf("%s", map_rect[i]);
        i++;
    }
    if (!has_valid_char(map_rect))
        return (1);
    free_map(map_rect);

    return (0);
}