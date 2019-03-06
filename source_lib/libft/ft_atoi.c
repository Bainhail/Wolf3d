/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:52:21 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:29:32 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_signe(int c, int *signe)
{
	if (c == 43)
	{
		*signe = -1;
		return (1);
	}
	else if (c == 45)
	{
		*signe = 1;
		return (1);
	}
	*signe = -1;
	return (0);
}

static int	check_size(int siz, int sig)
{
	if (siz >= 20 && sig == 1)
		return (0);
	else if (siz >= 20 && sig == -1)
		return (-1);
	return (1);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		num;
	int		signe;
	int		size;

	i = 0;
	num = 0;
	signe = 0;
	size = 0;
	while (ft_isspace(str[i]) == 1)
		i = i + 1;
	if (ft_signe(str[i], &signe) == 1)
		i = i + 1;
	while (ft_isdigit(str[i]) == 1)
	{
		num = num * 10 + ((str[i] - '0') * -1);
		size = size + 1;
		i = i + 1;
	}
	if (check_size(size, signe) == -1)
		return (-1);
	if (check_size(size, signe) == 0)
		return (0);
	num = num * signe;
	return (num);
}
