/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bmp_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 08:47:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/04/03 18:10:20 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_load_bmp(t_print *s_win)
{
	s_win->texture[NONE] = loadBMP(s_win->renderer[MAP_3D], "textures/untitled.bmp");
	s_win->texture[WEST_WALL] = loadBMP(s_win->renderer[MAP_3D], "textures/west.bmp");
	s_win->texture[EAST_WALL] = loadBMP(s_win->renderer[MAP_3D], "textures/east.bmp");
	s_win->texture[SOUTH_WALL] = loadBMP(s_win->renderer[MAP_3D], "textures/south.bmp");
	s_win->texture[NORTH_WALL] = loadBMP(s_win->renderer[MAP_3D], "textures/north.bmp");
}
