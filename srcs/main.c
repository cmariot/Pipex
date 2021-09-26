/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/26 23:51:07 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* In the parent, we want fd[0] as STDIN and file2 as STDOUT
   We open the file2, if it doesn't exist it's create, 
   Create redirections with dup2(), close unused FD,
   Execute command1 (input = file1, output = fd[1])
   Restore redirections. */
void	parent(char *file2, int *pipe_fd, char *command2, char **env)
{
	int	fd_file2;

	fd_file2 = open(file2, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_file2 == -1)
	{
		ft_putstr_fd("Error, file2 haven't been created in parent process.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN) == -1)
	{
		perror("parent stdin dup2");
		ft_putstr_fd("Error, in parent when dup2(fd[0], STDIN)\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file2, STDOUT) == -1)
	{
		ft_putstr_fd("Error, in parent when dup2(file2, STDOUT)\n", 2);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	close(fd_file2);
	execute_cmd(command2, env);
	dup2(0, pipe_fd[0]);
	dup2(1, fd_file2);
	exit(EXIT_SUCCESS);
}

/* In the child, we want file1 as STDIN and fd[1] as STDOUT
   We open the file1,
   Create redirections with dup2(), close unused FD,
   Execute command1 (input = file1, output = fd[1])
   Restore redirections. */
void	child(char *file1, int *pipe_fd, char *command1, char **env)
{
	int	fd_file1;

	fd_file1 = open(file1, O_RDONLY);
	if (fd_file1 == -1)
	{
		ft_putstr_fd("Error, file1 couldn't be open.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file1, STDIN) == -1)
	{
		ft_putstr_fd("Error, in child when dup2(file1, STDIN)\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT) == -1)
	{
		ft_putstr_fd("Error, in child when dup2(fd[1], STDOUT)\n", 2);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(fd_file1);
	execute_cmd(command1, env);
	dup2(0, fd_file1);
	dup2(1, pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

/* In the main we create a pipe, the fd[0] and the fd[1] are linked,
   We also create a fork,
   The parent process will wait until it's child finished. */
int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("Usage : ./pipex file1 'cmd1' 'cmd2' file2\n", 2);
		return (-1);
	}
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
	}
	return (0);
}
