/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:50:14 by bmaegan           #+#    #+#             */
/*   Updated: 2021/09/26 18:50:16 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	**free_double_int(int **double_arr)
{
	size_t	i;

	if (double_arr == NULL)
		return (0);
	i = 0;
	while (double_arr[i] != NULL)
	{
		free(double_arr[i]);
		double_arr[i] = NULL;
		i++;
	}
	free(double_arr);
	double_arr = NULL;
	return (NULL);
}

//Returns:
//if OK, returns 0
//if not, problem to fd==2 and returns 1
int	check_infile(char *file)
{
	if (file == NULL || *file == '\0')
	{
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if (access(file, F_OK) != 0)
	{
		write(2, file, ft_strlen(file));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if (access(file, R_OK) != 0)
	{
		write(2, file, ft_strlen(file));
		write(2, ": Permission denied\n", 20);
		return (1);
	}
	return (0);
}

//Returns:
//if OK, returns 0
//if not, problem to fd==2 and returns 1
int	check_outfile(char *file)
{
	if (file == NULL || *file == '\0')
	{
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) != 0)
		{
			write(2, file, ft_strlen(file));
			write(2, ": Permission denied\n", 20);
			return (1);
		}
	}
	return (0);
}

void	ft_putstr_fd_nl(char *str, int fd)
{
	if (str == NULL || fd < 0)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_put2str_fd(char *str1, char *str2, int fd)
{
	if (fd < 0)
		return ;
	if (str1 != NULL)
		write(fd, str1, ft_strlen(str1));
	if (str2 != 0)
		write(fd, str2, ft_strlen(str2));
}
