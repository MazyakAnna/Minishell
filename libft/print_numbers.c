/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:52:40 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:37:52 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_while_width_len_put_0(int *len, t_list *spec)
{
	while (spec->width > *len)
	{
		ft_putchar_mod('0', spec);
		spec->width--;
	}
}

void	ft_printf_u(unsigned int u, t_list *spec)
{
	int	len;
	int	len_tmp;

	len = ft_putnbr_len(u);
	len_tmp = ft_putnbr_len(u);
	f_if_accuracy_len(&len, &len_tmp, spec);
	if (spec->flag == 1 || spec->flag == 2)
	{
		if (spec->flag == 1)
			print_u_if_flag1(&u, &len, &len_tmp, spec);
		if (spec->flag == 2)
			print_u_if_flag2(&u, &len, spec);
		return ;
	}
	while (spec->width > len)
		f_width_put__(spec);
	f_while_len_len_put_0(&u, &len, spec);
	if (spec->accuracy == 0 && u == 0)
	{
		if (spec->width != 0)
			ft_putchar_mod(' ', spec);
		return ;
	}
	ft_putnbr_mod(u, spec);
}

void	ft_printf_x(unsigned int x, t_list *spec)
{
	int	len;
	int	len_tmp;
	int	len_tmp2;

	len_status_x(&x, &len, &len_tmp, &len_tmp2);
	if (spec->flag == 1 || spec->flag == 2)
	{
		if (spec->flag == 1)
		{
			f_if_accuracy_len(&len, &len_tmp, spec);
			print_x_if_flag1_1(&len, &len_tmp2, spec);
			print_x_if_flag1(&x, &len_tmp, spec);
		}
		print_x_if_flag2(&x, &len, &len_tmp, spec);
		return ;
	}
	f_connect(&x, &len, &len_tmp, spec);
	if (spec->accuracy == 0 && x == 0)
	{
		if (spec->width != 0)
			ft_putchar_mod(' ', spec);
		return ;
	}
	f_if_x_0(&x, spec);
	ft_putnbr_mod_16(x, spec);
}

void	ft_printf_p(unsigned long long x, t_list *spec)
{
	int	len;
	int	len_tmp;
	int	len_tmp2;

	len_status(&x, &len, &len_tmp, &len_tmp2);
	if (spec->flag == 1 || spec->flag == 2)
	{
		if (spec->flag == 1)
		{
			print_p_if_flag1_1(&len, &len_tmp, &len_tmp2, spec);
			print_p_if_flag1(&x, &len_tmp, spec);
		}
		print_p_if_flag2(&x, &len, &len_tmp, spec);
		return ;
	}
	f_connect_2(&x, &len, &len_tmp, spec);
	if (spec->accuracy == 0 && x == 0)
	{
		f_if_accuracy_and_p_0(&x, spec);
		return ;
	}
	ft_putstr_mod("0x", spec, 2);
	f_if_accuracy__m1(&x, &len, spec);
	f_if_x_0_and_accuracy_n0(&x, spec);
	ft_putnbr_mod_16(x, spec);
}

void	ft_printf_d(int d, t_list *spec)
{
	int	len;
	int	len_tmp;

	f_if_width_and_d_m0(&d, spec);
	len = ft_putnbr_len(d);
	len_tmp = ft_putnbr_len(d);
	f_if_accuracy_len(&len, &len_tmp, spec);
	if (spec->minus == 1 && spec->width > 0)
		spec->width--;
	if (spec->flag == 1 || spec->flag == 2)
	{
		print_d_if_flag1(&d, &len, spec);
		print_d_if_flag2(&d, &len, spec);
		return ;
	}
	print_d_while_width_len(&d, &len, spec);
	if (spec->accuracy == 0 && spec->width != 0 && d == 0)
		ft_putchar_mod(' ', spec);
	if (spec->accuracy == 0 && d == 0)
		return ;
	ft_putnbr_mod(d, spec);
}
