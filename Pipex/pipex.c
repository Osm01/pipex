/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:16:19 by ouidriss          #+#    #+#             */
/*   Updated: 2023/06/13 10:58:05 by ouidriss         ###   ########.fr       */
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
	while (t_p->split_env && t_p->split_env[y])
	{
		t_p->get_cmd = ft_strjoin(t_p->split_env[y], t_p->cmd);
		if (access(t_p->get_cmd, X_OK) == 0)
			return (t_p->get_cmd);
		y ++;
	}
	return (NULL);
}

void	child_process_function01(t_pipex *t_p)
{
	close(t_p->fd[0]);
	t_p->infile = open(t_p->argv[1], O_RDONLY);
	if (t_p->infile < 0)
		return (perror("Error open infile"), exit(EXIT_FAILURE));
	else
		dup2(t_p->infile, STDIN_FILENO);
	dup2(t_p->fd[1], STDOUT_FILENO);
	t_p->split_arg = ft_split(t_p->argv[2], 32);
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
		return (perror("Command not execuatble"), exit(EXIT_FAILURE));
	free_necessary(t_p);
	if (execve(t_p->get_cmd, t_p->split_arg, NULL) == -1)
		return (perror("Error execve"), exit(EXIT_FAILURE));
}

void	child_process_function02(t_pipex *t_p)
{
	close(t_p->fd[1]);
	t_p->outfile = open(t_p->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (t_p->outfile < 0)
		return (perror("Error outfile"), exit(EXIT_FAILURE));
	dup2(t_p->outfile, STDOUT_FILENO);
	dup2(t_p->fd[0], STDIN_FILENO);
	t_p->split_arg = ft_split(t_p->argv[3], 32);
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
		return (perror("Command not execuatble"), exit(2));
	free_necessary(t_p);
	if (execve(t_p->get_cmd, t_p->split_arg, NULL) == -1)
		return (perror("Error execve"), exit(3));
}

void	body_pipex(t_pipex *t_p)
{
	if (pipe(t_p->fd) == -1)
	{
		perror("Error pipe");
		exit(1);
	}
	t_p->pid = fork();
	if (t_p->pid == -1)
		perror("Fork Error");
	else if (t_p->pid == 0)
		child_process_function01(t_p);
	else
	{
		t_p->pid = fork();
		if (t_p->pid == 0)
			child_process_function02(t_p);
		else
			wait(NULL);
	}
}

int	main(int argc, char *argv[], char	*env[])
{
	t_pipex	*t_p;

	t_p = (t_pipex *)malloc(sizeof(t_pipex));
	t_p->env = env;
	t_p->argc = argc;
	t_p->argv = argv;
	if (t_p->argc == 5)
	{
		body_pipex(t_p);
		close(t_p->fd[0]);
		close(t_p->fd[1]);
	}
	else
		perror("Error problem arg pass");
	free(t_p);
	while (wait(NULL) != -1)
		;
	return (0);
}
