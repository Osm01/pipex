/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:46:19 by ouidriss          #+#    #+#             */
/*   Updated: 2023/06/13 12:36:02 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct struct_pipex
{
	int		infile;
	int		outfile;
	int		argc;
	char	**argv;
	char	**env;
	int		fd[2];
	pid_t	pid;
	char	*cmd;
	char	*get_cmd;
	char	**split_arg;
	char	**split_env;
}	t_pipex;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(char const *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *str, int c);
char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	check_multiple_or_doc(t_pipex *t_p, int *flag_to_inlink, int *index);
void	free_necessary(t_pipex *t_p);
char	*_ft_strjoin(char *s1, char *s2);
void	swap_pipes_by_index_and_redirect(t_pipex *t_p, int index, int flag);

#endif
