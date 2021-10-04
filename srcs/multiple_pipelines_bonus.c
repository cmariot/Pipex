/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipelines_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:36:53 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/04 08:48:02 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Create the redirection FILE1 (SDTIN) --> FD[1] (STDOUT) */
void	child_redirection_bonus(char *file1, int *pipe_fd, int stdin_saved)
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

void	middle_redirection_bonus2(int fd_in, int fd_out, int to_close)
{
	if (dup2(fd_in, STDIN) == -1)
	{
		ft_putstr_fd("Error, in stdin middle redirect\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT) == -1)
	{
		ft_putstr_fd("Error, in stdout middle redirect\n", 2);
		exit(EXIT_FAILURE);
	}
	close(to_close);
}

/* In the child, we want file1 as STDIN and fd[1] as STDOUT
   We open the file1,
   Create redirections with dup2(), close unused FD,
   Execute command1 (input = file1, output = fd[1])
   Restore the default redirections. */
void	child_bonus2(char *file1, int *pipe_fd, char *command1, char **env)
{
	int	stdin_saved;
	int	stdout_saved;

	stdin_saved = dup(STDIN);
	stdout_saved = dup(STDOUT);
	child_redirection_bonus(file1, pipe_fd, stdin_saved);
	execute_cmd(command1, env);
	dup2(stdin_saved, 0);
	dup2(stdout_saved, 1);
	exit(EXIT_SUCCESS);
}

//Faire file1 -> fd[1], executer la commande 1
void	first_redirection(int *pipe_fd, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, the main fork failed.\n", 2);
		return ;
	}
	if (pid == 0)
	{
		printf("Redirection stdin = file1 -> stdout = fd[0][1]); exec argv[2] = %s\n", argv[2]); 
		child_bonus2(argv[1], pipe_fd, argv[2], env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("%s lu, %s execute et output envoye dans pipe_fd[0][1]\n", argv[1], argv[2]);
	}
	return ;
}

void	redirections(char **argv, char **env, int number_of_pipes, int argc)
{
	int	pipe_fd[number_of_pipes][2];

	first_redirection(pipe_fd[0], argv, env);
	
	//middle_redirection();
	int	i;
	int		status;
	pid_t	pid;

	int stdin_saved;
	int stdout_saved;

	stdin_saved = dup(STDIN);
	stdout_saved = dup(STDOUT);
	i = 0;
	while (i < number_of_pipes - 1)
	{
		pipe(pipe_fd[i]);
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Error, multiple pipes fork failed", 2);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			printf("PID = %d\n", i);	
			printf("CMD = %s\n", argv[i + 3]);
			dup2(pipe_fd[i][0], STDIN);
			dup2(pipe_fd[i + 1][1], STDOUT);
			close(pipe_fd[i + 1][1]);
			close(pipe_fd[i][0]);
			execute_cmd(argv[i + 3], env);
			ft_putstr_fd("Test\n", 1);
			dup2(stdin_saved, 0);
			dup2(stdout_saved, 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
		i++;
	}

	//final_redirection();
	int	file2;
	file2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		ft_putstr_fd("Error, file2 could not be create.\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	multiple_pipelines_bonus(int argc, char **argv, char **env)
{
	int	stdin_bckp;
	int	stdout_bckp;
	int	number_of_pipes;

	stdin_bckp = dup(STDIN);
	stdout_bckp = dup(STDOUT);
	number_of_pipes = argc - 4;
	redirections(argv, env, number_of_pipes, argc);
}
