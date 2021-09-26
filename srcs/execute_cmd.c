/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:53:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/27 00:01:12 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	fork_command(char *command_path, char **command_array, char **env)
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
		execve(command_path, command_array, env);
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(command_path);
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
	while (path_array[i] != NULL)
	{
		path_with_slash = ft_strjoin(path_array[i], "/");
		command_path = ft_strjoin(path_with_slash, command_array[0]);
		free(path_with_slash);
		if (access(command_path, F_OK) == 0)
		{
			if (access(command_path, X_OK) == 0)
				if (fork_command(command_path, command_array, env) == 0)
					return (0);
			free(command_path);
		}
		i++;
	}
	return (-1);
}

/* Get the line which contains all the path in env,
   (type env in a terminal to see the env array)
   Split this line with the ':' delimiter,
   Split the command with the ' ' dilimiter, 
   Try the command in all the possible path. */
int	execute_cmd(char *command, char **env)
{
	char	*path_line;
	char	**path_array;
	char	**command_array;
	int		command_result;

	path_line = get_path_line_in_env(env);
	if (path_line == NULL)
		return (-1);
	path_array = ft_split(path_line, ':');
	free(path_line);
	if (path_array == NULL)
		return (-1);
	command_array = ft_split(command, ' ');
	if (command_array == NULL)
	{
		ft_free_array(path_array);
		return (-1);
	}
	command_result = try_command(path_array, command_array, env);
	ft_free_array(path_array);
	ft_free_array(command_array);
	if (command_result == -1)
	{
		ft_putstr_fd("Error, the command could not be not found.\n", 2);
		return (-1);
	}
	return (0);
}
