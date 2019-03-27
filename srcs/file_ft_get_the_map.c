/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ft_get_the_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:38:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/27 12:39:11 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int				ft_get_the_map(char **av, t_print *p)
{
	if (file_to_tab(av[1], &(p->m)) == -1)
	{
		printf("ERROR FILE\n");
		return (-1);
	}
	return (1);
}
