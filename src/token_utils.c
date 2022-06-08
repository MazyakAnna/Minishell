/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:55:55 by student           #+#    #+#             */
/*   Updated: 2021/11/04 02:56:22 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*create_token(char *content, t_token *next, t_token *prev)
{
	t_token	*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
	token->id = -1;
	token->content = content;
	token->next = next;
	token->prev = prev;
	if (next != NULL)
		next->prev = token;
	if (prev != NULL)
		prev->next = token;
	return (token);
}

void	remove_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->next != NULL)
		token->next->prev = token->prev;
	if (token->prev != NULL)
		token->prev->next = token->next;
	destroy_token(token);
}

void	destroy_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->content != 0)
	{
		free(token->content);
		token->content = 0;
	}
	free(token);
	token = 0;
}

t_token	*free_tokens(t_token *head)
{
	t_token	*tmp;

	if (head != 0)
	{
		while (head->next != 0)
		{
			tmp = head->next;
			head->next = tmp->next;
			destroy_token(tmp);
		}
		destroy_token(head);
		head = NULL;
	}
	return (NULL);
}
