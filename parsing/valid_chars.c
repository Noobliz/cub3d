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

#include "parsing.h"


int one_player(char **map)
{
    int player_count;
    int walkable_count;
    int i;
    int j;

    player_count = 0;
    walkable_count = 0;
    i = 0;
    while(map && map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (is_player(map[i][j]))
                player_count++;
            if (map[i][j] == '0')
                walkable_count++;
            j++;
        }
        i++;
    }
    if (player_count > 1 || player_count == 0 || walkable_count == 0)
        return (0);

    return (1);
}


int has_valid_char(char **map)
{
    int i;

    i = 0;
    if (!one_player(map))
    {
        write(2, "input 1 player max and at least 1 walkable\n", 44);
        free_map(map);
        return (0);
    }
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

int has_holes(char **map, int i, int j)
{
    if (j == 0 && map[i][j] != '1')
        return (1);
    if (map[i][j] == '0' || is_player(map[i][j]))
    {
        if ((map[i][j + 1] == HOLE) || (j > 0 && map[i][j - 1] == HOLE))
            return (1);
        if ((i > 0 && map[i - 1][j] == HOLE) || (map[i + 1] != NULL && map[i + 1][j] == HOLE))
            return (1);
    }
    return (0);
}

// check if player or 0 is next to a hole and that first colums is wall
int check_holes(char **map)
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
            if (has_holes(map, i, j))
            {
                write(2, "hole in the map\n", 17);
                free_map(map);
                return (0);
            }
            j++;
        }
        i++;

    }
    return (1);
}

void map_is_valid(char ***map_rect, char *argv)
{
    // char **map_rect;
    // map_rect = NULL;
    char **infile;
    infile = NULL;
    infile = get_map(argv);
    if (!infile)
        return ;
    *map_rect = map_to_rectangle(infile);
    if (!*map_rect)
        return ;
    print_map(*map_rect);
    if (!has_valid_char(*map_rect) || !check_holes(*map_rect))
    {
        *map_rect = NULL;
        return ;
    }
    
    //return (map_rect);
}