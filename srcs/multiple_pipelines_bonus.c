/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipelines_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:36:53 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/04 11:43:57 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirections(char **argv, char **env, int number_of_pipes, int argc)
{
	int fd[2];
	pid_t pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
	}
	else if (pid == 0)
	{
		ft_putstr_fd("Child process\n", 1);
		//Child
			//Save STDIN and STDOUT
			//Open file1
			//Create redirection fd_file1 STDIN
			//Create redirection fd[1] STDOUT
			//Close fd[0]
			//Execute cmd
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);	
		ft_putstr_fd("Parent process\n", 1);
		ft_putstr_fd(*env, 1);
		ft_putstr_fd(argv[2], 1);
		ft_putnbr_fd(number_of_pipes, 1);
		ft_putnbr_fd(argc, 1);
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
