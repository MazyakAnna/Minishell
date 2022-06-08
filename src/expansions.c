/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:43:38 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/19 22:27:33 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	remember_normal_chars(char *src, char **res)
{
	int	i;
	int	pointer;

	i = 0;
	pointer = i;
	while (is_quot(src[i]) == 0 && src[i] != '\0' && src[i] != '$')
		i++;
	if (i != pointer)
		add_str(res, src, i - pointer);
	return (i);
}

int	expand_single_quot(char *src, char **res)
{
	size_t	pointer;
	size_t	i;

	i = 1;
	pointer = 1;
	while (src[i] != '\'')
		i++;
	add_str(res, &src[pointer], i - pointer);
	i++;
	return (i);
}

int	expand_double_quot(char *src, char **res, t_data *data)
{
	size_t	pointer;
	size_t	i;
	char	*tmp_str;

	i = 1;
	pointer = i;
	while (src[i] != '\"')
	{
		if (src[i] == '$')
		{
			add_str(res, &src[pointer], i - pointer);
			tmp_str = expand_env(&src[i], data, &i);
			if (tmp_str != NULL)
			{
				add_str(res, tmp_str, ft_strlen(tmp_str));
				free(tmp_str);
			}
			pointer = i;
		}
		else
			i++;
	}
	add_str(res, &src[pointer], i - pointer);
	return (i + 1);
}

char	*expand_redirect_filename(char *src, t_data *data)
{
	char	*res;
	size_t	i;

	i = 0;
	res = NULL;
	if (src == NULL || data == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		i += remember_normal_chars(&src[i], &res);
		if (src[i] == '\'')
			i += expand_single_quot(&src[i], &res);
		else if (src[i] == '"')
			i += expand_double_quot(&src[i], &res, data);
		else if (src[i] == '$')
		{
			res = try_expand_env(&src[i], data, &i, &res);
			if (res == NULL)
				return (res);
		}
	}
	return (res);
}
