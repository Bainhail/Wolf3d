/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:09:50 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:25:45 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

char		*ft_strnew(size_t size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if ((tmp = (char*)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (i < size)
	{
		tmp[i] = '\0';
		i = i + 1;
	}
	tmp[i] = '\0';
	return (tmp);
}
