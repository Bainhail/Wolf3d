/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:49:50 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:24:01 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	i = 0;
	r = NULL;
	if (s == NULL)
		return (NULL);
	if (start > (ft_strlen(s) + 1))
		return (NULL);
	if (start + len > (ft_strlen(s) + 1))
		return (NULL);
	if ((r = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while ((start + i) < (len + start))
	{
		r[i] = s[start + i];
		i = i + 1;
	}
	r[i] = '\0';
	return (r);
}
