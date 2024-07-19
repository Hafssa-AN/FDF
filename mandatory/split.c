/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:55:40 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/15 16:21:26 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int count_words(const char *str, char c)
{
    int i;
    int count;
    int in_word;

	i = 0;
	count = 0;
	in_word = 0;
    while (str[i] != '\0')
	{
        if (str[i] != c && str[i] != '\n')
		{
            if (!in_word) 
			{
                count++;
                in_word = 1;
            }
        }
		else
            in_word = 0;
        i++;
    }
    return count;
}

static char	*new_word(const char *s, int *i, char c)
{
	int		j;
	int		start;
	char	*words;

	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	words = (char *)malloc ((*i - start) + 1);
	if (words == NULL)
		return (NULL);
	j = 0;
	while (start < *i)
	{
		words[j] = s[start];
		start++;
		j++;
	}
	words[j] = '\0';
	return (words);
}

static char	**free_words(char **words, int j)
{
	while (j >= 0)
	{
		free(words[j]);
		j--;
	}
	free(words);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	if (s == NULL)
		return (NULL);
	words = malloc ((count_words(s, c) + 1) * sizeof (char *));
	if (words == NULL)
		return (NULL);
	j = 0;
	while (j < count_words(s, c) && s[i])
	{
		if (s[i] != c)
		{
			words[j] = new_word(s, &i, c);
			if (words[j] == NULL)
				return (free_words(words, (j - 1)));
			j++;
		}
		i++;
	}
	words[j] = NULL;
	return (words);
}
int	ft_atoi(const char *str)
{
	int		i;
	int		sg;
	long	nb;

	sg = 0;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-' )
	{
		if (str[i] == '-')
			sg = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if(nb > 2147483647 || nb < -2147483648)
			my_exit("not valid value");
		i++;
	}
	if (sg == 1)
		return (nb * -1);
	return (nb);
}

int hexCharToValue(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
	else if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
	return(-1);//check after if i have -1 ??!!
}
unsigned int atoi_exa(char *str)
{
	int i;
	char *tab;
	unsigned int nb;
	
	tab = "0123456789abcdef";//verifie if u need to allocate
	i = 0;
	nb = 0;
	// if(ft_strlen(str) == 8 )
	// 	str =ft_strjoin(str, "FF",0);//verifier cette condition
	while(str[i] && str[i] == ' ')
		i++;
	if(str[i] && (str[i] == '-' || str[i] == '+'))
		my_exit("don't use - or + in the color value");//change it wit error dont use perror
	if(str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	else
		my_exit("the color must be in hexadecimal");//change it wit error 
	while(str[i] && ((str[i] >= '0' && str[i] <= '9') || 
			(str[i] >= 'a' && str[i] <= 'f') 
			|| (str[i] >= 'A' && str[i] <= 'F')))
		nb = nb * 16 + hexCharToValue(str[i++]);
	if(str[i] == '\0' || str[i] == '\n')
		return((nb << 8) | 0xFF);
	else
		my_exit("not a good color");
	return(-1);//check after
}
