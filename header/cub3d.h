/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjurdana <pjurdana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:15:56 by qumiraud          #+#    #+#             */
/*   Updated: 2025/07/04 15:51:52 by pjurdana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//####### includes ########//
# include "parsing.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <math.h>
# include <X11/keysym.h>
#include <time.h>


#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GREEN 0x00FF00



//####### structures ######//

typedef struct s_player
{
	void	*player_img;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
	char	p_dir;
	
}	t_player;

typedef struct s_bigben
{
	double	time;
	double	old_time;
	double frame_time;
}	t_bigben;

typedef struct	t_img
{
	void	*img_ptr;

	int		bpp;
	int		line_size;
	int		endian;

	char	*img_addr;


}	t_img;

typedef struct s_mlx_win
{
	void	*mlx_ptr;
	void	*mlx_win;


	int		img_width;
	int		img_height;

	// char	*img_ptr;
	// char	*img_data;


	// int		width;
	// int		height;
	// void	*time_value; //Permettra d'avoir un timer de fps afin d'appler les refresh au nombre d'image par seconde pour eviter d'avoir a le faire a chaque mlx_loop;

}		t_mlx_win;

typedef struct s_data
{
	char		**map;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;

	int			F[3];
	int			C[3];
	struct s_param		*param;
	t_bigben	*bigben;
	t_mlx_win	*win;
	t_player	*player;
	t_img		img;

}	t_data;


//############ GRAPHIC_DIR ############//
int		main(int argc, char **argv);
void	render_map(t_data *data);

#endif
