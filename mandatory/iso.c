/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:47:17 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 12:09:07 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void iso_project(t_fdf *fdf, t_point *points, t_point *iso_points)
{
    double alt;
    
    if (!fdf || !points || !iso_points)
        free_fdf_and_exit(fdf,"Null pointer in iso_project\n");
    fdf->angle = (42 * (M_PI / 180));
    iso_points->x = (points->x * cos(fdf->angle) - (points->y *  sin(fdf->angle)));
    iso_points->y = (points->y * cos(fdf->angle) + (points->x *  sin(fdf->angle))); 
    fdf->angle = atan(1 / sqrt(2) * 1.7);
    alt = iso_points->y;
    iso_points->y = (iso_points->y * cos(fdf->angle) - (points->z *  sin(fdf->angle)));
    iso_points->z = ((alt * sin(fdf->angle)) + (points->z *  cos(fdf->angle)));
}

void calc_iso_len(t_map *map)
{
    int i;
    int j;
    
    map->iso_min_x = 2147483647;
    map->iso_min_y = 2147483647;
    map->iso_max_x = -2147483648;
    map->iso_max_y = -2147483648;
    j = -1;
    while(++j < map->nbr_y)
    {
        i = -1;
        while (++i < map->nbr_x)
        {
            if(map->iso_points[j][i].x < map->iso_min_x)
                map->iso_min_x = map->iso_points[j][i].x;
            if(map->iso_points[j][i].x > map->iso_max_x)
                map->iso_max_x = map->iso_points[j][i].x;
            if(map->iso_points[j][i].y < map->iso_min_y)
                map->iso_min_y = map->iso_points[j][i].y;
            if(map->iso_points[j][i].y > map->iso_max_y)
                map->iso_max_y = map->iso_points[j][i].y;
        }  
    }
    map->iso_height = map->iso_max_y - map->iso_min_y + 1;
    map->iso_width = map->iso_max_x - map->iso_min_x + 1;
}
void dim_iso(t_fdf *fdf)
{
    int i, j;

    if (!fdf->map.iso_points)
    {
        fdf->map.iso_points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
        if (!fdf->map.iso_points)
            free_fdf_and_exit(fdf, "Memory allocation failed for iso_points");
    }
    j = 0;
    while (j < fdf->map.height)
    {
        fdf->map.iso_points[j] = NULL;
        if (!fdf->map.iso_points[j])
        {
            fdf->map.iso_points[j] = (t_point *)malloc(sizeof(t_point) * fdf->map.width);
            if (!fdf->map.iso_points[j])
            {
                free_double_list(fdf->map.iso_points, j);
                free_fdf_and_exit(fdf, "Memory allocation failed for iso_points[j]");
            }
        }
        i = 0;
        while (i < fdf->map.width)
        {
            iso_project(fdf, &(fdf->map.points[j][i]), &(fdf->map.iso_points[j][i]));
            i++;
        }
        j++;
    }
    calc_iso_len(&(fdf->map));
}
