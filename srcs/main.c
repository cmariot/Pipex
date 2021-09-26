/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/26 13:58:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(char *file2, int *fd, char *command2, char **env)
{
	int	fd_file2;

	fd_file2 = open(file2, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_file2 == -1)
	{
		perror("Error, file2 have not been created in the parent process.\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN) == -1)
	{
		perror("parent stdin dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file2, STDOUT) == -1)
	{
		perror("parent stdout dup2");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	close(fd_file2);
	//fork ?
	execute_cmd(command2, env);
	exit(EXIT_FAILURE);
}

void	child(char *file1, int *fd, char *command1, char **env)
{
	int	fd_file1;

	fd_file1 = open(file1, O_RDONLY);
	if (fd_file1 == -1)
	{
		perror("Error, file1 couldn't be open.\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_file1, STDIN) == -1)
	{
		perror("child stdin dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT) == -1)
	{
		perror("child stdout dup2");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd_file1);
	//fork ?
	execute_cmd(command1, env);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc != 5)
		return (-1);
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		perror("Error, the fork failed.\n");
		return (-1);
	}
	if (pid == 0)
	{
		child(argv[1], fd, argv[2], env);
		return (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		parent(argv[4], fd, argv[3], env);
		return (1);
	}
}
