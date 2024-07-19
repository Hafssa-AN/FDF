/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:45:22 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 12:11:40 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t p_color(uint32_t color1, uint32_t color2, float t)
{
    uint8_t r1 = (color1 >> 24) & 0xFF;
    uint8_t g1 = (color1 >> 16) & 0xFF;
    uint8_t b1 = (color1 >> 8) & 0xFF;
    uint8_t a1 = color1 & 0xFF;

    uint8_t r2 = (color2 >> 24) & 0xFF;
    uint8_t g2 = (color2 >> 16) & 0xFF;
    uint8_t b2 = (color2 >> 8) & 0xFF;
    uint8_t a2 = color2 & 0xFF;

    uint8_t r = r1 + (r2 - r1) * t;
    uint8_t g = g1 + (g2 - g1) * t;
    uint8_t b = b1 + (b2 - b1) * t;
    uint8_t a = a1 + (a2 - a1) * t;

    return (r << 24) | (g << 16) | (b << 8) | a;
}

void draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, unsigned int color1, unsigned int color2)
{
    int dx, dy, steps, i;
    float x_inc, y_inc, x, y;

    dx = x1 - x0;
    dy = y1 - y0;

    if (fabs((float)dx) > fabs((float)dy))
        steps = fabs((float)dx);
    else
        steps = fabs((float)dy);

    x_inc = (float)dx / steps;
    y_inc = (float)dy / steps;

    x = x0;
    y = y0;

    i = 0;
    while (i <= steps)
    {
        float t = (float)i / steps;
        unsigned int color = p_color(color1, color2, t);
        if(round(x) >= 0 && round(y) >= 0 && round(x) < fdf->width && round(y) < fdf->height)
            mlx_put_pixel(fdf->img, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

void draw_map(t_fdf *fdf)
{
    t_point **draw_points;
    int i;
    int j;

    if (fdf->img)
        mlx_delete_image(fdf->mlx, fdf->img);
    fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
    if (!fdf->img)
        free_fdf_and_exit(fdf, "Failed to create image");
    draw_points = NULL;
    calc_draw_points(*fdf, &draw_points);
    if(!draw_points)
        free_fdf_and_exit(fdf, "Failed to alocate draw points");
    j = 0; 
    while(j < fdf->map.height && draw_points[j])
    {
        i = 0;
        while (i < fdf->map.width)
        {
            if (i < fdf->map.width - 1 )
            {
                draw_line(fdf, draw_points[j][i].x, draw_points[j][i].y,
                        draw_points[j][i + 1].x, draw_points[j][i + 1].y,
                        fdf->map.points[j][i].color, fdf->map.points[j][i + 1].color);
            }
            if (j < fdf->map.height - 1 )
            {
                draw_line(fdf, draw_points[j][i].x, draw_points[j][i].y,
                        draw_points[j + 1][i].x, draw_points[j + 1][i].y,
                        fdf->map.points[j][i].color, fdf->map.points[j + 1][i].color);
            }
            i++;
        }
        j++; 
    }
    free_double_list(draw_points, fdf->map.height);
}
