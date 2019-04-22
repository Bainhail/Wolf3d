/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:48:56 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:29:03 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static void	get_nb_size(int n, int *mod, int *size)
{
	while (n < -9)
	{
		n = n / 10;
		*mod = *mod * 10;
		*size = *size + 1;
	}
}

static char	*convert_nb(int n, int mod, int signe, int size)
{
	int		i;
	char	*nb;

	i = 0;
	nb = NULL;
	if ((nb = (char*)malloc(sizeof(char) * (size + signe + 1))) == NULL)
		return (0);
	if (signe == 1)
	{
		nb[i] = '-';
		i = i + 1;
	}
	while (mod > 0)
	{
		nb[i] = ((n / mod) * (-1)) + '0';
		n = n % mod;
		mod = mod / 10;
		i = i + 1;
	}
	nb[i] = '\0';
	return (nb);
}

char		*ft_itoa(int n)
{
	int		mod;
	int		signe;
	int		size;
	char	*nb;

	mod = 1;
	signe = 0;
	size = 1;
	nb = NULL;
	if (n >= 0)
		n = n * (-1);
	else
		signe = 1;
	get_nb_size(n, &mod, &size);
	nb = convert_nb(n, mod, signe, size);
	return (nb);
}
