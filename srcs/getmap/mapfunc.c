/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 13:24:08 by naali             #+#    #+#             */
/*   Updated: 2019/04/11 11:31:22 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static t_vertex		*split_nb_to_tab2(t_map *m, char **line, int i, int *lizi)
{
	int			j;
	t_vertex	*tabnb;

	*lizi = 0;
	if ((tabnb = (t_vertex*)malloc(sizeof(t_vertex) \
					* (*lizi = tablen((char**)line)))) == NULL)
		return (NULL);
	j = 0;
	while (j < *lizi)
	{
		tabnb[j] = init_vtex((double)j, (double)i, \
								(double)ft_atoi(line[j]));
		if (m->zmax < ft_atoi(line[j]))
			m->zmax = ft_atoi(line[j]);
		j = j + 1;
	}
	if (m->xmax < j && i == 0)
		m->xmax = j;
	else if (i > 0 && m->xmax != j)
	{
		free_useless(&line, NULL, *lizi);
		exit(-1);
	}
	return (tabnb);
}

static t_vertex		**split_nb_to_tab1(char **tab, t_map *m)
{
	int			i;
	int			lizi;
	char		**line;
	t_vertex	**tabnb;

	i = 0;
	if ((tabnb = (t_vertex**)malloc(sizeof(t_vertex*) \
					* tablen((char**)tab))) == NULL)
		return (NULL);
	line = NULL;
	while (tab[i] != 0)
	{
		line = ft_strsplit(tab[i], ' ');
		tabnb[i] = split_nb_to_tab2(m, line, i, &lizi);
		free_useless(&line, NULL, lizi);
		i = i + 1;
	}
	if (m->ymax < i)
		m->ymax = i;
	free_useless(&line, NULL, lizi);
	free_useless(&tab, NULL, tablen((char**)tab));
	return (tabnb);
}

static int			check_line(char **l, int *fd)
{
	int		i;

	i = 0;
	if (l != NULL && *l != NULL)
	{
		while ((*l)[i] >= 0/* && (*l)[i] <= 127*/)
		{
			i++;
			if ((*l)[i] == '\0')
				return (0);
		}
		if ((*l) != NULL)
			free(*l);
		if ((*fd) > 0)
			close(*fd);
	}
	return (-1);
}

static void			init_image_struct(t_map *m)
{
	m->xmax = 0;
	m->ymax = 0;
	m->zmax = 0;
	m->f.nbl = 0;
	m->f.tbline = NULL;
	m->f.line = NULL;
}

int					file_to_tab(char *path, t_map *m)
{
	if (ft_strcmp(path, "/dev/zero") == 0)
		return (-1);
	init_image_struct(m);
	if ((m->f.fd = open(path, O_RDONLY)) <= 0 || m->f.fd == 0)
	{
		ft_putstr(path);
		ft_putstr(" est invalide\n");
		return (-1);
	}
	while (get_next_line(m->f.fd, &(m->f.line)) > 0)
	{
		if (check_line(&(m->f.line), &(m->f.fd)) == -1)
			return (-1);
		m->f.tbline = ft_pushback_str_to_tab(&(m->f.tbline), &(m->f.line));
		m->f.nbl++;
	}
	if (m->f.tbline == NULL)
		return (-1);
	m->tab = split_nb_to_tab1(m->f.tbline, m);

print_tab(m->tab);


	m->f.line != NULL ? free(m->f.line) : 0;
	m->f.fd > 0 ? close(m->f.fd) : 0;
	m->xcase = (double)WINX / (double)(m->xmax);
	m->ycase = (double)WINY / (double)(m->ymax);
	return (0);
}
