/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:13:10 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/27 19:02:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// get_next_line(0) -> STDOUT
void	child_bonus(char **argv, char **env, int *pipe_fd)
{
	int		stdin_saved;
	int		stdout_saved;
	char	*line;
	char	*limiter;


	stdin_saved = dup(STDIN);	
	stdout_saved = dup(STDOUT);
	limiter = ft_strjoin(argv[2], "\n");
	while (ft_strcmp(line, limiter) != 0)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	ft_putstr(*env);
	printf("%d\n", pipe_fd[1]);
	printf("%d\n", stdin_saved);
	printf("%d\n", stdout_saved);
	free(limiter);
}

int	pipex_bonus(char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, the bonus fork failed.\n", 2);
		return (-1);
	}
	if (pid == 0)
		child_bonus(argv, env, fd);
	else
	{
		waitpid(pid, &status, 0);
		//parent(argv[4], fd, argv[3], env);
		close(fd[1]);
	}
	return (0);
}

int	here_doc(char **argv, char **env)
{
	char *here_doc;

	here_doc = argv[1];
	if (ft_strcmp(here_doc, "here_doc"))
	{
		ft_putstr_fd("Error, usage : ./pipex here_doc file1 'cmd1' 'cmd2' file2\n", 2);
		return (-1);
	}
	pipex_bonus(argv, env);
	return (0);
}
