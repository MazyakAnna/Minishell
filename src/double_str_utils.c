/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:20:09 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 16:20:19 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	sizeof_str_arr(char **str)
{
	size_t	size;

	size = 0;
	while (str[size] != NULL)
		size++;
	return (size);
}

char	**copy_double_arr_char(char **src)
{
	char	**res;
	size_t	words;
	size_t	i;

	if (src == NULL)
		return (NULL);
	words = 0;
	while (src[words] != NULL)
		words++;
	res = (char **)ft_malloc(sizeof(char *) * (words + 1));
	i = 0;
	while (i < words)
	{
		res[i] = ft_strdup(src[i]);
		i++;
	}
	res[words] = NULL;
	return (res);
}

//for those arrays that are not null terminated
void	copy_doublearr(char **src, char **copy, int size)
{
	if (src != 0 && copy != NULL)
	{
		while (size > 0)
		{
			size--;
			copy[size] = ft_strdup(src[size]);
		}
	}
	else
		ft_putstr_fd("COPY_DOUBLEARR: NULLS CAME!", 1);
}

/* 
** returns diff between the first different chars
** or zero if they are the same;
** MEANING:
** ret > 0 => s1 alphabetically greater (later)
** ret < 0 => s1 alphabetically comes before s2
*/
int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	return ((int)*s1 - (int)*s2);
}
