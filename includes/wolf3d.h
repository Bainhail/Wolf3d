/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:15:38 by naali             #+#    #+#             */
/*   Updated: 2019/03/12 09:51:37 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WOLF3D_H
# define	WOLF3D_H

# define WINX 800
# define WINY 600

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
	float		xcase;
	float		ycase;
	t_vertex	**tab;
}					t_map;

typedef struct		s_print
{
	t_vertex		player;// sera remplacer par la structure player
	t_map			m;
	SDL_Window		*w;
	SDL_Renderer	*ren;
}					t_print;

int					file_to_tab(char *path, t_map *m);

#endif
