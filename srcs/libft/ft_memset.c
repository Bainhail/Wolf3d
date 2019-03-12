/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:33:12 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:36:33 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void		*ft_memset(void *s, int c, size_t len)
{
	size_t			i;
	unsigned char	c_c;
	unsigned char	*cpy;

	i = 0;
	c_c = (unsigned char)c;
	cpy = (unsigned char*)s;
	while (i < len)
	{
		cpy[i] = c_c;
		i = i + 1;
	}
	return (s);
}
