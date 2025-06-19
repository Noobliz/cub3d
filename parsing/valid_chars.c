/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:23:37 by lguiet            #+#    #+#             */
/*   Updated: 2025/06/19 12:31:10 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int valid_char(char *line)
{
    int i;
    i = 0;

    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != FILL && line[i] != '\0' && line[i] != '\n')

            return (0);
        i++;
    }
    return (1);
}

int has_valid_char(char **map)
{
    int i;
    i = 0;

    while (map && map[i])
    {
        if (!valid_char(map[i]))
        {
            write(2, "invalid char\n", 14);
            free_map(map);
            return (0);
        }
        i++;
    }
    return (1);
}

// check if player or 0 is next to a hole and that first colums is wall
int check_void(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (j == 0 && map[i][j] != '1')
            {
                write(2, "hole in the map\n", 17);
                free_map(map);
                return (0);
            }
            if (map[i][j] == '0' || IS_PLAYER(map[i][j]))
            {
                if ((map[i][j + 1] == FILL) || (j > 0 && map[i][j - 1] == FILL))
                {
                    write(2, "hole in the map\n", 17);
                    free_map(map);
                    return (0);
                }
                if ((i > 0 && map[i - 1][j] == FILL) || (map[i + 1] != NULL && map[i + 1][j] == FILL))
                {
                    write(2, "hole in the map\n", 17);
                    free_map(map);
                    return (0);
                }
            }
            j++;
        }
        i++;

    }
    return (1);
}