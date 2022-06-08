/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:57:58 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/10 15:58:09 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_command	*parse_to_command(t_token **token, t_command *new, t_data *data)
{
	t_token	*tmp;

	tmp = *token;
	new->argv = (char **)ft_malloc(sizeof(char *));
	new->argv[0] = NULL;
	new->argc = 0;
	while (tmp != NULL && tmp->id != PIPE)
	{
		if (tmp->id == WORD && new->err == 0)
			expand_argv(tmp->content, data, new);
		else if (new->err == 0 && parse_redirection(new, tmp, data) != 0)
			new->err = close_fds(new);
		else
			tmp = tmp->next;
		if (tmp != NULL)
			tmp = tmp->next;
	}
	if (tmp == NULL)
		*token = NULL;
	else
		*token = tmp->next;
	return (new);
}

int	count_argc(t_token *token, t_command *new)
{
	while (token != NULL && token->id != PIPE)
	{
		if (token->id == WORD)
			new->argc++;
		token = token->next;
	}
	return (0);
}

t_command	*parse_command(t_token **token, t_data *data)
{
	t_command	*new;

	new = create_command();
	count_argc(*token, new);
	parse_to_command(token, new, data);
	return (new);
}

t_command	*parse_commands(t_token *head_token, t_data *data)
{
	t_command	*command_head;
	t_command	*tmp_cmd;
	t_token		*token;

	token = head_token;
	command_head = 0;
	data->num_pipes = 0;
	if (check_tokens(token, data) != 0)
		return (NULL);
	if (token != NULL)
		command_head = parse_command(&token, data);
	tmp_cmd = command_head;
	while (token != NULL)
	{
		data->num_pipes++;
		tmp_cmd->next = parse_command(&token, data);
		if (tmp_cmd->next != NULL)
			tmp_cmd = tmp_cmd->next;
	}
	return (command_head);
}
