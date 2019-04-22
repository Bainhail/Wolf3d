/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:44:33 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:28:01 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static unsigned char	*copy_from_end(unsigned char *dst,
										unsigned char *src, size_t len)
{
	size_t			i;

	i = len - 1;
	while (i > 0)
	{
		dst[i] = src[i];
		i = i - 1;
	}
	dst[i] = src[i];
	return (dst);
}

static unsigned char	*copy_from_beg(unsigned char *dst,
										unsigned char *src, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i = i + 1;
	}
	return (dst);
}

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;

	c_dst = (unsigned char*)dst;
	c_src = (unsigned char*)src;
	if (len > 0)
	{
		if (dst < src)
			c_dst = copy_from_beg(c_dst, c_src, len);
		else
			c_dst = copy_from_end(c_dst, c_src, len);
	}
	return (dst);
}
