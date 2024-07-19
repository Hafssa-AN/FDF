/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:42:48 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 13:15:05 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void err_alloc(t_row **rows, int fd)
{
	free_list(rows);
	close(fd);
	my_exit("Memory allocation failed");
}

void err_jalloc(t_point **points, int j, char **split, int fd, t_row **rows)
{
	free_double_list(points, j);
	free_list(rows);
	while(split[j])
		free(split[j--]);
	free(split);
	close(fd);
	my_exit("Memory allocation failed");
}

void add_content(t_point ***points,int *i,)
{
	char **last_split;
	
	(*(*((*points) + j) + i)).x = i;
	(*(*((*points) + j) + i)).y = j;
	last_split = ft_split(split[i], ',');
	free(split[i]);
	(*(*((*points) + j) + i)).z = ft_atoi(last_split[0]);
	if(last_split[1])
		(*(*((*points) + j) + i)).color = atoi_exa(last_split[1]);
	else if((*(*((*points) + j) + i)).z == 0)
		(*(*((*points) + j) + i)).color = atoi_exa("0xB00000");
	else
		(*(*((*points) + j) + i)).color = atoi_exa("0xE5C0C0");
	i++;
	free(last_split[0]);
	free(last_split[1]);
	free(last_split);
}