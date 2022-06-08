/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 11:53:37 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 03:07:41 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_len(unsigned long long n)
{
	unsigned long long	num;
	int					i;

	i = 0;
	num = n;
	if (n > 4294967295)
		num = (unsigned int)n;
	if (num == 0)
		i = 0;
	if (num < 10)
		i++;
	if (num >= 10)
	{
		while (num >= 10)
		{
			num = num / 10;
			i++;
		}
		i++;
	}
	return (i);
}

int	ft_putnbr_len_p(unsigned long long n)
{
	unsigned long long	num;
	int					i;

	i = 0;
	num = n;
	if (num == 0)
		i = 0;
	if (num < 10)
		i++;
	if (num >= 10)
	{
		while (num >= 10)
		{
			num = num / 10;
			i++;
		}
		i++;
	}
	return (i);
}

int	ft_putnbr_len_16(unsigned long long n)
{
	unsigned long long	num;
	int					i;

	i = 0;
	num = n;
	if (n > 4294967295)
		num = (unsigned int)n;
	if (num == 0)
		i = 0;
	if (num < 16)
		i++;
	if (num >= 16)
	{
		while (num >= 16)
		{
			num = num / 16;
			i++;
		}
		i++;
	}
	return (i);
}

int	f_10_16(unsigned long long x)
{
	int	len;

	len = 0;
	if (x < 4294967296)
	{
		if (ft_putnbr_len(x) > ft_putnbr_len_16(x))
			len = ft_putnbr_len(x) - (ft_putnbr_len(x) - ft_putnbr_len_16(x));
		else
			len = ft_putnbr_len(x);
	}
	if (x >= 4294967296)
	{
		if (ft_putnbr_len_p(x) > ft_putnbr_len_16(x))
			len = ft_putnbr_len_p(x) - 1;
		else
			len = ft_putnbr_len_p(x);
	}
	return (len);
}

void	f_if_accuracy_len(int *len, int *len_tmp, t_list *spec)
{
	if (spec->accuracy != -1 && spec->accuracy > *len)
	{
		*len = spec->accuracy;
		*len_tmp = spec->accuracy;
	}
}
