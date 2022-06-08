/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:48:18 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/08 00:54:21 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	cmd_error_message(char *cmd, int access_flag)
{
	write(2, cmd, ft_strlen(cmd));
	if (access_flag == -1)
	{
		write(2, ": Permission denied\n", 20);
		return (126);
	}
	else
		write(2, ": command not found\n", 20);
	return (127);
}

int	cmd_with_slash(char **cmd)
{
	if (access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) == 0)
			return (0);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": Permission denied\n", 20);
		return (126);
	}
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": No such file or directory\n", 28);
	return (127);
}

int	cmd_no_slash(char **cmd, char **envpath)
{
	int		i;
	int		access_flag;
	char	*full_path;

	access_flag = 0;
	i = 0;
	while (envpath != NULL && envpath[i] != NULL)
	{
		full_path = ft_strjoin(envpath[i], cmd[0]);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0 && access(full_path, R_OK) == 0)
			{
				free(cmd[0]);
				cmd[0] = full_path;
				return (0);
			}
			access_flag = -1;
		}
		free(full_path);
		i++;
	}
	return (cmd_error_message(cmd[0], access_flag));
}

int	get_cmd_name(char **cmd, char **envpath)
{
	if (cmd[0] != NULL && ft_strchr(cmd[0], '/') != NULL)
		return (cmd_with_slash(cmd));
	else
		return (cmd_no_slash(cmd, envpath));
}
