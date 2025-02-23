/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushback_str_to_tab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:55:10 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 09:34:39 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int				tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
		i = i + 1;
	return (i);
}

int				ft_check_line_and_push(t_map *m)
{
	if (check_line(&(m->f.line), &(m->f.fd)) == -1)
		return (-1);
	if ((m->f.tbline = ft_pushback_str_to_tab(&(m->f.tbline), &(m->f.line)))\
		== NULL)
		return (-1);
	return (0);
}

void			free_useless(char ***tab, char **s1, int tmax)
{
	int		i;

	i = 0;
	if (s1 != NULL && *s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (tab != NULL && *tab != NULL)
	{
		while (i < tmax && (*tab)[i] != NULL)
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
			i = i + 1;
		}
		free(*tab);
		*tab = NULL;
	}
}

char			**ft_pushback_str_to_tab(char ***tab, char **s1)
{
	int		i;
	int		tmax;
	char	**ntab;

	i = 0;
	tmax = 0;
	if (*tab != NULL)
		tmax = tablen(*tab);
	if ((ntab = (char**)malloc(sizeof(char*) * (tmax + 2))) == NULL)
		return (NULL);
	if (*tab != NULL)
	{
		while (i < tmax)
		{
			ntab[i] = ft_strdup((*tab)[i]);
			i = i + 1;
		}
	}
	ntab[i] = ft_strdup(*s1);
	free_useless(tab, s1, tmax);
	ntab[++i] = 0;
	return (ntab);
}

int				ft_check_if_player(t_map m)
{
	int		x;
	int		y;

	y = 0;
	while (y < m.ymax)
	{
		x = 0;
		while (x < m.xmax)
		{
			if ((int)(m.tab[y][x].z) == -42)
				return (0);
			x++;
		}
		y++;
	}
	ft_putstr("manque le joueur\n");
	return (1);
}
