/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:40:16 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 17:40:31 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	expansion_length(char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	if (*str == '?' || ft_isdigit(*str))
		return (1);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	len = 1;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

char	*get_env_expansion(char *str, char **env, size_t *len, t_data *data)
{
	if (str == NULL)
		return (NULL);
	*len = expansion_length(str);
	if (*str == '?')
		return (ft_itoa(g_status));
	if (ft_isdigit(*str))
	{
		if (data->argc > *str + 1 - '0')
			return (ft_strdup(data->argv[*str + 1 - '0']));
		else
			return (NULL);
	}
	if (!ft_isalpha(*str) && *str != '_')
		return (ft_strdup("$"));
	if (env != NULL)
	{
		while (*env != NULL)
		{
			if (!ft_strncmp(*env, str, *len) && (*env)[*len] == '=')
				return (ft_strdup((*env) + *len + 1));
			env++;
		}
	}
	return (NULL);
}

char	*expand_env(char *src, t_data *data, size_t *position)
{
	int		pointer;
	size_t	len;
	size_t	i;
	char	*tmp_str;

	len = 0;
	i = 1;
	pointer = i;
	tmp_str = get_env_expansion(&src[i], data->envp, &len, data);
	i += len;
	*position = *position + i;
	return (tmp_str);
}

char	*try_expand_env(char *src, t_data *data, size_t *i, char **res)
{
	char	*tmp_str;

	tmp_str = expand_env(src, data, i);
	if (tmp_str != NULL)
	{
		if (ft_strchr(tmp_str, ' ') || ft_strchr(tmp_str, '	'))
		{
			free(*res);
			free(tmp_str);
			return (NULL);
		}
		add_str(res, tmp_str, ft_strlen(tmp_str));
		free(tmp_str);
	}
	return (*res);
}
