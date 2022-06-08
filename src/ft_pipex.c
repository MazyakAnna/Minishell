/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:48:45 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/08 00:58:11 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	child_in_pipe(t_data *data, t_command *cmd, int i)
{
	int	ret;

	ret = 0;
	if (cmd != NULL && cmd->argv != 0
		&& cmd->argv[0] != 0 && !is_builtin(cmd->argv[0]))
		ret = get_cmd_name(cmd->argv, data->envpath);
	if (cmd != NULL && cmd->argv != NULL)
		set_env(data, cmd->argv[0], "_=");
	if (ret != 0)
		ft_exit (0, data, ret, 1);
	if (cmd->err != 0)
		ft_exit (cmd, data, cmd->err, 1);
	if (i > 0)
		pipe_in(data->pipes_fd[i - 1]);
	if (cmd->next != NULL)
		pipe_out(data->pipes_fd[i]);
	if (cmd->fds[0] != STD_IN)
		redir_input(cmd->fds[0]);
	if (cmd->fds[1] != STD_OUT)
		redir_output(cmd->fds[1]);
	if (is_builtin(cmd->argv[0]))
		ret = run_builtin(cmd, data);
	else
		ret = execve(cmd->argv[0], cmd->argv, data->envp);
	ft_exit (0, data, ret, 1);
}

void	run_command(t_data *data, int i, t_command *cmd)
{
	if (data == NULL)
		return ;
	if (cmd != NULL && cmd->next != NULL)
		pipe(data->pipes_fd[i]);
	data->pid[i] = fork();
	if (data->pid[i] < 0)
	{
		write(2, "fork: Resource temporarily unavailable\n", 40);
		data->rss = -1;
		g_status = 128;
	}
	if (data->pid[i] == 0)
		child_in_pipe(data, cmd, i);
	if (i > 0)
	{
		close_pipe(data->pipes_fd[i - 1]);
	}
}

void	ft_waitpids(t_data *data, int pidsnum)
{
	int	i;

	i = 0;
	while (i <= pidsnum)
	{
		waitpid(data->pid[i], &g_status, 0);
		g_status = g_status >> 8;
		i++;
	}
	free(data->pid);
	data->pipes_fd = free_double_int(data->pipes_fd);
}

//--------- FT_PIPEX ----------
int	ft_pipex(t_data *data)
{
	int			i;
	t_command	*cmd;

	if (data == NULL)
		return (127);
	init_fds_pids(data);
	i = 0;
	cmd = data->cmd;
	while (cmd != NULL && data->rss == 0)
	{
		run_command(data, i, cmd);
		cmd = cmd->next;
		i++;
	}
	i--;
	ft_waitpids(data, i);
	if (data->rss != 0)
	{
		g_status = 128;
		data->rss = 0;
	}
	return (0);
}
