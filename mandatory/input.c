/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:49:39 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/19 13:18:23 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_close(char *str, int fd, char *msg)
{
	free(str);
	close(fd);
	my_exit(msg);
}

int	count_lines(int fd, t_row **rows)
{
	int		nbr;
	char	*str;
	t_row	*tmp;

	nbr = 0;
	tmp = NULL;
	str = get_next_line(fd);
	if (!str || !str[0])
		my_close(str, fd, "empty file\n");
	while(str)
	{
		if(!*rows)
		{
			*rows = (t_row *)malloc(sizeof(t_row));
			if(!*rows)
				my_close(str, fd, "Memory allocation failed\n");
			(*rows)->row = str;
			(*rows)->next = NULL;
			tmp = *rows;
		}
		else
		{
			tmp->next = (t_row *)malloc(sizeof(t_row));
			if(!tmp->next)
				my_close(str, fd, "Memory allocation failed\n");
			tmp = tmp->next;
			tmp->row = str;
			tmp->next = NULL;
		}
		nbr++;
		str = get_next_line(fd);
	}
	return (nbr);
}

void	input(char *argv, t_point ***points, double *len_0, double *len_1)
{
	int fd;
	int j;
	int i;
	t_row   *rows;
	t_row   *tmp;
	char **split;
	
	j = 0;
	rows = NULL;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		my_exit("error");
	*len_0 = count_lines(fd, &rows);
	*points = (t_point **)malloc(sizeof(t_point *) * (*len_0));
	if (!*points)
		err_alloc(&rows, fd);
	while (j < *len_0)
	{
		i = 0;
		split = ft_split(rows->row, ' ');
		while (split[i] != NULL)
			i++;   
		(*points)[j] = (t_point *)malloc(sizeof(t_point) * i);
		if (!(*points)[j])
			err_jalloc(*points, j, split, fd, &rows);
		i = 0;
		while (split[i] != NULL)
			add_content(t_point ***points,)
		if(j == 0)
			*len_1 = i;
		if(i != *len_1)
		{
			free_double_list(*points, *len_0);
			free_list(&rows);
			close(fd);
			my_exit("You must have the same number of columns in all rows");
		}  
		j++;
		tmp = rows;
		rows = rows->next;
		free(tmp->row);
		free(tmp);
		free(split);
	}
	close(fd); 
}
