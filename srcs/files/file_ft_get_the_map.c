/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ft_get_the_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:38:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/15 15:47:28 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int				ft_get_the_map(char **av, t_print *p)
{
	int		i;

	i = 0;
	if (file_to_tab(av[1], &(p->m)) == -1)
	{
		ft_putstr("ERROR FILE\n");
		if (p->m.tab != NULL)
		{
			while (p->m.tab[i] != NULL)
			{
				free(p->m.tab[i]);
				i++;
			}
			free(p->m.tab);
		}
		return (-1);
	}
	return (1);
}
