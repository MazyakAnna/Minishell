/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:35:12 by fserwyn           #+#    #+#             */
/*   Updated: 2020/12/28 23:32:43 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!(copy))
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*add;
	int		len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	add = (char *)malloc(sizeof(char) * (len + 1));
	if (!(add))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		add[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
	{
		add[i++] = s2[j++];
	}
	add[i] = '\0';
	return (add);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
		{
			return (NULL);
		}
		str++;
	}
	return (str);
}
