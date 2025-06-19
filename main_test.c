
#include "parsing/parsing.h"
#include "cub3d.h"



int main(int argc, char **argv)
{
    char **map_rect;
    map_rect = NULL;
    t_data data;
    if (argc != 2)
    {
        ft_printf("enter an infile .cub\n");
        return (1);
    }
    map_is_valid(&map_rect, argv[1]);
    if (!map_rect)
        return (1);
    data.map = map_rect;
    print_map(data.map);
    free_map(data.map);

    return (0);
}