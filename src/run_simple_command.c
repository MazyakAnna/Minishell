/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:45:01 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/20 05:17:07 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	child_simple(t_data *data, t_command *cmd)
{
	int	ret;

	if (data == NULL || cmd == NULL || cmd->argv == NULL)
		ft_exit(0, 0, 1, 1);
	if (cmd->err != 0)
		ft_exit (cmd, data, cmd->err, 1);
	if (cmd->fds[0] != STD_IN)
		redir_input(cmd->fds[0]);
	if (cmd->fds[1] != STD_OUT)
		redir_output(cmd->fds[1]);
	ret = execve(cmd->argv[0], cmd->argv, data->envp);
	ft_exit(0, data, ret, 1);
}

void	simple_cmd_fork(t_data *data, t_command *cmd)
{
	int	pid;
	int	ret;

	ret = get_cmd_name(cmd->argv, data->envpath);
	if (ret != 0)
	{
		g_status = ret;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(FORK_ERROR, 2);
		g_status = 1;
		return ;
	}
	if (pid == 0)
	{
		child_simple(data, cmd);
	}
	waitpid(pid, &g_status, 0);
	g_status = g_status >> 8;
}

void	simple_builtin(t_data *data, t_command *cmd)
{
	int	i;
	int	tmp_fds[3];

	i = 0;
	while (i < 3)
	{
		if (cmd->fds[i] != i)
		{
			tmp_fds[i] = dup(i);
			dup2(cmd->fds[i], i);
			close(cmd->fds[i]);
		}
		i++;
	}
	g_status = run_builtin(cmd, data);
	i = 0;
	while (i < 3)
	{
		if (cmd->fds[i] != i)
		{
			dup2(tmp_fds[i], i);
			close(tmp_fds[i]);
		}
		i++;
	}
}

void	run_simple_command(t_data *data, t_command *cmd)
{
	int	i;

	if (cmd == NULL || cmd->argv == NULL)
	{
		g_status = 1;
		return ;
	}
	i = 0;
	while (cmd->argv[i] != NULL)
		i++;
	if (i > 0)
		set_env(data, cmd->argv[i - 1], "_=");
	else
		set_env(data, "", "_=");
	if (cmd->err != 0 || cmd->argv[0] == 0)
		g_status = cmd->err;
	else if (ft_strncmp(cmd->argv[0], "", 1) == 0)
		g_status = 127;
	else if (is_builtin(cmd->argv[0]))
		simple_builtin(data, cmd);
	else
		simple_cmd_fork(data, cmd);
}
