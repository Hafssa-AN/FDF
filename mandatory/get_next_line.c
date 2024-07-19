/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:47:42 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/05 16:33:51 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*after(char *container, size_t i)
{
	char	*str;
	size_t	j;

	j = -1;
	str = (char *)malloc((ft_strlen(container) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (container[i + (++j)])
		str[j] = container[i + j];
	str[j] = '\0';
	free (container);
	return (str);
}

char	*cut_line(char *container, size_t *i)
{
	size_t	j;
	char	*str;

	if (!container)
		return (NULL);
	*i = 0;
	while (container[*i] && container[*i] != '\n')
		(*i)++;
	if (container[*i] == '\n')
		(*i)++;
	str = (char *)malloc((*i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = -1;
	while ((++j) < *i)
		str[j] = container[j];
	str[j] = '\0';
	return (str);
}

char	*f_line(char *str, int fd)
{
	int		c;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(buf))
		return (NULL);
	c = 1;
	while (c != 0)
	{
		c = read(fd, buf, BUFFER_SIZE);
		if (c < 0 || (c == 0 && (!str || !str[0])))
		{
			free (buf);
			free (str);
			return (NULL);
		}
		buf[c] = '\0';
		str = ft_strjoin(str, buf, 1);
		if (ft_strchr(buf, '\n') != 0)
			break ;
	}
	free (buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	container = f_line(container, fd);
	if (!container)
		return (NULL);
	line = cut_line(container, &i);
	container = after(container, i);
	return (line);
}
