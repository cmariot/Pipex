/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:39:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/06 13:16:40 by cmariot          ###   ########.fr       */
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

//MAIN
int		main(int argc, char **argv, char **env);
//MAIN FORK PROCESS
int		mandatory(char **argv, char **env);
void	child(char *file1, int *fd, char *command1, char **env);
void	child_redirection(char *file1, int *pipe_fd, int stdin_saved);
int		parent(char *file2, int *fd, char *command2, char **env);
void	parent_redirection(char *file2, int *pipe_fd, int stdin_saved);
//EXECUTE COMMAND
char	*get_path_line_in_env(char **env);
int		execute_cmd(char *command, char **env);
//BONUS FUNCTIONS
int		heredoc_bonus(char **argv, char **env);
void	child_bonus(char **argv, char **env, int *pipe_fd);
int		create_heredoc(char **argv);
void	parent_bonus(char *file2, int *pipe_fd, char *command2, char **env);
void	parent_redirection_bonus(char *file2, int *pipe_fd, int stdin_saved);
int		here_doc(char **argv, char **env);
void	multiple_pipelines_bonus(int argc, char **argv, char **env);

#endif
