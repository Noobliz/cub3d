/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:29:43 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/23 15:27:33 by qumiraud         ###   ########.fr       */
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
	if (c == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->player->plane_x = -0.66;
		data->player->plane_y = 0;
	}
	else if ( c == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
		data->player->plane_x = 0.66;
		data->player->plane_y = 0;
	}
	else if ( c == 'E')
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = -0.66;
	}
	else if (c == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = 0.66;
	}
}

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
				data->player->pos_x = x + 0.5;
				data->player->pos_y = y + 0.5;
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
	// https://www.notion.so/Ray-Casting-220938a31f20806a8dd4c3dec8392e20?source=copy_link
	int		x;
	int		map_x;
	int		map_y;
	int		step_x = 0;
	int		step_y = 0;
	int		hit = 0;
	int		side = 0;
	int		line_height = 0;
	int		draw_start = 0;
	int		draw_end = 0;
	double	side_dist_x = 0;
	double	side_dist_y = 0;
	double	delta_dist_x = 0;
	double	delta_dist_y = 0;
	double	perp_wall_dist = 0;
	double	camera_x;
	double	ray_dir_x = 0;
	double	ray_dir_y = 0;

	x = 0;
	side_dist_x = 0;
	side_dist_y = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2.00 * (double)x / SCREEN_WIDTH - 1;
		// printf("camera_x : %2.f", camera_x);
		ray_dir_x = data->player->dir_x + data->player->plane_x * camera_x;
		ray_dir_y = data->player->dir_y + data->player->plane_y * camera_x;
		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;
		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / ray_dir_y);
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
		// printf("BEFOREside_dist_x: %2.f, side_dist_y : %2.f\n\n", side_dist_x, side_dist_y);
		// printf("BEFOREdelta_dist_x: %2.f, delta_dist_y : %2.f\n\n", delta_dist_x, delta_dist_y);
		hit = 0;
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
			if (data->map[map_y][map_x] == '1')
			{
				// printf("map_x : %d et map_y : %d\n\n playerpos_x : %f et playerpos_y : %f", map_x, map_y, data->player->pos_x, data->player->pos_y);
				hit = 1;
			}
			// printf("DURINGside_dist_x: %2.f, side_dist_y : %2.f\n\n", side_dist_x, side_dist_y);
		}
		// printf("AFTERside_dist_x: %2.f, side_dist_y : %2.f\n\n", side_dist_x, side_dist_y);
		// printf("AFTERdelta_dist_x: %2.f, delta_dist_y : %2.f\n\n", delta_dist_x, delta_dist_y);

		if (side == 0)
		{
			perp_wall_dist = (side_dist_x - delta_dist_x);
			// printf ("HALLO\n\n");
		}
		else
		{
			// printf("BONJOUR\n\n");
			perp_wall_dist = (side_dist_y - delta_dist_y);
			// perp_wall_dist = (side_dist_y - side_dist_y);
		}
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		// printf("perpwalldist: %2.f, line_height : %d\n\n", perp_wall_dist, line_height);
		draw_start = -line_height * 0.5 + SCREEN_HEIGHT * 0.5;
		// printf ("DRAW_START : %d\n\n\n\n", draw_start);
		// exit (0);
		if (draw_start < 0)
			draw_start = 0;
		// draw_start = 0;

		draw_end = line_height * 0.5 + SCREEN_HEIGHT * 0.5;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		// printf("draw_start : %d, draw_end : %d\n\n", draw_start, draw_end);
		while (draw_start <= draw_end)
		{
			// printf("draw_start : %d, draw_end : %d\n\n", draw_start, draw_end);
			// printf("x : %d\n\n", x);
			mlx_pixel_put(data->win->mlx_ptr, data->win->mlx_win,
					x, draw_start, GREEN);
			draw_start++;
			// if (x == 50)
				// break;
		}
		// printf("x : %d\n\n", x);

		// if (x == 50)
		// 		break;
		x++;
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
	t_mlx_win	win;
	t_player	player;
	t_data		data;
	t_param		param;
	t_bigben	tardis;

	data.map = NULL;
	if (!guardian(&data, &param, argc, argv))
		return (1);
//initialisation
	data.img.img_ptr = NULL;
	data.win = &win;
	data.player = &player;
	data.bigben = &tardis;
	data.param = &param;
	data.win->mlx_ptr = mlx_init();
	if (data.win->mlx_ptr == NULL)
		return (1);
	data.win->mlx_win = mlx_new_window(data.win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub2D");
	if (data.win->mlx_win == NULL)
		return (1);
	// 	data.player->move_speed = 1;

	find_player_start(&data);
	init_time(data.bigben);
	raycasting_loop(&data);
	mlx_hook(data.win->mlx_win, KeyPress, KeyPressMask, &handle_key, &data);
	mlx_loop(data.win->mlx_ptr);

	//raycasting

	return (0);
}
