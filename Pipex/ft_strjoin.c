/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:44:19 by ouidriss          #+#    #+#             */
/*   Updated: 2023/05/18 22:31:22 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned long	i;
	unsigned long	index;

	i = 0;
	index = 0;
	if (!s1)
		s1 = ft_strdup("");
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (0);
	while (index < ft_strlen(s1))
		*(join + i++) = *(char *)(s1 + index++);
	index = 0;
	while (index < ft_strlen(s2))
		*(join + i++) = *(char *)(s2 + index++);
	*(join + i) = '\0';
	return (join);
}
