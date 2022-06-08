/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:52:06 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 05:27:19 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_mod(char c, t_list *spec)
{
	write(1, &c, 1);
	spec->result++;
}

void	ft_putstr_mod(char *s, t_list *spec, int len)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0' && len > 0)
	{
		ft_putchar_mod(s[i], spec);
		i++;
		len--;
	}
}

void	ft_putnbr_mod_16(unsigned long long n, t_list *spec)
{
	char	xx;
	int		rem;

	if (spec->up_x == 1)
		xx = 'A';
	else
		xx = 'a';
	if (n == 0)
		return ;
	rem = n % 16;
	if (rem <= 9)
	{
		ft_putnbr_mod_16(n / 16, spec);
		ft_putchar_mod((rem += '0'), spec);
	}
	else
	{
		ft_putnbr_mod_16(n / 16, spec);
		ft_putchar_mod((rem - 10 + xx), spec);
	}
}

void	ft_putnbr_mod(unsigned int n, t_list *spec)
{
	long int	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_mod('-', spec);
		num = num * -1;
	}
	if (num < 10)
	{
		ft_putchar_mod((num + 48), spec);
	}
	if (num >= 10)
	{
		ft_putnbr_mod((num / 10), spec);
		ft_putnbr_mod((num % 10), spec);
	}
}

void	print_x_if_flag1_1(int *len, int *len_tmp2, t_list *spec)
{
	while (*len > *len_tmp2)
	{
		ft_putchar_mod('0', spec);
		*len = *len - 1;
	}
}
