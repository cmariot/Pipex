/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipelines_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:36:53 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/04 16:50:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	multiple_pipelines_bonus(int argc, char **argv, char **env)
{
	int 	fd[argc - 4][2];
	pid_t	pid;
	int		status;
	int		stdin_saved;
	int		stdout_saved;
	int 	fd_file1;

	//first redirection
	pipe(fd[0]);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ft_putstr_fd("Child process\n", 1);
		stdin_saved = dup(STDIN);
		stdout_saved = dup(STDOUT);
		fd_file1 = open(argv[1], O_RDONLY);
		if (fd_file1 == -1)
		{
			ft_putstr_fd("Error, the file1 could not be open\n", 2);
			exit(EXIT_FAILURE);
		}		
		dup2(fd_file1, STDIN);
		dup2(fd[0][1], STDOUT);
		execute_cmd(argv[2], env);
		close(fd[0][0]);
		close(fd_file1);
		dup2(stdin_saved, 0);
		dup2(stdout_saved, 1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);	
		ft_putstr_fd("Parent process\n", 1);
	}

	//middle redirections	
	pipe(fd[1]);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ft_putstr_fd("Child processs num 2\n", 1);
		stdin_saved = dup(STDIN);
		stdout_saved = dup(STDOUT);
		//redirection stdin devient fd[0][1]
		dup2(fd[0][0], STDIN);
		close(fd[0][1]);
		//redirection stdout devient fd[1][0]
		dup2(fd[1][1], STDOUT);
		execute_cmd(argv[3], env);
		close(fd[0][1]);
		dup2(stdin_saved, 0);
		dup2(stdout_saved, 1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_putstr_fd("Parent processs num 2\n", 1);
	}
	
}
