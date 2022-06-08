/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:13:59 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 17:14:07 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*freenull(char **str)
{
	if (str != NULL && *str != NULL)
		free(*str);
	return (NULL);
}

void	split_env_expand(t_command *cmd, char	*str, char **res)
{
	int	i;
	int	pointer;

	if (str == 0)
		return ;
	i = 0;
	pointer = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '	')
		{
			if (res != NULL && *res != NULL)
			{
				add_argv(cmd, *res);
				free(*res);
				*res = NULL;
			}
		}
		while (str[i] == ' ' || str[i] == '	')
			pointer = ++i;
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '	')
			i++;
		if (i != pointer)
			add_str(res, &str[pointer], i - pointer);
	}
}

int	expand_quotes(char *src, char **res, t_data *data)
{
	int	i;

	i = 0;
	if (src[i] == '\'')
		i += expand_single_quot(src, res);
	if (src[i] == '"')
		i += expand_double_quot(&src[i], res, data);
	return (i);
}

void	expand_argv(char *src, t_data *data, t_command *cmd)
{
	char	*res;
	char	*tmp_str;
	size_t	i;

	i = 0;
	res = NULL;
	while (src[i] != '\0')
	{
		i += remember_normal_chars(&src[i], &res);
		i += expand_quotes(&src[i], &res, data);
		if (src[i] == '$')
		{
			tmp_str = expand_env(&src[i], data, &i);
			if (tmp_str != NULL)
			{
				split_env_expand(cmd, tmp_str, &res);
				free(tmp_str);
			}
		}
	}
	if (res != NULL)
	{
		add_argv(cmd, res);
		res = freenull(&res);
	}
}
