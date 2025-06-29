
#include "../header/parsing.h"
#include "../header/cub3d.h"

void    init_textures(t_data *data, t_param param)
{
    data->EA = param.ea_path;
    data->NO = param.no_path;
    data->SO = param.so_path;
    data->WE = param.we_path;
}

int main(int argc, char **argv)
{
    char **map_rect;
    map_rect = NULL;
    t_param param;
    t_data data;
    data.map = NULL;
    if (argc != 2)
    {
        ft_printf("enter an infile .cub\n");
        return (1);
    }
    map_is_valid(&map_rect, argv[1], &param);
    if (!map_rect)
        return (1);
    data.map = map_rect;
    init_textures(&data, param);
    //print_map(data.map);
    if (!is_color(param.f_color_str, data.F)
        || !is_color(param.c_color_str, data.C))
        {
            free_map(map_rect);
            free_param(&param);
            return (1);
        }
    //printf("f_color : %s\n", param.f_color_str);
    //printf("c_color : %s\n", param.c_color_str);

    free_map(map_rect);
    free_param(&param);


    return (0);
}