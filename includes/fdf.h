/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:03:52 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 13:15:14 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WIDTH 1200
# define HEIGHT 1000
# define PI 3.14159265358
# include <stdio.h> // a supprimer apres !!!!!!!!!!!!!!!!!!!!!!!! if u dont use perror
 
typedef struct point
{
	double x;
	double y;
	double z;
	unsigned int color;
	struct point *next;
} t_point;

typedef struct row
{
	char *row;
	struct row *next;
} t_row;

// typedef struct s_point {
//     int x, y, z;
//     unsigned int color;
// } t_point;

typedef struct s_map {
	t_point **points;
	t_point **iso_points;
	// t_point **scale_points;
	double width;//numb pix
	double height;//numb pix
	double iso_width;
	double iso_height;
	double iso_min_x;
	double iso_max_x;
	double iso_min_y;
	double iso_max_y;
	double nbr_x;// a supp === width
	double nbr_y;//a supp === height
} t_map;

typedef struct s_fdf {
	mlx_t *mlx;
	mlx_image_t *img;
	t_map map;
	double width;
	double height;
	double scale;
	double angle;
	double offset_x;
	double offset_y;
	int projection; // 0 for isometric, 1 for parallel
} t_fdf;


int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(char *s);
char	**ft_split(const char *s, char c);
int     ft_newSplit(t_point **points,const char *s, int j);
char	*get_next_line(int fd);
int	ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2, int x);
void	my_exit(char *str);
unsigned int atoi_exa(char *str);
int	ft_atoi(const char *str);
void scale_points(t_fdf *fdf);
void calc_draw_points(t_fdf fdf, t_point ***draw_points);
void    free_double_list(t_point **draw_points, double height);
void free_list(t_row   **rows);
void free_fdf(t_fdf *fdf);
void free_fdf_and_exit(t_fdf *fdf, char *message);
int count_lines(int fd, t_row   **rows);
void    input(char *argv, t_point ***points, double *len_0, double *len_1);
void iso_project(t_fdf *fdf, t_point *points, t_point *iso_points);
void calc_iso_len(t_map *map);
void dim_iso(t_fdf *fdf);
void draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, unsigned int color1, unsigned int color2);
void draw_map(t_fdf *fdf);
void err_alloc(t_row **rows, int fd);
void err_jalloc(t_point **points, int j, char **split, int fd, t_row **rows);
#endif