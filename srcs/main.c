/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/22 22:29:26 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	stdout_bckp;
	int	fd;

	if (argc != 0)
	{
		printf("ARGV[1] = %s\n", argv[1]);
		printf("ARGV[2] = %s\n", argv[2]);
		printf("ARGV[3] = %s\n", argv[3]);
		printf("ARGV[4] = %s\n", argv[4]);
		
		//Create a redirection
		stdout_bckp = dup(1);
		fd = open("test", O_RDWR);
		if (fd== -1)
		{
			ft_putstr("Error, the file could not be open\n");
			return (-1);
		}
		dup2(fd, 1);
		close(fd);
		
		//Execute the command here
		ft_putstr_fd("Hello World !\n", 1);
	
		//Restore the redirection
		dup2(stdout_bckp, 1);
		close(stdout_bckp);
	}
	return (0);
}
