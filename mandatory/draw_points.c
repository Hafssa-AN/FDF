/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:48:35 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 12:31:33 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void scale_points(t_fdf *fdf)
{
    int i;
    int j;

    j = 0;
    while(j < fdf->map.nbr_y)
    {
        i = 0;
        while(i < fdf->map.nbr_x)
        {
            fdf->map.iso_points[j][i].x  *= (fdf->scale * 0.8) ;
            fdf->map.iso_points[j][i].y  *= (fdf->scale * 0.8) ;
            i++;
        }
        j++;
    }
    calc_iso_len(&(fdf->map));
}

int val_points(t_fdf fdf, t_point ***draw_points, int *i, int *j,int *nbr)
{
    (*draw_points)[*j] = NULL;
    if (!(*draw_points)[*j])
    {
        (*draw_points)[*j] = (t_point *)malloc(sizeof(t_point) * fdf.map.width);
        if (!(*draw_points)[*j])
        {
            free_double_list(*draw_points, *j);
            return (0);
        }       
    }
    *i = 0;
    while(*i < fdf.map.width)
    {
        (*draw_points)[*j][*i].x = fdf.map.iso_points[*j][*i].x + nbr[0];
        (*draw_points)[*j][*i].y = fdf.map.iso_points[*j][*i].y + nbr[1];
        (*draw_points)[*j][*i].x += fdf.offset_x ;
        (*draw_points)[*j][*i].y += fdf.offset_y;
        (*i)++;
    }
    (*j)++;
    return (1);
}

void calc_draw_points(t_fdf fdf, t_point ***draw_points)
{
    int nbr[2];
    int i;
    int j;
    
    if(fdf.map.iso_min_x != 0)
        nbr[0] = fdf.map.iso_min_x * -1;// recalculate min && max
    else
        nbr[0] = fdf.map.iso_min_x;
    if(fdf.map.iso_min_y != 0)
        nbr[1] = fdf.map.iso_min_y * -1;
    else
        nbr[1] = fdf.map.iso_min_y;
    if (!*draw_points)
    {
        *draw_points = (t_point **)malloc(sizeof(t_point *) * fdf.map.height);
        if (!*draw_points)
            return ;
    }    
    j = 0;
    while(j < fdf.map.height)
    {
        if(!val_points(fdf, draw_points, &i, &j,nbr))
            return ;    
    }
}
