/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qumiraud <qumiraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:15:56 by qumiraud          #+#    #+#             */
/*   Updated: 2025/06/27 14:36:39 by qumiraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//####### includes ########//
//# include "parsing.h"
# include "../minilibx-linux/mlx.h"

//####### structures ######//
typedef struct s_data
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;

	int		F[3];
	int		C[3];

}	t_data;

typedef struct s_mlx_win
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		height;
	void	*time_value; //Permettra d'avoir un timer de fps afin d'appler les refresh au nombre d'image par seconde pour eviter d'avoir a le faire a chaque mlx_loop;
}		t_mlx_win;

#endif