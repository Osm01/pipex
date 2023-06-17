/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_for_get_next_line.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:36:06 by ouidriss          #+#    #+#             */
/*   Updated: 2023/05/19 10:37:53 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*_ft_strjoin(char *s1, char *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	index;

	i = 0;
	index = 0;
	if (!s1)
		s1 = ft_strdup("");
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	while (s1[index])
		*(join + i++) = *(s1 + index++);
	index = 0;
	while (s2[index])
		*(join + i++) = *(s2 + index++);
	*(join + i) = '\0';
	free (s1);
	return (join);
}
