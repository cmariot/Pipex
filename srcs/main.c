/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/25 12:23:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char	*file1;
	char	*cmd1;
	char	*cmd2;
	char	*file2;
	int		fd[2];
	int		pid;

	file1 = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	file2 = argv[4];
	if (argc != 0)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
		{
			printf("I'm the child, my pid is %d\n", pid);
			int	stdin_bckp;
			int	file1_fd;

			stdin_bckp = dup(0);
			file1_fd = open(argv[1], O_RDONLY);
			if (file1_fd == -1)
			{
				perror("open file1");
				return (-1);
			}
			dup2(file1_fd, 0);
			close(file1_fd);
			
			char	*line;
			while (1)
			{
				line = get_next_line(file1_fd);
				ft_putstr_fd(line, file1_fd);
				if (line == NULL)
					break ;
				free(line);
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			printf("I'm the parent, my pid is %d\n", getpid());
			execute_cmd2_in_file2(cmd2, file2, env);
		}
	}
	return (0);
}
