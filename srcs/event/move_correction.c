/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_correction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:01:44 by naali             #+#    #+#             */
/*   Updated: 2019/05/24 14:54:41 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void		position_calc_front(double *x, double *y, int angle, t_print *w)
{
	*x = w->player.pos.x + cos(conv_deg_to_rad(w->player.flg_dir + angle)) *
		(20 * (w->m.xcase / 50));
	*y = w->player.pos.y + sin(conv_deg_to_rad(w->player.flg_dir + angle)) *
		(20 * (w->m.xcase / 50));
}

int				ft_correction_pos_front(double x, double y, t_print *w)
{
	position_calc_front(&x, &y, 0, w);
	if (y > 0.01 && x > 0.01 \
		&& (int)(y / w->m.ycase) < w->m.ymax \
		&& (int)(x / w->m.xcase) < w->m.xmax \
		&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
	{
		position_calc_front(&x, &y, 30, w);
		if (y > 0.01 && x > 0.01 \
			&& (int)(y / w->m.ycase) < w->m.ymax \
			&& (int)(x / w->m.xcase) < w->m.xmax \
			&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
		{
			position_calc_front(&x, &y, -30, w);
			if (y > 0.01 && x > 0.01 \
				&& (int)(y / w->m.ycase) < w->m.ymax \
				&& (int)(x / w->m.xcase) < w->m.xmax \
				&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
				return (TRUE);
		}
	}
	return (FALSE);
}

static void		position_calc_back(double *x, double *y, int angle, t_print *w)
{
	*x = w->player.pos.x - cos(conv_deg_to_rad(w->player.flg_dir + angle)) *
		(20 * (w->m.xcase / 50));
	*y = w->player.pos.y - sin(conv_deg_to_rad(w->player.flg_dir + angle)) *
		(20 * (w->m.xcase / 50));
}

int				ft_correction_pos_back(double x, double y, t_print *w)
{
	position_calc_back(&x, &y, 0, w);
	if (y > 0.01 && x > 0.01 \
		&& (int)(y / w->m.ycase) < w->m.ymax \
		&& (int)(x / w->m.xcase) < w->m.xmax \
		&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
	{
		position_calc_back(&x, &y, 30, w);
		if (y > 0.01 && x > 0.01 \
			&& (int)(y / w->m.ycase) < w->m.ymax \
			&& (int)(x / w->m.xcase) < w->m.xmax \
			&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
		{
			position_calc_back(&x, &y, -30, w);
			if (y > 0.01 && x > 0.01 \
				&& (int)(y / w->m.ycase) < w->m.ymax \
				&& (int)(x / w->m.xcase) < w->m.xmax \
				&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
				return (TRUE);
		}
	}
	return (FALSE);
}

/* int		ft_correction_pos(double x, double y, t_print *w) */
/* { */
/* 	if (y > 0.01 && x > 0.01 \ */
/* 		&& (int)(y / w->m.ycase) < w->m.ymax \ */
/* 		&& (int)(x / w->m.xcase) < w->m.xmax \ */
/* 		&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0) */
/* 		return (TRUE); */
/* 	return (FALSE); */
/* } */

void	ft_apply_correction(t_print *w, double x, double y)
{
	w->player.pos.x = x;
	w->player.pos.y = y;
}
