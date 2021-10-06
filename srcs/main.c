/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:50:03 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/06 12:07:27 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* In the main we create a pipe, the fd[0] and the fd[1] are linked,
   We also create a fork,
   The parent process will wait until it's child finished. */
int	main(int argc, char **argv, char **env)
{
	if (argc == 5)
		mandatory(argv, env);
	else if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
		heredoc_bonus(argv, env);
	else if (argc >= 6)
		multiple_pipelines_bonus(argc, argv, env);
	else if (argc <= 4)
	{
		ft_putstr("Usage :\n./pipex file1 'cmd1' 'cmd2' file2\n");
		ft_putstr("./pipex file1 'cmd1' 'cmd2' ... 'cmdN' file2\n");
		ft_putstr("./pipex here_doc limiter 'cmd1' 'cmd2' file2\n");
		return (1);
	}
	return (0);
}
