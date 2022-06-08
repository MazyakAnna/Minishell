/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 02:42:28 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 06:07:10 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_while_width_and_more(unsigned long long *x, int *len, t_list *spec)
{
	while (spec->width > *len)
	{
		ft_putchar_mod(' ', spec);
		spec->width--;
	}
	while (*len > f_10_16(*x))
	{
		ft_putchar_mod('0', spec);
		*len = *len - 1;
	}
	ft_putstr_mod("0x", spec, 2);
	if (*x == 0)
		ft_putchar_mod('0', spec);
	ft_putnbr_mod_16(*x, spec);
}

void	f_while_fwidth_len_2(int *len, t_list *spec)
{
	while (spec->width > *len + 2)
	{
		ft_putchar_mod(' ', spec);
		spec->width--;
	}
}

void	f_if_accuracy_and_p_0(unsigned long long *x, t_list *spec)
{
	if (spec->width != 0)
	{
		if (spec->width > 2)
			ft_putchar_mod(' ', spec);
		ft_putstr_mod("0x", spec, 2);
	}
	if (*x == 0 && spec->width == 0)
		ft_putstr_mod("0x", spec, 2);
}

void	f_if_accuracy__m1(unsigned long long *x, int *len, t_list *spec)
{
	if (spec->accuracy > -1)
	{
		if ((spec->accuracy != -1 && spec->accuracy > *len) || \
							spec->accuracy == 0)
			*len = spec->accuracy;
		while (*len > ft_putnbr_len_16(*x))
		{
			ft_putchar_mod('0', spec);
			*len = *len - 1;
		}
	}
}

void	f_while_len_f(unsigned int *x, int *len, t_list *spec)
{
	while (*len > f_10_16(*x))
	{
		ft_putchar_mod('0', spec);
		*len = *len - 1;
	}
}
