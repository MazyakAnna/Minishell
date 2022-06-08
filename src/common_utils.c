/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:22:02 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 19:25:21 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	skip_chars(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	return (i);
}

//size of null terminated double array
size_t	sizeof_double_arr(void **arr, size_t type_size)
{
	size_t	size;

	size = 0;
	if (arr == NULL || type_size == 0)
		return (0);
	while (*(arr + size) != NULL)
	{
		size++;
	}
	return (size);
}

/*
** takes NULL-ptr terminated double array,
** allocates sufficient memory for an enlarged copy,
** copies the array by adding the same pointers to the same elems of new one;
** adds the pointer to a new str as the last element;
** free(arr) and returns copy.
*/
char	**add_to_double_arr(void **arr, char *str)
{
	size_t	size;
	size_t	i;
	char	**copy;

	if (arr == NULL || str == NULL)
		return (NULL);
	size = 0;
	while (arr[size] != NULL)
		size++;
	size++;
	copy = (char **)ft_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		copy[i] = arr[i];
		i++;
	}
	copy[size - 1] = str;
	copy[size] = NULL;
	free(arr);
	return (copy);
}

//RETURN VALUES:
//	0 on success, >0 if an error occurs.
//	126 = utility was found, but could not be executed.
//	127 = utility could not be found.
int	ft_env(t_data *data)
{
	int	i;

	if (data == NULL || data->envp == NULL)
		return (127);
	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strchr(data->envp[i], '=') != NULL)
			ft_put2str_fd(data->envp[i], "\n", 1);
		i++;
	}
	return (0);
}

int	close_fds(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (cmd->fds[i] != i)
			close(cmd->fds[i]);
		i++;
	}
	return (1);
}
