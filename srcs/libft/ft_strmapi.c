/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:35:37 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:26:07 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r;
	unsigned int	i;

	i = 0;
	r = NULL;
	if (s != NULL && f != NULL)
	{
		if ((r = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			r[i] = (*f)(i, s[i]);
			i = i + 1;
		}
		r[i] = '\0';
	}
	return (r);
}
