/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:34:05 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 13:17:17 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_exit(char *str)
{
	write(1, str, ft_strlen(str));
	exit(1);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf *fdf;
	
	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
}

void    some_instr(t_fdf *fdf)
{
	fdf->height = HEIGHT;
	fdf->width = WIDTH;
	if(fdf->map.height > 1300 || fdf->map.width > 2600)
		free_fdf_and_exit(fdf, "map dimension invalid");
	if(fdf->map.height > fdf->height)
		fdf->height = fdf->map.height;
	if(fdf->map.width > fdf->width)
		fdf->width = fdf->map.width;
	if((fdf->height)/fdf->map.iso_height <= (fdf->width)/fdf->map.iso_width)
		fdf->scale = (fdf->height - 100)/fdf->map.iso_height;
	else
		fdf->scale = (fdf->width - 100)/fdf->map.iso_width;
	fdf->projection = 0;
	scale_points(fdf);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", 1);
	if (!fdf->mlx)
		free_fdf_and_exit(fdf,"Failed to initialize MLX");
	fdf->offset_x = ((fdf->width/2) - (fdf->map.iso_width/2)) ;
	fdf->offset_y = ((fdf->height/2) - (fdf->map.iso_height/2));
	draw_map(fdf);
	mlx_key_hook(fdf->mlx, key_hook, fdf);
	mlx_loop(fdf->mlx);
}

void lol(void)
{
	system("leaks fdf");
}
int main(int argc, char **argv)
{
	atexit(lol);
	t_fdf fdf;
	
	if(argc != 2)
		return (write(1, "The number of arguments is not correct; \
		we need 1 parameter\n", 60), 1);
	if(ft_strlen(argv[1]) < 4 || (ft_strlen(argv[1]) > 4 && 
		ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".fdf", 4)))
		return (write (1, "The file must have an extension of .fdf\n", 39), 1);
	fdf.map.points = NULL;
	fdf.map.iso_points = NULL;
	input(argv[1], &(fdf.map.points), &(fdf.map.height), &(fdf.map.width));
	fdf.map.nbr_x = fdf.map.width;
	fdf.map.nbr_y = fdf.map.height;
	dim_iso(&fdf);
	some_instr(&fdf);
	free_fdf(&fdf);
	if (fdf.img)
		mlx_delete_image(fdf.mlx, fdf.img);
	mlx_terminate(fdf.mlx);
	return (0);
}

