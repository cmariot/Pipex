/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/24 10:14:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd1_on_file1(char *file1, char *cmd1)
{
	char	*input_file1;
	int		fd_file1;

	fd_file1 = open(file1, O_RDONLY);
	if (fd_file1 == -1)
		return (-1);
	while (1)
	{
		input_file1 = get_next_line(fd_file1);
	}

}

int	main(int argc, char **argv, char **env)
{
	char	*file1;
	char	*cmd1;
//	char	*cmd2;
//	char	*file2;

	file1 = argv[1];
	cmd1 = argv[2];
//	cmd2 = argv[3];
//	file2 = argv[4];
	if (argc != 0)
	{
		execute_cmd1_on_file1(file1, cmd1);	
//		execute_cmd2_in_file2(cmd2, file2, env);
	}
	return (0);
}
