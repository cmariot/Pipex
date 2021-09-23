/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/23 14:13:54 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_redirection(char *file2)
{
	int	stdout_bckp;
	int	fd;

	stdout_bckp = dup(1);
	fd = open(file2, O_RDWR | O_CREAT);
	if (fd == -1)
	{
		ft_putstr("Error, the file could not be open\n");
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	return (stdout_bckp);
}

void	restore_redirection(int stdout_fd)
{
	dup2(stdout_fd, 1);
	close(stdout_fd);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	main(int argc, char **argv, char **env)
{
//	char	*file1;
//	char	*cmd1;
	char	*cmd2 = argv[1];
	char	*file2 = argv[2];

	pid_t	child_pid;
	int		status;

	int		stdout_fd;
	char	**cmd2_array;
	char	*cmd2_name;
	char	*pathname;

	if (argc != 0)
	{
		//Create a child process
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (child_pid == 0)
		{
			//In the child process
			printf("Processus fils, pid = %d\n", getpid());
			//Create a redirection
			stdout_fd = create_redirection(file2);

				//Execute the command here
				cmd2_array = ft_split(cmd2, ' ');
				cmd2_name = cmd2_array[0];
				pathname = ft_strjoin("/bin/", cmd2_name);
				if (execve(pathname, cmd2_array, env) == -1)
					perror("execve");
				free(pathname);
				free_array(cmd2_array);	

			//Restore the redirection
			restore_redirection(stdout_fd);
			return (0);
		}
		else
		{
			// In the parent process
			waitpid(child_pid, &status, 0);
			printf("Processus parent, pid = %d, celui du processus fils = %d\n", getpid(), child_pid);
		}
	}
	return (0);
}
