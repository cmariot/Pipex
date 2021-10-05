/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:53:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/10/05 12:11:51 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */
int	fork_command(char **command_path, char **command_array, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, during fork in try_command()\n", 2);
		return (-1);
	}
	else if (pid == 0)
	{
		execve(*command_path, command_array, env);
		ft_putstr_fd("Command execution error\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(*command_path);
		return (0);
	}
}

/* For all the possible path of env,
   Put a '/' and the command at the end of the path,
   Check if the command exist and if it can be execute, if ok execute it.
   If it's execute, the child process stops.
   Else try the next path.  */
int	try_command(char **path_array, char **command_array, char **env)
{
	char	*path_with_slash;
	char	*command_path;
	int		i;

	i = 0;
	while (path_array[i])
	{
		path_with_slash = ft_strjoin(path_array[i], "/");
		command_path = ft_strjoin(path_with_slash, command_array[0]);
		free(path_with_slash);
		if (access(command_path, F_OK) == 0)
			if (access(command_path, X_OK) == 0)
				if (fork_command(&command_path, command_array, env) == 0)
					return (0);
		free(command_path);
		i++;
	}
	return (-1);
}

/* In the env array, check if the line begins by "PATH=",
   if a line is found, get the line without it's 5 first characters.
   Else, error. */
char	*get_path_line_in_env(char **env)
{
	char	*path_line;
	int		i;

	i = 0;
	path_line = NULL;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			path_line = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (path_line == NULL)
	{
		ft_putstr_fd("Path line not found in env\n", 2);
		return (NULL);
	}
	return (path_line);
}

/* Get the line which contains all the path in env,
   (type env in a terminal to see the env array)
   Split this line with the ':' delimiter,
   Split the command with the ' ' dilimiter, 
   Try the command in all the possible path. */
void	execute_cmd(char *command, char **env)
{
	char	*path_line;
	char	**path_array;
	char	**command_array;

	path_line = get_path_line_in_env(env);
	if (path_line == NULL)
		return ;
	path_array = ft_split(path_line, ':');
	free(path_line);
	if (path_array == NULL)
		return ;
	command_array = ft_split(command, ' ');
	if (command_array == NULL)
	{
		ft_free_array(path_array);
		return ;
	}
	if (try_command(path_array, command_array, env) == -1)
	{
		ft_putstr_fd("Error, command not found : ", 2);
		ft_putstr_fd(command_array[0], 2);
		ft_putstr_fd("\n", 2);
	}
	ft_free_array(path_array);
	ft_free_array(command_array);
}
