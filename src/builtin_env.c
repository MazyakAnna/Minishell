/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 23:32:57 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/19 23:57:02 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	remove_env(char *key, t_data *data, size_t size)
{
	size_t	i;
	char	**envcopy;

	if (data == NULL || data->envp == NULL || key == NULL)
		return ;
	while ((data->envp)[size] != NULL)
		size++;
	i = 0;
	while (i < size)
	{
		if (found_key(key, data->envp[i]))
		{
			envcopy = (char **)ft_malloc(sizeof(char *) * size);
			copy_doublearr(data->envp, envcopy, i);
			copy_doublearr(data->envp + i + 1, envcopy + i, size - i - 1);
			envcopy[size - 1] = NULL;
			data->envp = free_double_str(data->envp);
			data->envp = envcopy;
			data->envsize = data->envsize - 1;
			return ;
		}
		else
			i++;
	}
}

int	ft_unset(t_command *cmd, t_data *data)
{
	size_t	size;
	size_t	i;
	int		ret;

	if (data == NULL || data->envp == NULL || cmd == NULL)
		return (1);
	size = 0;
	while ((data->envp)[size] != NULL)
		size++;
	i = 0;
	ret = 0;
	while (cmd->argv[i] != NULL)
	{
		if (bad_env(cmd->argv[i]))
			ret = ret_error(data, cmd, "not a valid identifier\n", 1);
		else if (get_env_ptr(cmd->argv[i], data->envp) != NULL)
			remove_env(cmd->argv[i], data, size);
		i++;
	}
	data->envpath = free_double_str(data->envpath);
	get_envpathes(&(data->envpath), data->envp);
	return (ret);
}

/*
** replaces str in char** envp with the same key (or does nothing);
** return value = 0 on success, 1 if nothing to replace
*/
int	replace_env(char *str, t_data *data)
{
	int		i;
	size_t	keylen;

	i = 0;
	if (data == NULL || str == NULL || data->envp == NULL)
		return (1);
	keylen = expansion_length(str);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(str, data->envp[i], keylen) == 0)
		{
			if (data->envp[i][keylen] == '=' && str[keylen] == '\0')
				return (0);
			if (data->envp[i][keylen] == '\0' || data->envp[i][keylen] == '=')
			{
				free(data->envp[i]);
				data->envp[i] = ft_strdup(str);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

/*
** makes an extended copy of envp and replaces it;
*/
void	add_new_env(t_data *data, char *str)
{
	char	**envcopy;
	size_t	i;

	if (data == NULL || str == NULL || data->envp == NULL)
		return ;
	i = 0;
	envcopy = (char **)ft_malloc(sizeof(char *) * (data->envsize + 2));
	while (i < data->envsize)
	{
		envcopy[i] = data->envp[i];
		i++;
	}
	envcopy[i++] = ft_strdup(str);
	envcopy[i] = NULL;
	free(data->envp);
	data->envp = envcopy;
	data->envsize++;
}

void	set_env(t_data *data, char *value, char *key)
{
	char	*tmp;

	if (data == NULL || data->envp == NULL || key == NULL)
		return ;
	if (value != NULL)
	{
		tmp = ft_strjoin(key, value);
		if (replace_env(tmp, data) == 1)
			add_new_env(data, tmp);
		free(tmp);
	}
	else
	{
		if (replace_env(key, data) == 1)
			add_new_env(data, key);
	}
}
