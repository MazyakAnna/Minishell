/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:21:25 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 19:21:27 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	*ft_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (ptr == NULL)
	{
		perror(strerror(ENOMEM));
		exit (ENOMEM);
	}
	return (ptr);
}

void	*safe_calloc(size_t size, size_t count)
{
	size_t	max;
	char	*res;

	max = 0 - 1;
	if (count > max / size)
	{
		perror("Trying to allocate too much memory!\n");
		exit (ENOMEM);
	}
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	res = (void *)malloc(size * count);
	if (res != NULL)
		ft_bzero(res, size * count);
	return (res);
}

//RET: 1 if <'>, 2 if <">, 0 if not a quot
int	is_quot(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}

int	is_operator(char *str, int len)
{
	if (ft_strncmp(str, ">", len) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(str, ">>", len) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<", len) == 0)
		return (REDIR_IN);
	if (ft_strncmp(str, "<<", len) == 0)
		return (HEREDOC);
	if (ft_strncmp(str, "|", len) == 0)
		return (PIPE);
	return (0);
}

int	ret_error(t_data *data, t_command *cmd, char *err_msg, int err_num)
{
	if (cmd != NULL && cmd->argv != NULL)
	{
		write(data->fds[2], cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(data->fds[2], ": ", 2);
	}
	g_status = err_num;
	write(data->fds[2], err_msg, ft_strlen(err_msg));
	return (err_num);
}
