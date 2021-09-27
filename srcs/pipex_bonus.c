/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:13:10 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/27 19:58:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// get_next_line(0) -> STDOUT
void	child_bonus(char **argv, char **env, int *pipe_fd)
{
	int		stdout_saved;
	char	*line;
	char	*limiter;


	stdout_saved = dup(STDOUT);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT);
	limiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_putstr_fd("heredoc> ", stdout_saved);
		line = get_next_line(STDIN);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		else
		{
			ft_putstr(line);
			free(line);
		}
	}
	ft_putstr(*env);
	free(limiter);
	exit(EXIT_SUCCESS);
}

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
		//parent(argv[4], fd, argv[3], env);
		close(fd[1]);
	}
	return (0);
}

int	here_doc(char **argv, char **env)
{
	char *here_doc;

	here_doc = argv[1];
	if (ft_strcmp(here_doc, "here_doc"))
	{
		ft_putstr_fd("Error, usage : ./pipex here_doc file1 'cmd1' 'cmd2' file2\n", 2);
		return (-1);
	}
	fork_bonus(argv, env);
	return (0);
}
