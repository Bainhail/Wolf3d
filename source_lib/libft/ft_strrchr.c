/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:00:39 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:25:34 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char			*ft_strrchr(const char *s, int c)
{
	char		*cpy;
	char		conv;

	conv = (char)c;
	cpy = (char*)s;
	while (*cpy != '\0')
		cpy = cpy + 1;
	while (cpy != s)
	{
		if (*cpy == conv)
			return (cpy);
		cpy = cpy - 1;
	}
	if (*cpy == conv)
		return (cpy);
	return (NULL);
}
