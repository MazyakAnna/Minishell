/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:49:35 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:29:25 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_if_flag_1_2(int c, t_list *spec)
{
	if (spec->flag == 1)
	{
		ft_putchar_mod((char)c, spec);
		while (spec->width > 1)
		{
			ft_putchar_mod(' ', spec);
			spec->width--;
		}
	}
	if (spec->flag == 2)
	{
		while (spec->width > 1)
		{
			ft_putchar_mod('0', spec);
			spec->width--;
		}
		ft_putchar_mod((char)c, spec);
	}
}

void	ft_printf_c(int c, t_list *spec)
{
	if (spec->width < 0)
	{
		spec->width = spec->width * -1;
		spec->flag = 1;
	}
	if (spec->flag == 1 || spec->flag == 2)
		print_if_flag_1_2(c, spec);
	else if (spec->width > 0)
	{
		while (spec->width > 1)
		{
			ft_putchar_mod(' ', spec);
			spec->width--;
		}
		ft_putchar_mod((char)c, spec);
	}
	else
		ft_putchar_mod((char)c, spec);
}

void	len_status_x(unsigned int *x, int *len, int *len_tmp, int *len_tmp2)
{
	*len = f_10_16(*x);
	*len_tmp = *len;
	*len_tmp2 = *len;
}

void	f_connect(unsigned int *x, int *len, int *len_tmp, t_list *spec)
{
	f_if_accuracy_len(len, len_tmp, spec);
	f_while_width_len_put__(len, spec);
	f_while_len_f(x, len, spec);
}

void	f_connect_2(unsigned long long *x, int *len, int *len_tmp, t_list *spec)
{
	f_if_accuracy_len(len, len_tmp, spec);
	f_if_px_0(x, len);
	f_while_fwidth_len_2(len, spec);
}
