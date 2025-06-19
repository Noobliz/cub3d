#include "parsing.h"

void    free_map(char **map)
{
    int i;
    i = 0;
    while(map && map[i])
    {
        if (map[i])
        {
            free(map[i]);
            map[i] = NULL;
        }
        i++;
    }
    if (map)
        free(map);
    map = NULL;
}

// void free_map(char ***map)
// {
//     int i;
    
//     i = 0;
//     if (!map || !*map)
//         return;
//     while (*map && (*map)[i])
//     {
//         free((*map)[i]);
//         (*map)[i] = NULL;
//         i++;
//     }
//     if (*map)
//         free(*map);
//     *map = NULL;
// }