/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:39:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/27 15:15:44 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h> 

# define STDIN 0
# define STDOUT 1
# define STDERR 2

int		main(int argc, char **argv, char **env);
void	child(char *file1, int *fd, char *command1, char **env);
void	parent(char *file2, int *fd, char *command2, char **env);
char	*get_path_line_in_env(char **env);
void	execute_cmd(char *command, char **env);
int		here_doc(char **argv, char **env);

#endif
