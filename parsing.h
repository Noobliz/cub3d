#ifndef PARSING_H
# define PARSING_H

#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
//skip the textures lines and then copy into a **tab starting from the first valid char found (1 / 0 / N / S etc)
char **get_map(char *filename);

//make the original map rectangle
char **map_to_rectangle(char **map);

int has_valid_char(char **map);

//utils
void    free_map(char **map);

#endif