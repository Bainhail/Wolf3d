/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:29:34 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:25:40 by naali            ###   ########.fr       */
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
	if (n < ft_strlen(s2))
		return (-1);
	while (i < n && c_s1[i] == c_s2[i] && c_s1[i] != '\0')
	{
		i = i + 1;
		if (c_s2[i] == '\0')
			return (0);
	}
	return (c_s1[i] - c_s2[i]);
}

char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len)
{
	size_t		i;
	size_t		n_size;
	char		*c_h;

	i = 0;
	ft_strlen(haystack);
	c_h = (char*)haystack;
	n_size = ft_strlen(needle);
	if (n_size == 0)
		return (c_h);
	if (len < n_size)
		return (NULL);
	while (i < len && c_h[i] != '\0')
	{
		if (ft_strncmp_bis(&c_h[i], needle, len - i) == 0)
			return (&c_h[i]);
		i = i + 1;
	}
	return (NULL);
}
