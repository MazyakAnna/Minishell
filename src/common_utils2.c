/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:21:47 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 19:21:55 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*ret;
	size_t	j;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (ft_strlen(s2) < n)
		n = ft_strlen(s2);
	ret = (char *)ft_malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	j = 0;
	while (s1[j] != '\0')
	{
		ret[j] = s1[j];
		j++;
	}
	i = 0;
	while (i < n)
	{
		ret[i + j] = s2[i];
		i++;
	}
	ret[i + j] = '\0';
	return (ret);
}

void	add_str(char **str1, char *str2, size_t size)
{
	char	*tmp_str;

	if (str1 == NULL || str2 == NULL)
		return ;
	else if (*str1 == NULL)
		*str1 = ft_strndup(str2, size);
	else
	{
		tmp_str = ft_strnjoin(*str1, str2, size);
		free(*str1);
		*str1 = tmp_str;
	}
}

long	ft_atol(char *str)
{
	long	res;
	size_t	digit;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '	')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0')
	{
		digit = *str - '0';
		if (digit > 9)
			break ;
		res = res * 10 + digit;
		str++;
	}
	res = res * sign;
	return (res);
}

int	static	is_number2(char *str, int sign)
{
	long	num;

	if (ft_isdigit(*str) == 0 && sign == 0)
		return (0);
	num = ft_atol(str);
	if (sign == -1 && num > 0)
		return (0);
	else if (sign == -1)
		return (1);
	if (num < 0)
		return (0);
	return (1);
}

//returns 1 if valid long
// or 0 if not numbers or overflow
int	is_number(char *str)
{
	int		len;
	int		sign;

	sign = 0;
	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	if (len > 20)
		return (0);
	if (*str == '-')
		sign = -1;
	else if (*str == '+')
		sign = 1;
	while (len > 1)
	{
		len--;
		if (ft_isdigit(str[len]) == 0)
			return (0);
	}
	return (is_number2(str, sign));
}
