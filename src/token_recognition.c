/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:27:50 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 16:27:55 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//creates token and fills it;
void	delimit_token(char *str, int start, int end, t_token **token)
{
	t_token	*new;
	int		len;

	if (end < start)
		return ;
	len = end - start + 1;
	new = create_token(0, 0, 0);
	if (token == NULL)
		return ;
	new->content = ft_strndup(&str[start], len);
	new->id = is_operator(new->content, 3);
	new->next = NULL;
	if (*token != NULL)
	{
		new->prev = *token;
		(*token)->next = new;
		*token = (*token)->next;
	}
	else
		*token = new;
}

int	token_recognition3(char *input, t_token **token, t_flags *f, int i)
{
	if (f->quot == 0 && is_operator(&input[i], 1) != 0)
	{
		delimit_token(input, f->start, i - 1, token);
		f->operator = 1;
		f->start = i;
		i++;
	}
	else if (f->quot == 0 && (input[i] == ' ' || input[i] == '	'))
	{
		delimit_token(input, f->start, i - 1, token);
		while (input[i] == ' ' || input[i] == '	')
			i++;
		f->start = i;
	}
	else if (f->start < i)
		i++;
	else
	{
		f->start = i;
		i++;
	}
	return (i);
}

int	token_recognition2(char *input, t_token **token, t_flags *f)
{
	int	i;

	i = f->count;
	if (f->quot == 0 && is_quot(input[i]) != 0)
	{
		f->quot = is_quot(input[i]);
		i++;
	}
	else if (f->quot != 0 && is_quot(input[i]) == f->quot)
	{
		f->quot = 0;
		i++;
	}
	else if (f->quot == 0 && input[i] == '$')
	{
		i++;
		i += expansion_length(&input[i]);
	}
	else
		i = token_recognition3(input, token, f, i);
	return (i);
}

int	token_recognition1(char *input, t_token **token, t_flags *f)
{
	int	i;

	i = f->count;
	if (f->operator != 0 && f->quot == 0
		&& is_operator(&input[f->start], i - f->start + 1) != 0)
		i++;
	else if (f->operator != 0
		&& is_operator(&input[f->start], i - f->start + 1) == 0)
	{
		delimit_token(input, f->start, i - 1, token);
		f->start = i;
		f->operator = 0;
	}
	else
	{
		f->count = i;
		i = token_recognition2(input, token, f);
	}
	return (i);
}

t_token	*token_recognition(char *input, t_data *data)
{
	t_flags	f;
	t_token	*head_token;
	t_token	*tmp_token;

	f.count = 0;
	f.start = 0;
	f.operator = 0;
	f.quot = 0;
	head_token = create_token(0, 0, 0);
	tmp_token = head_token;
	while (input[f.count] != '\0')
		f.count = token_recognition1(input, &tmp_token, &f);
	if (input[f.count] == '\0')
	{
		delimit_token(input, f.start, f.count - 1, &tmp_token);
		if (f.quot != 0)
		{
			ret_error(data, 0, SNTX_ERROR, 258);
			head_token = free_tokens(head_token);
		}
	}
	return (head_token);
}
