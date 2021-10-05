/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:49:36 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/05 12:25:11 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_redirection_bonus(char *file2, int *pipe_fd, int stdin_saved)
{
	int	fd_file2;

	fd_file2 = open(file2, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_file2 == -1)
	{
		ft_putstr_fd("Error, open file2 failed.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN) == -1)
	{
		ft_putstr_fd("Error, in stdin parent redirect\n", 2);
		close(fd_file2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file2, STDOUT) == -1)
	{
		dup2(stdin_saved, 0);
		close(fd_file2);
		ft_putstr_fd("Error, in stdout parent redirect\n", 2);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	close(fd_file2);
}

void	parent_bonus(char *file2, int *pipe_fd, char *command2, char **env)
{
	int	stdin_saved;
	int	stdout_saved;

	stdin_saved = dup(STDIN);
	stdout_saved = dup(STDOUT);
	parent_redirection_bonus(file2, pipe_fd, stdin_saved);
	execute_cmd(command2, env);
	dup2(stdin_saved, 0);
	dup2(stdout_saved, 1);
	exit(EXIT_SUCCESS);
}

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
