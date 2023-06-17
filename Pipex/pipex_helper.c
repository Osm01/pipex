/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:26:48 by ouidriss          #+#    #+#             */
/*   Updated: 2023/06/13 12:39:22 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_function(t_pipex *t_p)
{
	char	*line;
	char	*limiter;

	t_p->infile = open(t_p->argv[1], O_CREAT | O_WRONLY, 0644);
	if (t_p->infile < 0)
	{
		perror("Error open infile descriptor");
		exit(1);
	}
	limiter = ft_strjoin(t_p->argv[2], "\n");
	write(STDOUT_FILENO, "here_doc> ", sizeof("here_doc> "));
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strcmp(limiter, line))
			break ;
		write(STDOUT_FILENO, "here_doc> ", sizeof("here_doc> "));
		write(t_p->infile, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(limiter);
	close(t_p->infile);
}

void	check_multiple_or_doc(t_pipex *t_p, int *flag_to_inlink, int *index)
{
	if (!ft_strncmp(t_p->argv[1], "here_doc", \
		sizeof("here_doc")) && t_p->argc >= 6)
	{
		here_doc_function(t_p);
		*flag_to_inlink = 1;
		*index = *index + 1;
	}
	t_p->infile = open(t_p->argv[1], O_RDONLY);
	if (*flag_to_inlink)
		t_p->outfile = open(t_p->argv[t_p->argc - 1], \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		t_p->outfile = open(t_p->argv[t_p->argc - 1], \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (t_p->outfile < 0)
		return (perror("Error open outfile"), exit(EXIT_FAILURE));
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i ++;
	}
	free(array);
}

void	free_necessary(t_pipex *t_p)
{
	free_2d_array(t_p->split_env);
	free(t_p->cmd);
}

void	swap_pipes_by_index_and_redirect(t_pipex *t_p, int index, int flag)
{
	close(t_p->fd[0]);
	if (index == 2 || (flag && index == 3))
	{
		if (t_p->infile < 0)
			return (perror("Error open infile"), exit(EXIT_FAILURE));
		else
		{
			dup2(t_p->infile, STDIN_FILENO);
			close(t_p->infile);
		}
	}
	if (index == t_p->argc - 2)
	{
		dup2(t_p->outfile, STDOUT_FILENO);
		close(t_p->outfile);
	}
	else
		dup2(t_p->fd[1], STDOUT_FILENO);
	close(t_p->fd[1]);
}
