/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:02:19 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/02 16:38:59 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minilibx-linux/mlx.h"
#include "../../header/cub3d.h"
# include "../../header/parsing.h"
#define map_width 24
#define map_height 24
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PLAYER_SIZE 10
// #define MOVE_SPEED 20



int	handle_key(int keycode, t_data *data)
{

// need to protect the map limit for the player

	
	if (keycode == 65307)
		exit (0); // need to go to a free function

	if (keycode == 'w' || keycode == 119)
		data->player->player_y -= data->player->move_speed;

	if (keycode == 's' || keycode == 115)
		data->player->player_y += data->player->move_speed;
	
	if (keycode == 'a' || keycode == 97)
		data->player->player_x -= data->player->move_speed;
		
	if (keycode == 'd' || keycode == 100)
		data->player->player_x += data->player->move_speed;

	// mlx_clear_window(data->win->mlx_ptr, data->win->mlx_win);
	render_map(data);
	// mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->player->player_img, data->player->player_x, data->player->player_y);

	return (0);

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
				data->player->player_x = x;
				data->player->player_y = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	home_made_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->img_addr + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dest = color;

}

void draw_img(t_data *data, int color, int x, int y)
{

	// int color = 0x00FF0000;

	while (y < 24)
	{
		while (x < 24)
		{
			home_made_pixel_put(&data->img, x, y, color);
			x++;
		}
		x = 0;
		home_made_pixel_put(&data->img, x, y, color);

		y++;
	}
	
}

t_img	create_img(t_data data)
{
	t_img	img;
	
	img.img_ptr = mlx_new_image(data.win->mlx_ptr, 24, 24);
	
	// printf ("HALLLOOO???\n\n\n\n\n");
	img.img_addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_size, &img.endian);

	return (img);
}

void	render_map(t_data *data)
{
	int	color;
	int	x;
	int	y;

	(void)color;
	x = 0;
	y = 0;
	if (data->img.img_ptr != NULL)
		mlx_destroy_image(data->win->mlx_ptr, data->img.img_ptr);
	// color = 0x00FF0000;

	data->img = create_img(*data);
	
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				color = WHITE;
			else if (data->map[y][x] == '0' || is_player(data->map[y][x]))
				color = BLACK;
			else
				color = GREEN;
			draw_img(data, color, x * 24, y * 24);
			x++;
			// printf ("UIIIIIII???\n\n\n\n\n");

		}
		x = 0;
		y++;
	// printf ("HALLLOOO???\n\n\n\n\n");

	}
	
	draw_img(data, 0x00FF0000, data->player->player_x * 24, data->player->player_y * 24);
	mlx_put_image_to_window(data->win->mlx_ptr, data->win->mlx_win, data->img.img_ptr, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
	// printf ("HALLLOOO???\n\n\n\n\n");
}






#include <stdio.h>

int main(int argc, char **argv)
{
	t_mlx_win win;
	t_player player;
	t_data data;
	t_param param;

	data.map = NULL;

	if (!guardian(&data, &param, argc, argv))
		return (1);

	// printf ("HALLLOOO???\n\n\n\n\n");

	data.img.img_ptr = NULL;
	data.player = &player;
	data.win = &win;


	data.win->mlx_ptr = mlx_init();
	data.player->move_speed = 20;
	
	if (data.win->mlx_ptr == NULL)
		return (1);
		
	data.win->mlx_win = mlx_new_window(data.win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub2D");
	if (data.win->mlx_win == NULL)
		return (1);

	// data.player->player_img = mlx_xpm_file_to_image(data.win->mlx_ptr, "H_I_F.xpm", &data.win->img_width, &data.win->img_height);
	// if(!data.player->player_img)
	// {
	// 	return (printf("Broken IMG"));
	// }
	find_player_start(&data);
	// printf ("\n\n\n player_x : %f\n\n\nplayer_y : %f", data.player->player_x, data.player->player_y);
	
	// data.player->player_x = screen_width / 2;
	// data.player->player_y = screen_height / 2;
	
	render_map(&data);
	
	
	// draw_player(&data);
	// mlx_put_image_to_window(data.win->mlx_ptr, data.win->mlx_win, data.player->player_img, data.player->player_x, data.player->player_y);
	// mlx_destroy_image(data.mlx_ptr, data.player_img);
	
	mlx_key_hook(data.win->mlx_win, handle_key, &data);
	// mlx_loop_hook(data.mlx_ptr, handle_key, &data);
	
	mlx_loop(data.win->mlx_ptr);
	
	
	// c'est la fing
	
	free_map(data.map);
	free_param(&param);
	
	return (0);
	
	// printf ("HALLOO???\n\n\n");
}









// void draw_player(t_mlx_win *window)
// {
// 	int x = 0;
// 	int y = 0;
// 	int color = 0x00FF0000;

// 	while (y < PLAYER_SIZE)
// 	{
// 		while (x < PLAYER_SIZE)
// 		{
// 			mlx_pixel_put(window->mlx_ptr, window->mlx_win, window->player_x + x, window->player_y + y, color);
// 			x++;
// 		}
// 		x = 0;
// 		mlx_pixel_put(window->mlx_ptr, window->mlx_win, window->player_x + x, window->player_y + y, color);

// 		y++;
// 	}
	
// }

// int	handle_key(int keycode, t_mlx_win *window)
// {

// // need to protect the map limit for the player

	
// 	if (keycode == 65307)
// 		exit (0); // need to go to a free function

// 	if (keycode == 'w' || keycode == 119)
// 		window->player_y -= MOVE_SPEED;

// 	if (keycode == 's' || keycode == 115)
// 		window->player_y += MOVE_SPEED;
	
// 	if (keycode == 'a' || keycode == 97)
// 		window->player_x -= MOVE_SPEED;
		
// 	if (keycode == 'd' || keycode == 100)
// 		window->player_x += MOVE_SPEED;

// 	mlx_clear_window(window->mlx_ptr, window->mlx_win);
// 	mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, window->player_img, window->player_x, window->player_y);

	
// 	// draw_player(window);?
	

// 	return (0);

	
// }

// #include <stdio.h>


// int main(void)
// {
// 	t_mlx_win window;

// 	window.mlx_ptr = mlx_init();
// 	if (window.mlx_ptr == NULL)
// 		return (1);
// 	window.mlx_win = mlx_new_window(window.mlx_ptr, screen_width, screen_height, "Cub2D");
// 	if (window.mlx_win == NULL)
// 		return (1);

// 	window.player_img = mlx_xpm_file_to_image(window.mlx_ptr, "H_I_F.xpm", &window.img_width, &window.img_height);
// 	if(!window.player_img)
// 	{
// 		return (printf("Broken IMG"));
// 	}


// 	window.player_x = screen_width / 2;
// 	window.player_y = screen_height / 2;

// 	// draw_player(&window);
// 	mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, window.player_img, window.player_x, window.player_y);

	
// 	mlx_key_hook(window.mlx_win, handle_key, &window);

	
// 	mlx_loop(window.mlx_ptr);

// 	return (0);

// }


// double pos_x = 22, pos_y = 12;  //_x and _y start position
// double dir_x = -1, dir_y = 0; //initial direction vector
// double plane_x = 0, plane_y = 0.66; //the 2d raycaster version of camera plane

// double time = 0; //time of current frame
// double oldTime = 0; //time of previous frame

// screen(screen_width, screen_height, 0, "Raycaster");




// int world_map[map_width][map_height]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };