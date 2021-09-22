/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/22 17:23:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int fd;
	int	fd2;

	if (argc == 2)
	{
		printf("ARGV[1] = %s\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd== -1)
			ft_putstr("Error, the file could not be open\n");
		fd2 = dup(fd);
		printf("FD = %d\nFD2 = %d\n", fd, fd2);
		close(fd);
		dup2(fd2, 1);
	}
	return (0);
}
