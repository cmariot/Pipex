/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipelines_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:36:53 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/30 18:52:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		child(argv[1], pipe_fd, argv[2], env);
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
		//	execute_cmd(argv[i + 3], env);
			ft_putstr_fd("Test\n", 1);
			dup2(stdin_saved, 0);
			dup2(stdout_saved, 1);
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
