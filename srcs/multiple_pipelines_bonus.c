/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipelines_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:36:53 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/29 14:12:19 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	multiple_pipelines_bonus(int argc, char **argv, char **env)
{
	int	stdin_bckp;
	int	stdout_bckp;

	stdin_bckp = dup(STDIN);
	stdout_bckp = dup(STDOUT);


	int	file1;
	int	file2;

	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
	{
		ft_putstr_fd("Error, no such file or directory : ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}

	int	number_of_pipes;

	number_of_pipes = argc - 4;

	int	pipe_fd[number_of_pipes][2];

	int	i;
	pid_t pid;
	int	status;

	i = 0;
	while (i < number_of_pipes)
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
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &status, 0);

		}
		i++;
	}
		
	



	file2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		ft_putstr_fd("Error, file2 could not be create.\n", 2);
		exit(EXIT_FAILURE);
	}

	ft_putstr(*env);
}
