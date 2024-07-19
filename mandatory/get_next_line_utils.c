/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:48:45 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/05 16:33:29 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



int	ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return (i + 1);
		i++;
	}
	return (0);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t	i;
// 	char	*str;
// 	size_t	len1;
// 	size_t	len2;

// 	printf("in strjoin %s et %s\n",s1,s2);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	if ((!s1 && !s2) || !s2)
// 		return (NULL);
// 	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
// 	if (!str)
// 		return (NULL);
// 	i = -1;
// 	while (s1 && s1[(++i)])
// 		str[i] = s1[i];
// 	if (!s1)
// 		i = 0;
// 	while (s2[(i++) - len1])
// 		str[i - 1] = s2[i - len1 - 1];
// 	str[i - 1] = '\0';
// 	printf("########################## %s\n",str);
// 	if (s1)
// 	{
		
// 	}
//         free(s1);  // Ne libère que si s1 a été alloué dynamiquement
// 	return (str);
// }
