/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bmp_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 08:47:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/24 15:38:11 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_load_bmp(t_print *s_win)
{
	s_win->texture[NONE] = NULL;
	s_win->texture[WEST_WALL] = NULL;
	s_win->texture[EAST_WALL] = NULL;
	s_win->texture[SOUTH_WALL] = NULL;
	s_win->texture[NORTH_WALL] = NULL;
	s_win->texture[NONE] = loadbmp(s_win->renderer[MAP_3D], \
											"textures/untitled.bmp");
	s_win->texture[WEST_WALL] = loadbmp(s_win->renderer[MAP_3D], \
											"textures/west.bmp");
	s_win->texture[EAST_WALL] = loadbmp(s_win->renderer[MAP_3D], \
											"textures/east.bmp");
	s_win->texture[SOUTH_WALL] = loadbmp(s_win->renderer[MAP_3D], \
											"textures/south.bmp");
	s_win->texture[NORTH_WALL] = loadbmp(s_win->renderer[MAP_3D], \
											"textures/north.bmp");
	s_win->texture[CEILLING] = loadbmp(s_win->renderer[MAP_3D], \
											"textures/east_old.bmp");
	if (s_win->texture[NONE] == NULL \
		|| s_win->texture[WEST_WALL] == NULL \
		|| s_win->texture[EAST_WALL] == NULL \
		|| s_win->texture[SOUTH_WALL] == NULL \
		|| s_win->texture[NORTH_WALL] == NULL)
		ft_quit("error in loading bmp texture", s_win);
}
