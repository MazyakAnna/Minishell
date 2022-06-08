/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 02:38:17 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 03:46:14 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_d_if_flag1(int *d, int *len, t_list *spec)
{
	if (spec->flag == 1)
	{
		if (spec->minus == 1)
			ft_putchar_mod('-', spec);
		while (*len > ft_putnbr_len(*d))
		{
			ft_putchar_mod('0', spec);
			*len = *len - 1;
			spec->width--;
		}
		if (spec->accuracy == 0 && spec->width != 0 && *d == 0)
			ft_putchar_mod(' ', spec);
		else
		{
			if (spec->accuracy == 0 && *d == 0)
				return ;
			ft_putnbr_mod(*d, spec);
		}
		while (spec->width > ft_putnbr_len(*d))
		{
			ft_putchar_mod(' ', spec);
			spec->width--;
		}
	}
}

void	print_d_if_flag2(int *d, int *len, t_list *spec)
{
	if (spec->flag == 2)
	{
		print_d_if_accuracy_m1_ang_b1(len, spec);
		while (*len > ft_putnbr_len(*d))
		{
			ft_putchar_mod('0', spec);
			*len = *len - 1;
			spec->width--;
		}
		print_d_if_accuracy_m1(d, spec);
		if (spec->accuracy == 0 && spec->width != 0 && *d == 0)
			ft_putchar_mod(' ', spec);
		else
		{
			if (spec->accuracy == 0 && *d == 0)
				return ;
			ft_putnbr_mod(*d, spec);
		}
	}
}

void	f_if_width_and_d_m0(int *d, t_list *spec)
{
	if (spec->width < 0)
	{
		spec->width = spec->width * -1;
		spec->flag = 1;
	}
	if (*d < 0)
	{
		*d = *d * -1;
		spec->minus = 1;
	}
}

void	print_d_if_accuracy_m1_ang_b1(int *len, t_list *spec)
{
	if (spec->accuracy < -1)
	{
		if (spec->minus == 1)
			ft_putchar_mod('-', spec);
		while (spec->width > *len)
		{
			ft_putchar_mod('0', spec);
			spec->width--;
		}
	}
	if (spec->accuracy > -1)
	{
		while (spec->width > *len)
		{
			ft_putchar_mod(' ', spec);
			spec->width--;
		}
		if (spec->minus == 1)
			ft_putchar_mod('-', spec);
	}
}

void	print_d_if_accuracy_m1(int *d, t_list *spec)
{
	if (spec->accuracy == -1)
	{
		if (spec->minus == 1)
			ft_putchar_mod('-', spec);
		while (spec->width > ft_putnbr_len(*d))
		{
			ft_putchar_mod('0', spec);
			spec->width--;
		}
	}
}
