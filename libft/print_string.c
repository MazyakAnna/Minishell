/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:50:00 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:32:15 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_if_width_minus(t_list *spec)
{
	spec->width = spec->width * -1;
	spec->flag = 1;
}

void	print_str_if_flag_1_2(char *str, t_list *spec, int len)
{
	if (spec->flag == 1)
	{
		ft_putstr_mod(str, spec, len);
		while (spec->width > len)
		{
			ft_putchar_mod(' ', spec);
			spec->width--;
		}
	}
	if (spec->flag == 2)
	{
		while (spec->width > len)
		{
			ft_putchar_mod('0', spec);
			spec->width--;
		}
		ft_putstr_mod(str, spec, len);
	}
	return ;
}

void	ft_printf_s(char *str, t_list *spec)
{
	int	len;

	if (spec->width < 0)
		f_if_width_minus(spec);
	if (str == NULL || str == 0)
		str = "(null)";
	len = ft_strlen(str);
	if (spec->accuracy > -1 && spec->accuracy < len)
		len = spec->accuracy;
	if (spec->flag == 1 || spec->flag == 2)
		print_str_if_flag_1_2(str, spec, len);
	else
	{
		while (spec->width > len)
		{
			ft_putchar_mod(' ', spec);
			spec->width--;
		}
		ft_putstr_mod(str, spec, len);
	}
}

void	print_p_if_flag1_1(int *len, int *len_tmp, int *len_tmp2, t_list *spec)
{
	f_if_accuracy_len(len, len_tmp, spec);
	while (*len > *len_tmp2)
	{
		ft_putchar_mod('0', spec);
		*len = *len - 1;
	}
}

void	f_if_x_0_and_accuracy_n0(unsigned long long *x, t_list *spec)
{
	if (*x == 0 && spec->accuracy != 0)
		ft_putchar_mod('0', spec);
}
