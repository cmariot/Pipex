/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:53:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/26 13:20:43 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		perror("path not found");
		return (NULL);
	}
	return (path_line);
}

void	execute_cmd(char *command, char **env)
{
	char	*path_line;
	char	**path_array;
	char	*path_with_slash;
	char	**command_array;
	char	*command_path;

	path_line = get_path_line_in_env(env);
	if (path_line == NULL)
		return ;
	path_array = ft_split(path_line, ':');
	if (path_array == NULL)
		return ;
	free(path_line);
	command_array = ft_split(command, ' ');
	if (command_array == NULL)
		return ;
	while (*path_array++ != NULL)
	{
		path_with_slash = ft_strjoin(*path_array, "/");
		command_path = ft_strjoin(path_with_slash, command_array[0]);
		free(path_with_slash);
		execve(command_path, command_array, env);
		free(command_path);
	}
	ft_free_array(path_array);
	ft_free_array(command_array);
}
