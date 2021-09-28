/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/28 17:51:58 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_bonus(char **argv, char **env)
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
	{
		child_bonus(argv, env, fd);
	}
	else
	{
		waitpid(pid, &status, 0);
		parent_bonus(argv[5], fd, argv[4], env);
		close(fd[1]);
	}
	return (0);
}

int	here_doc(char **argv, char **env)
{
	char	*here_doc;

	here_doc = argv[1];
	if (ft_strcmp(here_doc, "here_doc"))
	{
		ft_putstr_fd("Usage : ./pipex here_doc file1 'cmd1' 'cmd2' file2\n", 2);
		return (-1);
	}
	fork_bonus(argv, env);
	return (0);
}

int	simple_redirection_fork(char **argv, char **env)
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
		simple_redirection_fork(argv, env);
	else if (argc == 6)
		here_doc(argv, env);
	else
	{
		ft_putstr_fd("Mandatory usage : ./pipex file1 'cmd1' 'cmd2' file2\n", 2);
		ft_putstr_fd("Bonus usage : ./pipex limiter 'cmd1' 'cmd2' file2\n", 2);
	}
	return (0);
}
