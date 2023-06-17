/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:12:16 by ouidriss          #+#    #+#             */
/*   Updated: 2023/06/16 18:22:00 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(t_pipex *t_p)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	t_p->get_cmd = NULL;
	while (t_p->env[i])
	{
		if (ft_strncmp(t_p->env[i], "PATH", 3) == 0)
			t_p->get_cmd = t_p->env[i];
		i ++;
	}
	if (!t_p->get_cmd)
		return (NULL);
	t_p->get_cmd = t_p->get_cmd + 5;
	t_p->split_env = ft_split(t_p->get_cmd, ':');
	while (t_p->split_env[y])
	{
		t_p->get_cmd = ft_strjoin(t_p->split_env[y], t_p->cmd);
		if (access(t_p->get_cmd, X_OK) == 0)
			return (t_p->get_cmd);
		y ++;
	}
	return (NULL);
}

void	child_process_function(t_pipex *t_p, int index)
{
	t_p->split_arg = ft_split(t_p->argv[index], 32);
	if (access(t_p->split_arg[0], X_OK) == 0 && \
	ft_strchr(t_p->split_arg[0], '/'))
	{
		if (execve(t_p->split_arg[0], t_p->split_arg, NULL) == -1)
			return (perror("Error child execve"), exit(EXIT_FAILURE));
	}
	if (ft_strchr(t_p->split_arg[0], '.') || ft_strchr(t_p->split_arg[0], '/'))
		return (perror("Error command not found"), exit(EXIT_FAILURE));
	t_p->cmd = ft_strjoin("/", t_p->split_arg[0]);
	t_p->get_cmd = get_command_path(t_p);
	if (t_p->get_cmd == NULL)
		return (perror("Error find path"), exit(2));
	free_necessary(t_p);
	if (execve(t_p->get_cmd, t_p->split_arg, NULL) == -1)
		return (perror("Error execve"), exit(3));
}

void	re_child_process_function(t_pipex *t_p, int index, int flag)
{
	if (pipe(t_p->fd) == -1)
		return (perror("Error pipe"), exit(EXIT_FAILURE));
	t_p->pid = fork();
	if (t_p->pid == -1)
		perror("Fork Error");
	else if (t_p->pid == 0)
	{
		swap_pipes_by_index_and_redirect(t_p, index, flag);
		child_process_function(t_p, index);
	}
	else
	{
		dup2(t_p->fd[0], STDIN_FILENO);
		close(t_p->fd[1]);
	}
}

void	init_values(t_pipex *t_p, char	*env[], char	*argv[], int argc)
{
	t_p->env = env;
	t_p->argc = argc;
	t_p->argv = argv;
}

int	main(int argc, char *argv[], char	*env[])
{
	t_pipex	*t_p;
	int		index;
	int		flag_to_inlink;

	t_p = (t_pipex *)malloc(sizeof(t_pipex));
	init_values(t_p, env, argv, argc);
	flag_to_inlink = 0;
	index = 2;
	if (t_p->argc >= 5)
	{
		check_multiple_or_doc(t_p, &flag_to_inlink, &index);
		while (index <= t_p->argc - 2)
			re_child_process_function(t_p, index ++, flag_to_inlink);
		if (flag_to_inlink)
			unlink("here_doc");
		while (wait(NULL) != -1)
			;
		return (close(t_p->infile), close(t_p->fd[0]), close(t_p->fd[1]), \
		close (t_p->outfile), free (t_p), 0);
	}
	else
		perror ("Error problem arg pass");
	free (t_p);
	return (EXIT_SUCCESS);
}
