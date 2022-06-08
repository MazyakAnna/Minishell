/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:47:59 by bmaegan           #+#    #+#             */
/*   Updated: 2021/09/26 18:48:03 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** ------------------------------------------------------------
** checks if the *str before '=' char and the key are the same
**
** returns the length of the key;
** returns 0 if the str's key and the "char *key" are different
**
** (!) note: is '=' as a member of key protected??
** -------------------------------------------------------------
*/
int	found_key(char *key, char *str)
{
	size_t	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (key[i] == str[i])
			i++;
		else
			return (0);
	}
	if (str[i] == '=')
		i++;
	else
		return (0);
	return ((int)i);
}

/*
** ------------------------------------------------------------
** RETURNS:
**  sets the value (char *) of the env that
**  correspondes to the key into (**res) (or empty str if no key found).
** returns the size of res on success, 0 on failure
** ------------------------------------------------------------
*/
size_t	get_env(char *key, char **env, char **res)
{
	size_t	i;
	size_t	size;
	int		n;

	i = 0;
	while (env[i])
	{
		n = found_key(key, env[i]);
		if (n != 0)
		{
			size = ft_strlen(env[i]) - n + 1;
			*res = (char *)ft_malloc(sizeof(char) * size);
			ft_strlcpy(*res, &env[i][n], size);
			return (size);
		}
		i++;
	}
	*res = (char *)ft_malloc(sizeof(char));
	*res[0] = '\0';
	return (0);
}

/*
** ------------------------------------------------------------
** takes $PATH from "env", splits it by ':'
** 		and writes all the pathes into "envpath"
** ------------------------------------------------------------
*/
void	get_envpathes(char ***envpath, char **envp)
{
	int		i;
	char	*full_path;

	get_env("PATH", envp, &full_path);
	*envpath = ft_split(full_path, ':');
	free(full_path);
	i = 0;
	while ((*envpath)[i])
	{
		full_path = ft_strjoin((*envpath)[i], "/");
		free((*envpath)[i]);
		(*envpath)[i] = full_path;
		full_path = 0;
		i++;
	}
}

/*
** ------------------------------------------------------------
** RETURNS:
**    ptr to the beginning of value corresponding to a key in env
** ------------------------------------------------------------
*/
char	*get_env_ptr(char *key, char **env)
{
	size_t	i;
	int		size;

	i = 0;
	if (!env || !key)
		return (NULL);
	while (env[i])
	{
		size = found_key(key, env[i]);
		if (size != 0)
			return (&env[i][size]);
		i++;
	}
	return (NULL);
}
