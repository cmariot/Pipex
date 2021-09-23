/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd2_in_file2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:31:38 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/23 16:36:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	restore_redirection(int stdout_fd)
{
	dup2(stdout_fd, 1);
	close(stdout_fd);
}

void	execute_cmd2(char *cmd2, char **env)
{
	char	**cmd2_array;
	char	*cmd2_name;
	char	*pathname;

	cmd2_array = ft_split(cmd2, ' ');
	cmd2_name = cmd2_array[0];
	pathname = ft_strjoin("/usr/bin/", cmd2_name);
	if (execve(pathname, cmd2_array, env) == -1)
		perror("execve");
	free(pathname);
	ft_free_array(cmd2_array);
}

int	create_redirection(char *file2)
{
	int	stdout_bckp;
	int	fd;

	stdout_bckp = dup(1);
	fd = open(file2, O_RDWR | O_CREAT, 0600);
	if (fd == -1)
	{
		ft_putstr("Error, the file could not be create.\n");
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	return (stdout_bckp);
}

int	execute_cmd2_in_file2(char *cmd2, char*file2, char **env)
{
	pid_t	child_pid;
	int		status;
	int		stdout_fd;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (child_pid == 0)
	{
		stdout_fd = create_redirection(file2);
		execute_cmd2(cmd2, env);
		restore_redirection(stdout_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		return (0);
	}
}
