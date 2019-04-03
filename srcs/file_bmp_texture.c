/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bmp_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 08:47:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/04/03 08:47:59 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_load_bmp(t_print *p)
{
	p->txt = loadBMP(p->renderer_3d, "textures/untitled.bmp");
	p->txt_x_west = loadBMP(p->renderer_3d, "textures/west_x.bmp");
	p->txt_x_east = loadBMP(p->renderer_3d, "textures/east_x.bmp");
	p->txt_y_south = loadBMP(p->renderer_3d, "textures/south_y.bmp");
	p->txt_y_north = loadBMP(p->renderer_3d, "textures/north_y.bmp");
}
