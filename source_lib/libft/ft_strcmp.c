/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:24:38 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:27:10 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	i = 0;
	c_s1 = (unsigned char*)s1;
	c_s2 = (unsigned char*)s2;
	while (c_s1[i] == c_s2[i] && c_s1[i] != '\0')
	{
		if (c_s2[i] == '\0')
			return (c_s1[i] - c_s2[i]);
		i = i + 1;
	}
	return (c_s1[i] - c_s2[i]);
}
