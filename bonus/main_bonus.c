/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:04:17 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/15 16:04:20 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	my_exit(char *str)
{
	perror(str);
	exit(1);
}
int count_lines(int fd, t_row   **rows)
{
    int nbr;
    char *str;
    t_row   *tmp;

    nbr = 0;
    tmp = NULL;
    str = get_next_line(fd);
    while(str)
    {
        if(!*rows)
        {
            *rows = (t_row *)malloc(sizeof(t_row));
            if(!*rows)
                return (0);
            (*rows)->row = str;
            (*rows)->next = NULL;
            tmp = *rows;
        }
        else
        {
            tmp->next = (t_row *)malloc(sizeof(t_row));
            if(!tmp->next)
                return (0);
            tmp = tmp->next;
            tmp->row = str;
            tmp->next = NULL;
        }
        nbr++;
        str = get_next_line(fd);
    }
    return (nbr);
}

void    input(char *argv, t_point ***points, double *len_0, double *len_1)// i can change the return to int , and return size[1]
{
    int fd;
    int j;
    int i;
    t_row   *rows;
    char **split;
    char **last_split;
    
    j = 0;
    rows = NULL;
    fd = open(argv, O_RDONLY);
	if (fd == -1)
		my_exit("error");//bien structurer using perror
    *len_0 = count_lines(fd, &rows);
    *points = (t_point **)malloc(sizeof(t_point *) * *len_0);
    if(!*points)
        return ;
    while(j < *len_0)
    {
        i = 0;
        split = ft_split(rows->row, ' ');
        while(split[i] != NULL)
            i++;
            
        (*points)[j] = (t_point *)malloc(sizeof(t_point) * i);
        if(!(*points)[j])
            return ;
        i = 0;
        while(split[i] != NULL)
        {
            (*(*((*points) + j) + i)).x = i;//(*points)[j][i]
            (*(*((*points) + j) + i)).y = j;
            last_split = ft_split(split[i], ',');
            (*(*((*points) + j) + i)).z = ft_atoi(last_split[0]);
            if(last_split[1])
                (*(*((*points) + j) + i)).color = atoi_exa(last_split[1]);
            else if((*(*((*points) + j) + i)).z == 0)
                (*(*((*points) + j) + i)).color = atoi_exa("0xB00000");
            else
                (*(*((*points) + j) + i)).color = atoi_exa("0xE5C0C0");
            i++;
        }
        if(j == 0)
            *len_1 = i;
        if(i != *len_1)
        {
            // for (int k = 0; k < j; k++) {
            //     free((*points)[k]);
            // }
            // free(*points);
            //free if is possible;&& destroy the window
            write(1, "You must have the same number of columns in all rows\n", 53);//replace with my_exit
            exit(1);
        }  
        j++;
        rows = rows->next;
    }
}

// void iso_project(t_fdf *fdf, t_point *points, t_point *iso_points)
// {
//     if (!fdf || !points || !iso_points) {
//         printf("Null pointer in iso_project\n");
//         exit(1);
//         return;
//     }
//     // printf("[%f]\n",fdf->angle);
//     iso_points->x = ((points->x - points->y) * cos(fdf->angle) );
//     iso_points->y = (((points->x + points->y) * sin(fdf->angle) - points->z));
//     // printf("[%f,%f,%f]\n",iso_points->x,iso_points->y,points->z);
// }

void iso_project(t_fdf *fdf, t_point *points, t_point *iso_points)
{
    double alt;
    
    if (!fdf || !points || !iso_points) {
        printf("Null pointer in iso_project\n");//change
        exit(1);
        return;
    }
    // printf("[%f]\n",fdf->angle);
    
    //rot z
    fdf->angle = (42 * (M_PI / 180));
    iso_points->x = (points->x * cos(fdf->angle) - (points->y *  sin(fdf->angle)));
    iso_points->y = (points->y * cos(fdf->angle) + (points->x *  sin(fdf->angle)));

    //ret x    
    fdf->angle = atan(1 / sqrt(2) * 1.7);
    alt = iso_points->y;
    iso_points->y = (iso_points->y * cos(fdf->angle) - (points->z *  sin(fdf->angle)));
    iso_points->z = ((alt *  sin(fdf->angle)) + (points->z *  cos(fdf->angle)));
    // printf("[%f,%f,%f]\n",iso_points->x,iso_points->y,points->z);
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
int dim_iso(t_fdf *fdf)
{
    int i, j;

    if (!fdf->map.iso_points)
    {
        fdf->map.iso_points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
        if (!fdf->map.iso_points)
            return 0; // Échec
    }

    j = 0;
    // printf("width = %d, height = %d\n",fdf->map.width,fdf->map.height);
    while (j < fdf->map.height)
    {
        fdf->map.iso_points[j] = NULL;
        if (!fdf->map.iso_points[j])
        {
            fdf->map.iso_points[j] = (t_point *)malloc(sizeof(t_point) * fdf->map.width);
            if (!fdf->map.iso_points[j])
            {
                // Libérer la mémoire déjà allouée
                while (j > 0)
                {
                    j--;
                    free(fdf->map.iso_points[j]);
                }
                free(fdf->map.iso_points);
                fdf->map.iso_points = NULL;
                return 0; // Échec
            }
        }

        i = 0;
        while (i < fdf->map.width)
        {
            // (fdf->map.iso_points[j][i]).x = 900;
            // (fdf->map.iso_points[j][i]).y = 1337;
            
            // printf("[%d,%d]\n",fdf->map.points[j][i].x,fdf->map.points[j][i].y);
            iso_project(fdf, &(fdf->map.points[j][i]), &(fdf->map.iso_points[j][i]));
            // printf("[%d,%d]", (fdf->map.iso_points[j][i]).x, (fdf->map.iso_points[j][i]).y);
            i++;
        }
        j++;
    }
    // exit(1);
    calc_iso_len(&(fdf->map));
    return 1; // Succes
}

void scale_points(t_fdf *fdf)
{
    int i;
    int j;

    j = 0;
    printf("in scale function sc = % lf\n",fdf->scale);
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
            return ; // Échec
    }    
    j = 0;
    while(j < fdf.map.height)
    {
        (*draw_points)[j] = NULL;
        if (!(*draw_points)[j])
        {
            (*draw_points)[j] = (t_point *)malloc(sizeof(t_point) * fdf.map.width);
            if (!(*draw_points)[j])
                return ;// a verif apres
        }
        i = 0;
        while(i < fdf.map.width)
        {
            (*draw_points)[j][i].x = fdf.map.iso_points[j][i].x + nbr[0];
            (*draw_points)[j][i].y = fdf.map.iso_points[j][i].y + nbr[1];
            // printf("[%d,%d]\n",fdf.map.iso_width,fdf.map.iso_height);
            
            // fdf.offset_x = ((fdf.width/2) - (fdf.map.iso_width/2)) ;
            // fdf.offset_y = ((fdf.height/2) - (fdf.map.iso_height/2));
            (*draw_points)[j][i].x += fdf.offset_x ;
            (*draw_points)[j][i].y += fdf.offset_y;
            // printf("[%f,%f]\n",(*draw_points)[j][i].x,(*draw_points)[j][i].y);
            i++;
        }
        j++;
    }
}

// void draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, uint32_t color)
// {
//     int dx = fabs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//     int dy = -fabs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//     int err = dx + dy, e2;

//     while (1) {
//         if (x0 >= 0 && x0 < (int)fdf->width && y0 >= 0 && y0 < (int)fdf->height)
//             mlx_put_pixel(fdf->img, x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = 2 * err;
//         if (e2 >= dy) { err += dy; x0 += sx; }
//         if (e2 <= dx) { err += dx; y0 += sy; }
//     }
// }

// void draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, unsigned int color)
// {
//     int dx, dy, steps, i;
//     float x_inc, y_inc, x, y;

//     dx = x1 - x0;
//     dy = y1 - y0;

//     if (fabs(dx) > fabs(dy))
//         steps = fabs(dx);
//     else
//         steps = fabs(dy);

//     x_inc = (float)dx / steps;
//     y_inc = (float)dy / steps;

//     x = x0;
//     y = y0;

//     i = 0;
//     while (i <= steps)
//     {
//         mlx_put_pixel(fdf->img, round(x), round(y), color);
//         x += x_inc;
//         y += y_inc;
//         i++;
//     }
// }

uint32_t interpolate_color(uint32_t color1, uint32_t color2, float t)
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
        unsigned int color = interpolate_color(color1, color2, t);
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

    
    if (fdf->img) mlx_delete_image(fdf->mlx, fdf->img);
    fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
    if (!fdf->img) my_exit("Failed to create image");
    draw_points = NULL;
    calc_draw_points(*fdf, &draw_points);
    j = 0;
    // printf("[%d,%d]",fdf->map.height,fdf->map.width);
    while(j < fdf->map.height)
    {
        
        // printf("[%d,%d]",fdf->map.width,fdf->map.height);
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
    // TODO: free draw_points
}

void rotate_map_z(t_fdf *fdf, double angle)// change _x and _z
{
    int i, j;
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    
    j = 0;
    while ( j < fdf->map.height)
    {
        i = 0;
        while ( i < fdf->map.width)
        {
            double x = fdf->map.iso_points[j][i].x - fdf->map.width / 2;
            double y = fdf->map.iso_points[j][i].y - fdf->map.height / 2;
            
            fdf->map.iso_points[j][i].x = x * cos_a - y * sin_a + fdf->map.width / 2;
            fdf->map.iso_points[j][i].y = x * sin_a + y * cos_a + fdf->map.height / 2;
            i++;
        }
        j++;
    }
    calc_iso_len(&(fdf->map));
    draw_map(fdf);
}

void rotate_map_y(t_fdf *fdf, double angle)
{
    int i, j;
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    
    j = 0;
    while ( j < fdf->map.height)
    {
        i = 0;
        while ( i < fdf->map.width)
        {
            double x = fdf->map.iso_points[j][i].x;
            double z = fdf->map.iso_points[j][i].z;
            
            fdf->map.iso_points[j][i].x = x * cos_a - z * sin_a;
            fdf->map.iso_points[j][i].z = x * sin_a + z * cos_a;
            i++;
        }
        j++;
    }
    calc_iso_len(&(fdf->map));
    draw_map(fdf);
}
void rotate_map_x(t_fdf *fdf, double angle)
{
    int i, j;
    double cos_a = cos(angle);
    double sin_a = sin(angle);
    
    j = 0;
    while ( j < fdf->map.height)
    {
        i = 0;
        while ( i < fdf->map.width)
        {
            double x = fdf->map.iso_points[j][i].x;
            double y = fdf->map.iso_points[j][i].y;
            
            fdf->map.iso_points[j][i].x = x * cos_a - y * sin_a;
            fdf->map.iso_points[j][i].y = x * sin_a + y * cos_a;
            i++;
        }
        j++;
    }
    calc_iso_len(&(fdf->map));
    draw_map(fdf);
}

// void switch_projection(t_fdf *fdf) {
//     fdf->projection = !fdf->projection;
//     draw_map(fdf);
// }

void translate_map(t_fdf *fdf, int dx, int dy)
{
    calc_iso_len(&(fdf->map));
    fdf->offset_x += dx;
    fdf->offset_y += dy; 
    draw_map(fdf);
}

void zoom_map(t_fdf *fdf, double factor)
{
    int i;
    int j;
    int x;
    int y;


    fdf->scale *= factor;
    if(!fdf->projection)
        dim_iso(fdf);
    else
    {
        fdf->projection = 1;
        j = 0;
        while(j < fdf->map.nbr_y)
        {
            i = 0;
            while(i < fdf->map.nbr_x)
            {
                x = fdf->map.points[j][i].x;
                y = fdf->map.points[j][i].y;
                fdf->map.iso_points[j][i].x = x;
                fdf->map.iso_points[j][i].y = y;
                i++;
            }
            j++;
        }
        calc_iso_len(&(fdf->map));
    }
        
    scale_points(fdf);
    fdf->offset_x = ((fdf->width/2) - (fdf->map.iso_width/2)) ;
    fdf->offset_y = ((fdf->height/2) - (fdf->map.iso_height/2));
    draw_map(fdf);
}
void adjust_height_scale(t_fdf *fdf, double factor)
{
    int i, j;
    for (j = 0; j < fdf->map.height; j++)
    {
        for (i = 0; i < fdf->map.width; i++)
        {
            fdf->map.points[j][i].z *= factor;
        }
    }
    dim_iso(fdf);
    scale_points(fdf);
    fdf->offset_x = ((fdf->width/2) - (fdf->map.iso_width/2)) ;
    fdf->offset_y = ((fdf->height/2) - (fdf->map.iso_height/2));
    draw_map(fdf);
}

void project_parallel(t_fdf *fdf) {
    // Coefficients de transformation pour une projection isométrique
    int i;
    int j;
    int x;
    int y;

    fdf->projection = 1;
    j = 0;
    while(j < fdf->map.nbr_y)
    {
        i = 0;
        while(i < fdf->map.nbr_x)
        {
            x = fdf->map.points[j][i].x;
            y = fdf->map.points[j][i].y;
            fdf->map.iso_points[j][i].x = x;
            fdf->map.iso_points[j][i].y = y;
            i++;
        }
        j++;
    }
    // dim_iso(fdf);
    scale_points(fdf);
    fdf->offset_x = ((fdf->width/2) - (fdf->map.iso_width/2)) ;
    fdf->offset_y = ((fdf->height/2) - (fdf->map.iso_height/2));
    draw_map(fdf);
}

void reset(t_fdf *fdf)
{
    fdf->projection = 0;
    if(fdf->map.height > fdf->height)
        fdf->height = fdf->map.height;
    if(fdf->map.width > fdf->width)
        fdf->width = fdf->map.width;//verif max_width and max_height
    if((fdf->height)/fdf->map.iso_height <= (fdf->width)/fdf->map.iso_width)
        fdf->scale = (fdf->height - 100)/fdf->map.iso_height;
    else
        fdf->scale = (fdf->width - 100)/fdf->map.iso_width;
    dim_iso(fdf);  
    scale_points(fdf);
    fdf->offset_x = ((fdf->width/2) - (fdf->map.iso_width/2)) ;
    fdf->offset_y = ((fdf->height/2) - (fdf->map.iso_height/2));
    draw_map(fdf);
}
void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fdf *fdf = (t_fdf *)param;

    if (keydata.action == MLX_RELEASE)
        return;

    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(fdf->mlx);
    else if (keydata.key == MLX_KEY_UP)
        translate_map(fdf, 0, -10);
    else if (keydata.key == MLX_KEY_DOWN)
        translate_map(fdf, 0, 10);
    else if (keydata.key == MLX_KEY_LEFT)
        translate_map(fdf, -10, 0);
    else if (keydata.key == MLX_KEY_RIGHT)
        translate_map(fdf, 10, 0);
    else if (keydata.key == MLX_KEY_KP_ADD)
        zoom_map(fdf, 1.1);
    else if (keydata.key == MLX_KEY_KP_SUBTRACT)
        zoom_map(fdf, 0.9);
    else if (keydata.key == MLX_KEY_R)
        rotate_map_y(fdf, 30 * (M_PI / 180));
        else if (keydata.key == MLX_KEY_Y)
        rotate_map_z(fdf, -30 * (M_PI / 180));
    else if (keydata.key == MLX_KEY_P)
        project_parallel(fdf);
    else if (keydata.key == MLX_KEY_W)
        adjust_height_scale(fdf, 1.1);
    else if (keydata.key == MLX_KEY_Q)
        adjust_height_scale(fdf, 0.9);
    else if (keydata.key == MLX_KEY_S)
        adjust_height_scale(fdf, -0.9);
    else if (keydata.key == MLX_KEY_0)
        reset(fdf);
}

int main(int argc, char **argv)
{
    t_fdf fdf;
    
    if(argc != 2)
        return(write(1,"The number of arguments is not correct; we need 1 parameter\n",60),1);
    if(ft_strlen(argv[1]) < 4 || (ft_strlen(argv[1]) > 4 && ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4],".fdf",4)))
        return(write(1,"The file must have an extension of .fdf\n",39),1);
    fdf.map.points = NULL;
    fdf.map.iso_points = NULL;
    input(argv[1], &(fdf.map.points), &(fdf.map.height), &(fdf.map.width));//changer len
    fdf.map.nbr_x = fdf.map.width;
    fdf.map.nbr_y = fdf.map.height;
    fdf.angle = 30 * (PI / 180.0);
    if (!dim_iso(&fdf))
    {
        write(1,"Failed to create isometric projection\n",38);//changer apres
        // free et sortie
        return 1;
    }
    fdf.height = HEIGHT;
    fdf.width = WIDTH;
    if(fdf.map.height > fdf.height)
        fdf.height = fdf.map.height;
    if(fdf.map.width > fdf.width)
        fdf.width = fdf.map.width;//verif max_width and max_height
    if((fdf.height)/fdf.map.iso_height <= (fdf.width)/fdf.map.iso_width)
        fdf.scale = (fdf.height - 100)/fdf.map.iso_height;
    else
        fdf.scale = (fdf.width - 100)/fdf.map.iso_width;
    fdf.projection = 0;
    scale_points(&fdf);
    fdf.mlx = mlx_init(WIDTH, HEIGHT, "FDF", 1);
    if (!fdf.mlx)
        my_exit("Failed to initialize MLX");
    fdf.offset_x = ((fdf.width/2) - (fdf.map.iso_width/2)) ;
    fdf.offset_y = ((fdf.height/2) - (fdf.map.iso_height/2));
    draw_map(&fdf);
    mlx_key_hook(fdf.mlx, key_hook, &fdf);
    mlx_loop(fdf.mlx);
}