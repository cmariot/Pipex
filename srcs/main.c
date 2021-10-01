/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/30 18:19:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	heredoc_bonus(char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, the bonus fork failed.\n", 2);
		return (-1);
	}
	if (pid == 0)
		child_bonus(argv, env, fd);
	else
	{
		waitpid(pid, &status, 0);
		parent_bonus(argv[5], fd, argv[4], env);
		close(fd[1]);
	}
	return (0);
}

int	mandatory(char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, the main fork failed.\n", 2);
		return (-1);
	}
	if (pid == 0)
		child(argv[1], fd, argv[2], env);
	else
	{
		waitpid(pid, &status, 0);
		parent(argv[4], fd, argv[3], env);
		close(fd[1]);
	}
	return (0);
}

/* In the main we create a pipe, the fd[0] and the fd[1] are linked,
   We also create a fork,
   The parent process will wait until it's child finished. */
int	main(int argc, char **argv, char **env)
{
	if (argc == 5)
		mandatory(argv, env);
	else if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
		heredoc_bonus(argv, env);
	else if (argc >= 6)
		multiple_pipelines_bonus(argc, argv, env);
	else if (argc <= 4)
	{
		ft_putstr_fd("Mandatory usage : ./pipex file1 'cmd1' 'cmd2' file2\n", 2);
		ft_putstr_fd("Bonus usage : ./pipex here_doc limiter 'cmd1' 'cmd2' file2\n", 2);
	}
	return (0);
}
