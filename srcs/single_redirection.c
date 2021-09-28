/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:45:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/28 17:46:34 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Create the redirection FD[0] (STDIN) --> FILE2 (STDOUT) */
void	parent_redirection(char *file2, int *pipe_fd, int stdin_saved)
{
	int	fd_file2;

	fd_file2 = open(file2, O_RDWR | O_CREAT | O_TRUNC, 0644);
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

/* In the parent, we want fd[0] as STDIN and file2 as STDOUT
   We open the file2, if it doesn't exist it's create,
   Create redirections with dup2(), close unused FD,
   Execute command1 (input = file1, output = fd[1])
   Restore the default redirections. */
void	parent(char *file2, int *pipe_fd, char *command2, char **env)
{
	int	stdin_saved;
	int	stdout_saved;

	stdin_saved = dup(STDIN);
	stdout_saved = dup(STDOUT);
	parent_redirection(file2, pipe_fd, stdin_saved);
	execute_cmd(command2, env);
	dup2(stdin_saved, 0);
	dup2(stdout_saved, 1);
	exit(EXIT_SUCCESS);
}

/* Create the redirection FILE1 (SDTIN) --> FD[1] (STDOUT) */
void	child_redirection(char *file1, int *pipe_fd, int stdin_saved)
{
	int	fd_file1;

	fd_file1 = open(file1, O_RDONLY);
	if (fd_file1 == -1)
	{
		ft_putstr_fd("Error, no such file or directory : ", 2);
		ft_putstr_fd(file1, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file1, STDIN) == -1)
	{
		ft_putstr_fd("Error, in stdin child redirect\n", 2);
		close(fd_file1);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT) == -1)
	{
		ft_putstr_fd("Error, in stdout child redirect\n", 2);
		dup2(stdin_saved, 0);
		close(fd_file1);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(fd_file1);
}

/* In the child, we want file1 as STDIN and fd[1] as STDOUT
   We open the file1,
   Create redirections with dup2(), close unused FD,
   Execute command1 (input = file1, output = fd[1])
   Restore the default redirections. */
void	child(char *file1, int *pipe_fd, char *command1, char **env)
{
	int	stdin_saved;
	int	stdout_saved;

	stdin_saved = dup(STDIN);
	stdout_saved = dup(STDOUT);
	child_redirection(file1, pipe_fd, stdin_saved);
	execute_cmd(command1, env);
	dup2(stdin_saved, 0);
	dup2(stdout_saved, 1);
	exit(EXIT_SUCCESS);
}
