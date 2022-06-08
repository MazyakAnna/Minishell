/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:49:13 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/08 00:30:32 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_envp(t_data *data, char **envp)
{
	int		i;
	char	*str;
	char	*str2;

	if (data == NULL || envp == NULL)
		return ;
	data->envp = copy_double_arr_char(envp);
	data->envsize = sizeof_double_arr((void **)data->envp, sizeof(char *));
	i = ft_atoi(get_env_ptr("SHLVL", envp));
	if (i == 0)
		add_new_env(data, "SHLVL=1");
	else
	{
		i++;
		str = ft_itoa(i);
		str2 = ft_strjoin("SHLVL=", str);
		replace_env(str2, data);
		free(str);
		free(str2);
	}
}

//Zero to everything + copy & set envs;
void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	get_envpathes(&(data->envpath), envp);
	data->cmd = 0;
	data->token = 0;
	g_status = 0;
	init_envp(data, envp);
	data->num_pipes = 0;
	data->fds[0] = dup(STD_IN);
	data->fds[1] = dup(STD_OUT);
	data->fds[2] = dup(STD_ERR);
	data->pipes_fd = NULL;
	data->pid = NULL;
	data->rss = 0;
}

void	init_fds_pids(t_data *data)
{
	int	i;

	data->pipes_fd = (int **)ft_malloc(sizeof(int *) * (data->num_pipes + 1));
	data->pid = (int *)ft_malloc(sizeof(int) * (data->num_pipes + 1));
	i = 0;
	if (data->pipes_fd != NULL)
	{
		while (i < (int)data->num_pipes)
		{
			data->pipes_fd[i] = (int *)ft_malloc(sizeof(int) * 2);
			data->pipes_fd[i][0] = -1;
			data->pipes_fd[i][1] = -1;
			data->pid[i] = -1;
			i++;
		}
		data->pipes_fd[i] = NULL;
	}
}
