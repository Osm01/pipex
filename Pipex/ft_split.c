/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:49:03 by ouidriss          #+#    #+#             */
/*   Updated: 2023/05/03 21:55:49 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	count_element_split_by(char const *s, char c)
{
	unsigned int	i;
	size_t			count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count ++;
			while (s[i] != '\0' && s[i] != c)
			{
				i ++;
			}
			if (s[i] == '\0')
				break ;
		}
		i ++;
	}
	return (count);
}

size_t	find_end(char const *s, char c, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			break ;
		i ++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	start;
	size_t	y;

	if (!s)
		return (0);
	i = 0;
	y = 0;
	start = 0;
	split = malloc(sizeof(char *) * (count_element_split_by(s, c) + 1));
	if (!split)
		return (0);
	split[count_element_split_by(s, c)] = (char *) NULL;
	while (y < ft_strlen(s))
	{
		if (s[y] != c)
		{
			start = y;
			y = find_end(s, c, y);
			split[i ++] = ft_substr(s, start, y - start);
		}
		y ++;
	}
	return (split);
}
