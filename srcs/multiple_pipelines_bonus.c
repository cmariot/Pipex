/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipelines_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:36:53 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/05 11:30:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int error_number)
{
	if (error_number == 1)
	{
		ft_putstr_fd("Error, in the bonus pipe process\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (error_number == 2)
	{
		ft_putstr_fd("Error, in the bonus fork process\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (error_number == 3)
	{
		ft_putstr_fd("Error, the file1 does not exist.\n", 2);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);
}

void	child_bonus2(char *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		error(1);
	pid = fork();
	if (pid == -1)
		error(2);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		execute_cmd(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd[1]);
		dup2(fd[0], STDIN);
	}
}

void	multiple_pipelines_bonus(int argc, char **argv, char **env)
{
	int	file1;
	int	file2;
	int	i;

	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		error(3);
	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0640);
	if (file2 == -1)
	{
		ft_putstr_fd("Error, the file2 could not be create.\n", 2);
		close(file1);
		exit(EXIT_FAILURE);
	}
	dup2(file1, STDIN);
	i = 2;
	while (i < (argc - 2))
		child_bonus2(argv[i++], env);
	dup2(file2, STDOUT);
	execute_cmd(argv[argc - 2], env);
	close(file1);
	close(file2);
}
