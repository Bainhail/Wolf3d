/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:03:56 by naali             #+#    #+#             */
/*   Updated: 2019/05/24 15:43:57 by naali            ###   ########.fr       */
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
		w->player.flg_dir += (w->show == 1 ? 5 : 1);
	else if (move == ANTI)
		w->player.flg_dir -= (w->show == 1 ? 5 : 1);
	while (w->player.flg_dir < 0)
		w->player.flg_dir += 360;
	w->player.flg_dir = w->player.flg_dir % 360;
}

void	ft_move(int move, t_print *w)
{
	double	x;
	double	y;

	x = 0;
	y = 0;
	if (move == UP)
	{
		if (ft_correction_pos_front(x, y, w) == TRUE)
		{
			x = w->player.pos.x + cos(conv_deg_to_rad(w->player.flg_dir)) *
				((w->show == 1 ? 10 : 2) * (w->m.xcase / 50));
			y = w->player.pos.y + sin(conv_deg_to_rad(w->player.flg_dir)) *
				((w->show == 1 ? 10 : 2) * (w->m.xcase / 50));
			ft_apply_correction(w, x, y);
		}
	}
	else if (move == DOWN)
	{
		if (ft_correction_pos_back(x, y, w) == TRUE)
		{
			x = w->player.pos.x - cos(conv_deg_to_rad(w->player.flg_dir)) *
				((w->show == 1 ? 10 : 2) * (w->m.xcase / 50));
			y = w->player.pos.y - sin(conv_deg_to_rad(w->player.flg_dir)) *
				((w->show == 1 ? 10 : 2) * (w->m.xcase / 50));
			ft_apply_correction(w, x, y);
		}
	}
	else if (move == TRIGO || move == ANTI)
		ft_move_leftright(move, w);
}
