/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:22:11 by ouidriss          #+#    #+#             */
/*   Updated: 2023/05/19 10:39:44 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	size_t			n;
	unsigned char	*alloc;

	i = 0;
	n = (count * size);
	if (n == 0)
		return (NULL);
	alloc = (unsigned char *)malloc(n);
	if (!alloc)
		return (NULL);
	while (i < n)
	{
		*(char *)(alloc + i) = '\0';
		i ++;
	}
	return (alloc);
}

char	*set_full_buffer_size(int fd, char *rem)
{
	char	*result_read;
	int		i;

	i = 1;
	result_read = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!result_read)
		return (NULL);
	while (!ft_strchr(result_read, '\n') && i)
	{
		i = read(fd, result_read, BUFFER_SIZE);
		if (i == 0)
			break ;
		if (i == -1)
			return (free(rem), free(result_read), NULL);
		result_read[i] = '\0';
		rem = _ft_strjoin(rem, result_read);
	}
	free (result_read);
	return (rem);
}

char	*set_remaing_result(char *bf)
{
	int		i;

	i = 0;
	while (bf[i] != '\0')
	{
		if (bf[i] == '\n')
			break ;
		i++;
	}
	if (bf[i] == '\0' || bf[i + 1] == '\0')
		return (NULL);
	return (ft_strdup(bf + (i + 1)));
}

char	*set_full_line(char *bf)
{
	char	*line;
	int		i;

	i = 0;
	while (bf[i] != '\0')
	{
		if (bf[i] == '\n')
			break ;
		i ++;
	}
	if (bf[i] == '\0')
		return (bf);
	line = malloc (sizeof(char) * (i + 2));
	if (!line)
		return (free(line), NULL);
	line [i + 1] = '\0';
	while (i >= 0)
	{
		line[i] = bf[i];
		i --;
	}
	free (bf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = set_full_buffer_size(fd, remaining);
	if (!buffer)
		return (remaining = NULL, NULL);
	remaining = set_remaing_result(buffer);
	buffer = set_full_line(buffer);
	return (buffer);
}
