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

#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//define the value used to make the map rectangle
# ifndef HOLE
#  define HOLE '4'

//skip the textures lines and then copy into a **tab starting from the first valid char found (1 / 0 / N / S etc)
char    **get_map(char *filename);

//make the original map rectangle
char    **map_to_rectangle(char **map);

int     has_valid_char(char **map);
int     check_holes(char **map);

//utils
void    free_map(char **map);
void    print_map(char **map);
int     valid_char(char *line);
int     is_player(char c);



void map_is_valid(char ***map_rect, char *argv);

# endif
#endif