/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 23:35:24 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/08 23:35:35 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//FROM DOCUMENTATION:
//exit [n]
//Exit the shell, returning a status of n to the shell’s parent.
//If n is omitted, the exit status is that of the last command executed.
//Any trap on EXIT is executed before the shell terminates. (???)
int	ft_exit(t_command *cmd, t_data *data, int status, int silent)
{
	if (silent == 0)
		write(2, "exit\n", 5);
	if (cmd == 0)
	{
		clear_all(data);
		exit (status);
	}
	if (cmd->argc > 1)
	{
		if (is_number(cmd->argv[1]) == 1)
		{
			if (cmd->argc == 2)
				g_status = ft_atoi(cmd->argv[1]) % 256;
			else
			{
				g_status = ret_error(data, cmd, "too many arguments\n", 1);
				return (g_status);
			}
		}
		else
			g_status = ret_error(data, cmd, "numeric argument required\n", 255);
	}
	clear_all(data);
	exit (g_status);
	return (g_status);
}
