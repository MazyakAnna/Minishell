/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 05:48:31 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/20 05:48:41 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pwd(t_command *cmd)
{
	char	*ptr;

	if (cmd == NULL)
		write(2, "PROBLEMS\n", 10);
	ptr = NULL;
	ptr = getcwd(NULL, 256);
	if (ptr == NULL)
		return (1);
	ft_putstr_fd(ptr, 1);
	write(1, "\n", 1);
	free(ptr);
	return (0);
}

int	change_dir(t_data *data, t_command *cmd, char *new_pwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 256);
	if (chdir(new_pwd) == -1)
	{
		if (pwd != NULL)
			free(pwd);
		return (ret_error(data, cmd, "Not a directory\n", 1));
	}
	if (pwd != NULL)
		free(pwd);
	pwd = getcwd(NULL, 256);
	if (pwd != NULL)
	{
		set_env(data, pwd, "PWD=");
		free(pwd);
	}
	return (0);
}

int	ft_cd(t_command *cmd, t_data *data)
{
	char	*new_pwd;
	int		ret;

	if (cmd == NULL || cmd->argv == NULL)
		return (1);
	if (cmd->argc > 1)
		new_pwd = ft_strdup(cmd->argv[1]);
	else
		new_pwd = ft_strdup(get_env_ptr("HOME", data->envp));
	if (new_pwd == NULL)
		return (ret_error(data, cmd, "HOME not set\n", 1));
	if (check_infile(new_pwd) != 0)
	{
		free(new_pwd);
		return (1);
	}
	ret = change_dir(data, cmd, new_pwd);
	if (new_pwd != NULL)
		free(new_pwd);
	return (ret);
}
