/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:40:07 by naali             #+#    #+#             */
/*   Updated: 2018/11/25 17:04:00 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void		*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_dst;
	unsigned char	*c_src;
	unsigned char	conv;

	i = 0;
	c_dst = (unsigned char*)dst;
	c_src = (unsigned char*)src;
	conv = (unsigned char)c;
	while (i < n)
	{
		*c_dst = c_src[i];
		c_dst = c_dst + 1;
		if (c_src[i] == conv)
			return (&c_dst[i + 1]);
		i = i + 1;
	}
	return (NULL);
}
