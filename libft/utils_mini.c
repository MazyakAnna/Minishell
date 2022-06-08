/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 02:46:13 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:49:50 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_if_x_0(unsigned int *x, t_list *spec)
{
	if (*x == 0)
		ft_putchar_mod('0', spec);
}

void	f_if_p_0(unsigned long long *x, t_list *spec)
{
	if (*x == 0)
		ft_putchar_mod('0', spec);
}

void	len_status(unsigned long long *x, int *len, int *len_tmp, int *len_tmp2)
{
	*len = f_10_16(*x);
	*len_tmp = *len;
	*len_tmp2 = *len;
}

void	f_if_px_0(unsigned long long *x, int *len)
{
	if (*x == 0)
		*len = 1;
}

void	f_width_put__(t_list *spec)
{
	ft_putchar_mod(' ', spec);
	spec->width--;
}
