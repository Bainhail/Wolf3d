/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:05:11 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:24:48 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int		ft_strncmp_bis(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	i = 0;
	c_s1 = (unsigned char*)s1;
	c_s2 = (unsigned char*)s2;
	while (i < n && c_s1[i] == c_s2[i] && c_s1[i] != '\0')
	{
		i = i + 1;
		if (c_s2[i] == '\0')
			return (0);
	}
	return (c_s1[i] - c_s2[i]);
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		n_size;
	char		*c_h;

	i = 0;
	c_h = (char*)haystack;
	n_size = ft_strlen(needle);
	if (n_size == 0)
		return (c_h);
	if (n_size <= ft_strlen(haystack))
	{
		while (*c_h != '\0' && n_size != 0)
		{
			if (ft_strncmp_bis(&haystack[i], needle, n_size) == 0)
				return (c_h);
			c_h = c_h + 1;
			i = i + 1;
		}
	}
	return (NULL);
}
