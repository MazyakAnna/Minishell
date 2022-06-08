/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 02:34:23 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:45:00 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_u_if_flag2(unsigned int *u, int *len, t_list *spec)
{
	if (spec->accuracy == -1)
	{
		f_while_width_len_put_0(len, spec);
		while (*len > ft_putnbr_len(*u))
		{
			ft_putchar_mod(' ', spec);
			*len = *len - 1;
		}
		ft_putnbr_mod(*u, spec);
		return ;
	}
	while (spec->width > *len)
		f_width_put__(spec);
	f_while_len_len_put_0(u, len, spec);
	if (spec->accuracy == 0 && *u == 0 && spec->width != 0)
	{
		ft_putchar_mod(' ', spec);
		return ;
	}
	if (!(spec->accuracy == 0 && *u == 0))
		ft_putnbr_mod(*u, spec);
}

void	print_x_if_flag1(unsigned int *x, int *len_tmp, t_list *spec)
{
	if (spec->accuracy == 0 && spec->width == 0 && *x == 0)
		return ;
	if (spec->accuracy == 0 && *x == 0)
		ft_putchar_mod(' ', spec);
	else
	{
		if (*x == 0)
			ft_putchar_mod('0', spec);
		ft_putnbr_mod_16(*x, spec);
	}
	while (spec->width > *len_tmp)
		f_width_put__(spec);
}

void	print_x_if_flag2(unsigned int *x, int *len, int *len_tmp, t_list *spec)
{
	if (spec->flag == 2)
	{
		f_if_accuracy_len(len, len_tmp, spec);
		if (spec->accuracy == -1)
		{
			f_if_accuracy_m1(x, len, spec);
			return ;
		}
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
		if (*x == 0 && spec->accuracy != 0)
			ft_putchar_mod('0', spec);
		if (*x == 0 && spec->accuracy == 0 && spec->width != 0)
			ft_putchar_mod(' ', spec);
		ft_putnbr_mod_16(*x, spec);
	}
}

void	print_p_if_flag1(unsigned long long *x, int *len_tmp, t_list *spec)
{
	if (spec->accuracy == 0)
		ft_putchar_mod(' ', spec);
	else
	{
		ft_putstr_mod("0x", spec, 2);
		f_if_p_0(x, spec);
		ft_putnbr_mod_16(*x, spec);
	}
	if (*x == 0)
		*len_tmp = 1;
	while (spec->width > *len_tmp + 2)
	{
		ft_putchar_mod(' ', spec);
		spec->width--;
	}
}

void	print_p_if_flag2(unsigned long long *x, int *len, int
		*len_tmp, t_list *spec)
{
	if (spec->flag == 2)
	{
		f_if_accuracy_len(len, len_tmp, spec);
		if (spec->accuracy == -1)
		{
			while (spec->width > *len)
			{
				ft_putchar_mod('0', spec);
				spec->width--;
			}
			while (*len > f_10_16(*x))
			{
				ft_putchar_mod(' ', spec);
				len--;
			}
			ft_putstr_mod("0x", spec, 2);
			if (*x == 0)
				ft_putchar_mod('0', spec);
			ft_putnbr_mod_16(*x, spec);
			return ;
		}
		f_while_width_and_more(x, len, spec);
	}
}
