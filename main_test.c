
#include "parsing/parsing.h"
#include "cub3d.h"



int main(int argc, char **argv)
{
    char **map_rect;
    map_rect = NULL;
    t_param param;
    t_data data;
    if (argc != 2)
    {
        ft_printf("enter an infile .cub\n");
        return (1);
    }
    map_is_valid(&map_rect, argv[1], &param);
    if (!map_rect)
        return (1);
    //printf("f_color : %s\n", param.f_color_str);
    is_color(param.f_color_str, data.F);
    //printf("f_color : %s\n", param.f_color_str);
    //printf("c_color : %s\n", param.c_color_str);

    //data.map = map_rect;
    //print_map(data.map);
    free_map(map_rect);
    free_param(&param);


    return (0);
}