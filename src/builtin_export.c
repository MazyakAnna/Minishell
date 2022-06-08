/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 23:32:57 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/08 23:33:02 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** takes 2 possible <key>[<c>[<val>]] strs an compares if the keys are equal;
** char c = delimiter in str between the key and the value
** RETURN VALUES:
** 0 if keys are the same
** >0 if key in str1 > key in str2
** <0 if key in str1 < key in str2
*/
int	cmp_keys(char *s1, char *s2, char c)
{
	while (*s1 == *s2 && *s1 != '\0' && *s1 != c)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	if (*s1 == '\0' && *s2 == c)
		return (1);
	return (0);
}

int	check_export(t_command *cmd, t_data *data)
{
	if (data == NULL || data->envp == NULL
		|| cmd == NULL || cmd->argv == NULL)
		return (1);
	if (cmd->argv[1] == NULL)
		return (0);
	return (0);
}

int	bad_env(char *str)
{
	if (!str)
		return (1);
	if (ft_isalpha(*str) == 0 && *str != '_')
		return (1);
	str++;
	while (*str != '\0' && *str != '=')
	{
		if (ft_isalnum(*str) == 0 && *str != '_')
			return (1);
		str++;
	}
	return (0);
}

//creates a copy of envp, sort it, prints out, free
void	export_show(t_data *data)
{
	char	**declared;
	size_t	i;
	size_t	len;

	if (!data || !data->envp)
		return ;
	declared = copy_double_arr_char(data->envp);
	qsort_double_arr(declared, data->envsize);
	i = 0;
	while (i < data->envsize)
	{
		len = expansion_length(declared[i]);
		ft_putstr_fd("declare -x ", 1);
		write(1, declared[i], len);
		if (declared[i][len] != '\0')
		{
			write(1, "=\"", 2);
			ft_put2str_fd(&declared[i][len + 1], "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
	free_double_str(declared);
}

int	ft_export(t_command *cmd, t_data *data)
{
	size_t	i;
	int		ret;

	if (check_export(cmd, data))
		return (1);
	if (cmd->argc < 2)
	{
		export_show(data);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->argv[i] != NULL)
	{
		if (bad_env(cmd->argv[i]))
			ret = ret_error(data, cmd, "not a valid identifier\n", 1);
		else if (replace_env(cmd->argv[i], data))
			add_new_env(data, cmd->argv[i]);
		i++;
	}
	free_double_str(data->envpath);
	get_envpathes (&(data->envpath), data->envp);
	return (ret);
}
