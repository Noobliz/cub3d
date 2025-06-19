
#include "../parsing.h"

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
    if (!has_valid_char(map_rect) || !check_void(map_rect))
        return (1);
    free_map(map_rect);

    return (0);
}