/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:26:41 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 19:26:43 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**free_double_str(char **double_arr)
{
	int	i;

	if (double_arr == NULL)
		return (0);
	i = 0;
	while (double_arr[i] != NULL)
	{
		free(double_arr[i]);
		double_arr[i] = NULL;
		i++;
	}
	free(double_arr);
	double_arr = NULL;
	return (NULL);
}

void	free_commands(t_data *data)
{
	t_command	*tmp;

	if (data == NULL || data->cmd == NULL)
		return ;
	while (data->cmd->next != NULL)
	{
		tmp = data->cmd->next;
		data->cmd->next = tmp->next;
		destroy_command(tmp);
	}
	destroy_command(data->cmd);
	data->cmd = NULL;
}

void	clear_all(t_data *data)
{
	data->envp = free_double_str(data->envp);
	data->envpath = free_double_str(data->envpath);
	data->token = free_tokens(data->token);
	free_commands(data);
	rl_clear_history();
}
