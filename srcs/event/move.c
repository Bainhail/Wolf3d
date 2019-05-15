/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:03:56 by naali             #+#    #+#             */
/*   Updated: 2019/05/15 15:15:27 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ft_mouse_move(int rot, t_print *w)
{
	w->player.flg_dir += rot;
	while (w->player.flg_dir < 0)
		w->player.flg_dir += 360;
	w->player.flg_dir = w->player.flg_dir % 360;
}

void	ft_move_leftright(int move, t_print *w)
{
	if (move == TRIGO)
		w->player.flg_dir += 5;
	else if (move == ANTI)
		w->player.flg_dir -= 5;
	while (w->player.flg_dir < 0)
		w->player.flg_dir += 360;
	w->player.flg_dir = w->player.flg_dir % 360;
	refresh_screen(w);
}

void	ft_move(int move, t_print *w)
{
	double	x;
	double	y;

	if (move == UP)
	{
		x = w->player.pos.x + cos(conv_deg_to_rad(w->player.flg_dir)) *
			(20 * (w->m.xcase / 50));
		y = w->player.pos.y + sin(conv_deg_to_rad(w->player.flg_dir)) *
			(20 * (w->m.xcase / 50));
		if (ft_correction_pos(x, y, w) == TRUE)
			ft_apply_correction(w, x, y);
	}
	else if (move == DOWN)
	{
		x = w->player.pos.x - cos(conv_deg_to_rad(w->player.flg_dir)) *
			(20 * (w->m.xcase / 50));
		y = w->player.pos.y - sin(conv_deg_to_rad(w->player.flg_dir)) *
			(20 * (w->m.xcase / 50));
		if (ft_correction_pos(x, y, w) == TRUE)
			ft_apply_correction(w, x, y);
	}
	else if (move == TRIGO || move == ANTI)
		ft_move_leftright(move, w);
}
