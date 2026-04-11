/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:43:22 by hiipek            #+#    #+#             */
/*   Updated: 2024/12/28 18:31:14 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (*str != '\0')
	{
		counter++;
		str++;
	}
	return (counter);
}

char	*ft_gnl_strchr(const char *str, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == uc)
			return ((char *)str);
		str++;
	}
	if (uc == '\0' && *str == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_gnl_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_gnl_strlen(s1);
	s2_len = ft_gnl_strlen(s2);
	str = (char *)malloc(s1_len + s2_len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[s1_len + s2_len] = '\0';
	return (free(s1), str);
}
