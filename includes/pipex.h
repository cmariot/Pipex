/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:39:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/09/23 16:40:04 by cmariot          ###   ########.fr       */
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

int	execute_cmd2_in_file2(char *cmd2, char*file2, char **env);

#endif
