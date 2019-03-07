/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:15:38 by naali             #+#    #+#             */
/*   Updated: 2019/03/07 10:43:35 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WOLF3D_H
# define	WOLF3D_H

# include "includes.h"
# include "t_struct.h"

typedef struct		s_file
{
	int			fd;
	int			nbl;
	char		*line;
	char		**tbline;
}					t_file;

typedef struct		s_map
{
	t_file		f;
	int			xmax;
	int			ymax;
	int			zmax;
	t_vertex	**tab;
}					t_map;

int					file_to_tab(char *path, t_map *m);

#endif
