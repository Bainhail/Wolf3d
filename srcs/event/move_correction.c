/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_correction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:01:44 by naali             #+#    #+#             */
/*   Updated: 2019/05/13 16:03:03 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		ft_correction_pos(double x, double y, t_print *w)
{
	if (y > 0.01 && x > 0.01 \
		&& (int)(y / w->m.ycase) < w->m.ymax \
		&& (int)(x / w->m.xcase) < w->m.xmax \
		&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
		return (TRUE);
	return (FALSE);
}

void	ft_apply_correction(t_print *w, double x, double y)
{
	w->player.pos.x = x;
	w->player.pos.y = y;
	refresh_screen(w);
}
