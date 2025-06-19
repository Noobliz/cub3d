/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:26:23 by lguiet            #+#    #+#             */
/*   Updated: 2025/06/19 11:26:36 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSING_H
# define PARSING_H

#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//define the value used to make the map rectangle
# ifndef FILL
#  define FILL '4'

# ifndef PLAYER
#define IS_PLAYER(c) ((c) == 'N' || (c) == 'S' || (c) == 'E' || (c) == 'W')


//skip the textures lines and then copy into a **tab starting from the first valid char found (1 / 0 / N / S etc)
char **get_map(char *filename);

//make the original map rectangle
char **map_to_rectangle(char **map);

int has_valid_char(char **map);
int check_void(char **map);

//utils
void    free_map(char **map);
# endif
# endif
#endif