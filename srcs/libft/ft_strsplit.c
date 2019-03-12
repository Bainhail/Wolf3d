/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:49:26 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:25:02 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static int		count_word(char const *str, char c)
{
	int	i;
	int flg;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		flg = 0;
		while (str[i] != c && str[i] != '\0')
		{
			i = i + 1;
			flg = 1;
		}
		if (flg == 1)
			word = word + 1;
		if (str[i] != '\0')
			i = i + 1;
	}
	return (word + 1);
}

static int		count_letter(char const *str, int i, char c)
{
	int	n;

	n = 0;
	while (str[i + n] != c && str[i + n] != '\0')
		n = n + 1;
	return (n);
}

static char		*ft_strlcpy_a(char const *src, int *i, char c)
{
	int		ct;
	int		end;
	char	*dest;

	ct = 0;
	end = *i + count_letter(src, *i, c);
	if ((dest = (char *)malloc(sizeof(char) * (end - *i + 1))) == NULL)
		return (0);
	while (*i < end)
	{
		dest[ct] = src[*i];
		ct = ct + 1;
		*i = *i + 1;
	}
	dest[ct] = '\0';
	return (dest);
}

char			**ft_strsplit(char const *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = NULL;
	if (str == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(char*) * count_word(str, c))) == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			tab[j] = ft_strlcpy_a(str, &i, c);
			j = j + 1;
		}
		if (str[i] != '\0')
			i = i + 1;
	}
	tab[j] = 0;
	return (tab);
}
