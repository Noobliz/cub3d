/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:29:43 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/04 15:54:18 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"
#include "../../header/cub3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



void	dir_player(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
	}
	else if ( c == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
	}
	else if ( c == 'E')
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
	}
	else if (c == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
	}
}

// int is_player(char c)
// {
// 	return (((c) == 'N' || (c) == 'S' || (c) == 'E' || (c) == 'W'));
// }

void	find_player_start(t_data *data)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (is_player(data->map[y][x]))
			{
				dir_player(data, data->map[y][x]);
				data->player->pos_x = x;
				data->player->pos_y = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	init_time(t_bigben *bigben)
{
	bigben->old_time = 0;
	bigben->time = 0;
}

void	raycasting_loop(t_data *data)
{
	int		x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	
	
	x = 0;
	map_x = 0;
	map_y = 0;
	camera_x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / SCREEN_WIDTH - 1;
		ray_dir_x = data->player->dir_x + data->player->plane_x * camera_x;
		ray_dir_y = data->player->dir_y + data->player->plane_y * camera_x;
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else delta_dist_y = fabs(1 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player->pos_x) * delta_dist_x; 
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player->pos_y) * delta_dist_y; 
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map[map_y][map_x] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - side_dist_y);
		line_height = (int)(SCREEN_WIDTH / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT) 
			draw_end = SCREEN_HEIGHT - 1;
	}
	data->bigben->old_time = data->bigben->time;
	data->bigben->time = clock();
	data->bigben->frame_time = (data->bigben->time - data->bigben->old_time) / CLOCKS_PER_SEC;
	printf ("FPS : %.2f\n", data->bigben->frame_time);
	data->player->move_speed = data->bigben->frame_time * 5.0;
	data->player->rot_speed = data->bigben->frame_time * 3.0;
}
 
int main(int argc, char **argv)
{
	// t_mlx_win	win;
	// t_player	player;
	t_data		data;
	t_param		param;
	
	data.map = NULL;

	if (!guardian(&data, &param, argc, argv))
		return (1);
	data.param = &param;
	
	find_player_start(&data);
	init_time(data.bigben);
	raycasting_loop(&data);

	
}
