/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 03:30:24 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:58:01 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_while_len_len_put_0(unsigned int *u, int *len, t_list *spec)
{
	while (*len > ft_putnbr_len(*u))
	{
		ft_putchar_mod('0', spec);
		*len = *len - 1;
	}
}

void	f_if_accuracy_m1(unsigned int *x, int *len, t_list *spec)
{
	while (spec->width > *len)
	{
		ft_putchar_mod('0', spec);
		spec->width--;
	}
	while (*len > f_10_16(*x))
	{
		ft_putchar_mod(' ', spec);
		*len = *len - 1;
	}
	if (*x == 0)
		ft_putchar_mod('0', spec);
	ft_putnbr_mod_16(*x, spec);
}

void	f_while_width_len_put__(int *len, t_list *spec)
{
	while (spec->width > *len)
	{
		ft_putchar_mod(' ', spec);
		spec->width--;
	}
}

void	print_d_while_width_len(int *d, int *len, t_list *spec)
{
	while (spec->width > *len)
	{
		ft_putchar_mod(' ', spec);
		spec->width--;
	}
	if (spec->minus == 1)
		ft_putchar_mod('-', spec);
	while (*len > ft_putnbr_len(*d))
	{
		ft_putchar_mod('0', spec);
		*len = *len - 1;
	}
}

void	print_u_if_flag1(unsigned int *u, int *len, int *len_tmp, t_list *spec)
{
	f_while_len_len_put_0(u, len, spec);
	if (spec->accuracy == 0 && spec->width == 0 && *u == 0)
		return ;
	if (spec->accuracy == 0 && *u == 0)
		ft_putchar_mod(' ', spec);
	else
		ft_putnbr_mod(*u, spec);
	while (spec->width > *len_tmp)
		f_width_put__(spec);
}
