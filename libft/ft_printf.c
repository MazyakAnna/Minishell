/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:01:40 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 03:14:39 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	spec_null(t_list *spec)
{
	spec->width = 0;
	spec->accuracy = -1;
	spec->flag = 0;
	spec->minus = 0;
	spec->star = 0;
	spec->up_x = 0;
	spec->p_null = 0;
	spec->accuracy_0 = 0;
}

int	ft_printf(const char *str, ...)
{
	int			res;
	t_list		*spec;
	va_list		arg;

	res = 0;
	va_start(arg, str);
	spec = malloc(sizeof(t_list));
	if (!(spec))
		return (-1);
	spec->result = 0;
	f_parse(arg, (char *)str, spec);
	va_end(arg);
	res = spec->result;
	free(spec);
	return (res);
}

void	f_if_strar_1(int *i, t_list *spec, va_list arg)
{
	spec->star = 1;
	spec->width = (va_arg(arg, int));
	*i = *i + 1;
}

void	f_while_str_num_acy(int *i, char *str, t_list *spec)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		spec->accuracy = spec->accuracy * 10 + (str[*i] - '0');
		*i = *i + 1;
	}
}

void	f_while_str_num(int *i, char *str, t_list *spec)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		spec->width = spec->width * 10 + (str[*i] - '0');
		*i = *i + 1;
	}
}
