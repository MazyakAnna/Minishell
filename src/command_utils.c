/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:26:52 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 19:26:54 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->id = 0;
	cmd->err = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->fds[0] = STD_IN;
	cmd->fds[1] = STD_OUT;
	cmd->fds[2] = STD_ERR;
	return (cmd);
}

void	remove_command(t_command *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->next != NULL)
		cmd->next->prev = cmd->prev;
	if (cmd->prev != NULL)
		cmd->prev->next = cmd->next;
	destroy_command(cmd);
}

void	destroy_command(t_command *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	if (cmd->argv != NULL)
	{
		i = 0;
		while (cmd->argv[i] != NULL)
		{
			free(cmd->argv[i]);
			cmd->argv[i] = NULL;
			i++;
		}
		free(cmd->argv);
		cmd->argv = NULL;
	}
	free(cmd);
	cmd = NULL;
}

void	add_argv(t_command *cmd, char *str)
{
	size_t	i;
	char	**copy;

	if (cmd == NULL || cmd->argv == NULL)
		return ;
	i = 0;
	while (cmd->argv[i] != NULL)
		i++;
	copy = (char **)ft_malloc(sizeof(char *) * (i + 2));
	copy[i + 1] = NULL;
	copy[i] = ft_strdup(str);
	if (copy[i] == NULL)
	{
		free(copy);
		return ;
	}
	while (i > 0)
	{
		i--;
		copy[i] = cmd->argv[i];
	}
	free(cmd->argv);
	cmd->argv = copy;
	cmd->argc++;
}
