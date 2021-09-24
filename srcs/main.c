/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/24 13:36:34 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	restore_redirection1(int stdin_fd)
{
	dup2(stdin_fd, 0);
	close(stdin_fd);
}

int	create_redirection1(char *file1)
{
	int	stdin_bckp;
	int	fd;

	stdin_bckp = dup(0);
	fd = open(file1, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Error, the file1 can't be open.\n");
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (stdin_bckp);
}

int	execute_cmd1_on_file1(char *file1, char *cmd1)
{
	int	stdin_fd;

	//create redirection fd -> in
	stdin_fd = create_redirection1(file1);
	//execute cmd1
	ft_putstr_fd(cmd1, stdin_fd);
	//restore redirection
	restore_redirection1(stdin_fd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*file1;
	char	*cmd1;
	char	*cmd2;
	char	*file2;

	file1 = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	file2 = argv[4];
	if (argc != 0)
	{
		execute_cmd1_on_file1(file1, cmd1);	
		execute_cmd2_in_file2(cmd2, file2, env);
	}
	return (0);
}
