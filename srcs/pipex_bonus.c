/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:13:10 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/28 15:52:00 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_heredoc(char **argv)
{
	int		heredoc_fd;
	char	*limiter;
	char	*line;

	heredoc_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		return (-1);
	limiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT);
		line = get_next_line(STDIN);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		else
		{
			ft_putstr_fd(line, heredoc_fd);
			free(line);
		}
	}
	free(line);
	free(limiter);
	close(heredoc_fd);
	return (0);
}

// get_next_line(0) -> FD[1] (STDOUT)
void	child_bonus(char **argv, char **env, int *pipe_fd)
{
	int		stdin_saved;
	int		stdout_saved;

	if (create_heredoc(argv) == -1)
		ft_putstr_fd("Error, during here_doc file creation.\n", 2);
	stdin_saved = dup(STDIN);
	stdout_saved = dup(STDOUT);
	child_redirection("here_doc", pipe_fd, stdin_saved);
	execute_cmd(argv[3], env);
	unlink("here_doc");
	dup2(stdin_saved, 0);
	dup2(stdout_saved, 1);
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
		parent(argv[5], fd, argv[4], env);
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
