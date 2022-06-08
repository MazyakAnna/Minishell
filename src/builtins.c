/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:27:10 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/20 05:31:44 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_echo(t_command *cmd)
{
	int		i;
	char	eol;

	eol = '\n';
	i = 1;
	while (cmd->argv[i] != NULL && ft_strncmp("-n", cmd->argv[i], 3) == 0)
	{
		i++;
		eol = 0;
	}
	print_double_arr_char(1, &cmd->argv[i], ' ', eol);
	return (0);
}

int	is_builtin(char *argv)
{
	if (ft_strncmp(argv, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(argv, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(argv, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(argv, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(argv, "export", 7) == 0)
		return (1);
	if (ft_strncmp(argv, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(argv, "env", 4) == 0)
		return (1);
	return (0);
}

int	run_builtin(t_command *cmd, t_data *data)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (ft_export(cmd, data));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (ft_env(data));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (ft_pwd(cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (ft_cd(cmd, data));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (ft_unset(cmd, data));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (ft_exit(cmd, data, g_status, 0));
	return (BUILTIN_NOT_EXECUTED);
}
