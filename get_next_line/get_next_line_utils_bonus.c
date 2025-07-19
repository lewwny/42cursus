/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:38:55 by lengarci          #+#    #+#             */
/*   Updated: 2025/04/28 15:14:19 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int				size_s1;
	int				size_s2;
	char			*res;
	unsigned int	i;
	unsigned int	j;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	res = (char *) malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!res)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int		i;
	unsigned char		d;
	size_t				size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	d = (unsigned char) c;
	while (i < size + 1)
	{
		if (d == s[i])
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *src)
{
	int		size;
	int		i;
	char	*res;

	i = 0;
	size = ft_strlen(src);
	res = (char *) malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
