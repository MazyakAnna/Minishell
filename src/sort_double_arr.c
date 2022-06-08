/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_double_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:15:31 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 19:15:41 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//returns:
// -1 if strings in arr are not sorted
// 1 if the array is sorted
int	double_arr_sorted(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			return (-1);
		i++;
	}
	return (1);
}

void	cmp_and_swap(char **arr, size_t *i, size_t *j, char *mid)
{
	char	*tmp;

	while (ft_strcmp(mid, arr[*i]) > 0)
		*i = *i + 1;
	while (ft_strcmp(arr[*j], mid) > 0 && *j > 0)
		*j = *j - 1;
	if (ft_strcmp(arr[*i], arr[*j]) > 0)
	{
		tmp = arr[*i];
		arr[*i] = arr[*j];
		arr[*j] = tmp;
	}
}

void	qsort_double_arr(char **arr, size_t size)
{
	char	*mid;
	size_t	i;
	size_t	j;

	if (size < 2)
		return ;
	j = size - 1;
	i = 0;
	mid = arr[j / 2];
	while (i < j)
	{
		cmp_and_swap(arr, &i, &j, mid);
	}
	if (i > 0 && double_arr_sorted(arr, i) == -1)
		qsort_double_arr(arr, i);
	if (i < (size - 1) && double_arr_sorted(&arr[i], size - i) == -1)
		qsort_double_arr(&arr[i], size - i);
}
