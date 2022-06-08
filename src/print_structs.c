/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:52:25 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/10 15:52:54 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_double_arr_char(int fd, char **str, char delim, char last_char)
{
	if (str != NULL)
	{
		if (*str != NULL)
		{
			ft_putstr_fd(*str, fd);
			str++;
		}
		while (*str != NULL)
		{
			write(fd, &delim, 1);
			ft_putstr_fd(*str, fd);
			str++;
		}
		if (last_char != 0)
			write(fd, &last_char, 1);
	}
}

void	print_tokens(int fd, t_token *head)
{
	t_token	*tmp;

	write(fd, "Tokens: ", 9);
	if (head != 0)
	{
		tmp = head;
		while (tmp->next != 0)
		{
			if (tmp->content != NULL)
				ft_put2str_fd(tmp->content, " -- ", fd);
			else
				ft_putstr_fd("(null)", fd);
			tmp = tmp->next;
		}
		if (tmp->content != NULL)
			ft_putstr_fd(tmp->content, fd);
		else
			ft_putstr_fd("(null)", fd);
		write(fd, "\n", 1);
	}
}
