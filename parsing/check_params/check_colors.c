/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:04:25 by lguiet            #+#    #+#             */
/*   Updated: 2025/06/24 12:35:59 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../cub3d.h"


int    is_color(char *color_str, int color_int[3])
{
    char *trimmed;
    char    **split_clr;
    int i;
    int res;

    split_clr = NULL;
    trimmed = ft_strtrim(color_str, " \t \n");
    if (!trimmed)
    {
        perror("malloc");
        return (0);
    }
    i = 0;
    res = -1;
    printf("trimmed :%s\n", trimmed);
    while(trimmed[i])
    {
        if (!ft_isdigit(trimmed[i]) && trimmed[i] != ',' && trimmed[i] != '\n')
        {
            free(trimmed);
            write(2, "Error\ncolors should be described as [R,G,B]\n", 45);
            return (0);
        }
        i++;
    }
    split_clr = ft_split(trimmed, ',');
    if(!split_clr)
    {
        free(trimmed);
        return(0);
    }
    i = 0;
    while(split_clr && split_clr[i])
        i++;
    if (i != 3)
    {
        write(2, "Error\ncolors should be [R,G,B]\n", 32);
        free_map(split_clr);
        free(trimmed);
        return (0);
    }
    i = 0;
    while(split_clr && split_clr[i])
    {
        res = ft_atoi(split_clr[i]);
        if (res < 0 || res > 255)
        {
            free_map(split_clr);
            free(trimmed);
            write(2, "Error\ncolors not within range\n", 31);
            return (0);
        }
        color_int[i] = res;    
        i++;
    }
    i = 0;
    while (i < 3)
    {
        printf("colors int[%d] = %d\n", i, color_int[i]);
        i++;
    }
    free(trimmed);
    free_map(split_clr);
    return (1);
    
}
