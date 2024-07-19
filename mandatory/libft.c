/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:40:16 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/05 16:33:47 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

// int	ft_strchr(char *s, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] == (char)c)
// 			return (i + 1);
// 		i++;
// 	}
// 	return (0);
// }

char	*ft_strjoin(char *s1, char *s2, int x)
{
	size_t	i;
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((!s1 && !s2) || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1 && s1[(++i)])
		str[i] = s1[i];
	if (!s1)
		i = 0;
	while (s2[(i++) - len1])
		str[i - 1] = s2[i - len1 - 1];
	str[i - 1] = '\0';
	if (x == 1)
		free (s1);
	return (str);
}

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]))
// 	{
// 		if ((unsigned char)s1[i] > (unsigned char)s2[i])
// 			return (1);
// 		if ((unsigned char)s1[i] < (unsigned char)s2[i])
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}