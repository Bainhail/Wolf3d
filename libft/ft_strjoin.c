/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:08:08 by naali             #+#    #+#             */
/*   Updated: 2018/11/18 17:23:07 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static char		*single_cpy(char *dst, char const *src)
{
	size_t	i;

	i = 0;
	if ((dst = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1))) == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i = i + 1;
	}
	dst[i] = '\0';
	return (dst);
}

static char		*dbl_cpy(char *dst, char const *src1, char const *src2)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if ((dst = (char*)malloc(sizeof(char) * (ft_strlen(src1) +
												ft_strlen(src2) + 1))) == NULL)
		return (NULL);
	while (src1[i] != '\0')
	{
		dst[i] = src1[i];
		i = i + 1;
	}
	while (src2[j] != '\0')
	{
		dst[i + j] = src2[j];
		j = j + 1;
	}
	dst[i + j] = '\0';
	return (dst);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	str = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s2 == NULL)
		str = single_cpy(str, s1);
	else if (s1 == NULL)
		str = single_cpy(str, s2);
	else
		str = dbl_cpy(str, s1, s2);
	return (str);
}
