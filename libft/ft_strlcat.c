/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:14:41 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:26:44 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static size_t	return_for_cat(const char *src, size_t n)
{
	size_t		src_size;

	src_size = ft_strlen(src);
	return (n + src_size);
}

size_t			ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t			i;
	size_t			dst_size;

	i = 0;
	dst_size = ft_strlen(dst);
	if (dst_size > n)
	{
		dst[dst_size] = '\0';
		return (return_for_cat(src, n));
	}
	while ((dst_size + i) < (n - 1) && src[i] != '\0')
	{
		dst[dst_size + i] = src[i];
		i = i + 1;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + ft_strlen(src));
}
