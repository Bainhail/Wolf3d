/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:23:14 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:23:57 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static int		check_for_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static size_t	get_size_wo_space(char const *s)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (check_for_space(s[i]) == 1 && s[i] != '\0')
		i = i + 1;
	while (check_for_space(s[j]) == 1 && j > 0)
		j = j - 1;
	if (j < i)
		return (0);
	return ((j - i) + 1);
}

static char		*cpy_wo_space(char const *src, size_t n)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((dst = (char*)malloc(sizeof(char) * (n + 1))) == NULL)
		return (NULL);
	while (check_for_space(src[i]) == 1)
		i = i + 1;
	while (i + j < n + i)
	{
		dst[j] = src[i + j];
		j = j + 1;
	}
	dst[j] = '\0';
	return (dst);
}

char			*ft_strtrim(char const *s)
{
	size_t	size;
	char	*r;

	size = 0;
	r = NULL;
	if (s == NULL)
		return (NULL);
	if ((size = get_size_wo_space(s)) == 0)
	{
		if ((r = (char*)malloc(sizeof(char))) == NULL)
			return (NULL);
		r[0] = '\0';
	}
	else
		r = cpy_wo_space(s, size);
	return (r);
}
