/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:42:54 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 13:15:20 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    free_double_list(t_point **draw_points, double height)
{
	int j;

	j = 0;
	if (draw_points)
	{
		while (j < height && (draw_points)[j])
		{
			free((draw_points)[j]);
			j++;
		}
		free(draw_points);
		draw_points = NULL;
	}
}

void free_list(t_row   **rows)
{
	t_row   *tmp;
	
	tmp = *rows;
	while(tmp)
	{
		*rows = (*rows)->next;
		free(tmp->row);
		free(tmp);
		tmp = *rows;   
	}
}
void free_fdf(t_fdf *fdf)
{
	
	if (fdf->map.iso_points) {
		free_double_list(fdf->map.iso_points, fdf->map.height);
	}
	if (fdf->map.points) {
		free_double_list(fdf->map.points, fdf->map.height);
	}
}

void free_fdf_and_exit(t_fdf *fdf, char *message)
{
	if (fdf->img)
		mlx_delete_image(fdf->mlx, fdf->img);
	free_fdf(fdf);
	mlx_terminate(fdf->mlx);
	my_exit(message);
}