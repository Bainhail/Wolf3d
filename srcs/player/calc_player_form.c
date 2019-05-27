/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_player_form.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:42:55 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 11:18:50 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
** Contraction des fonctions calc s1 s2 s3
** A mettre en une ou deux fonctions max.
*/

static t_vertex		calc_s1(t_vertex *pos, double flg, t_vertex ct)
{
	t_vertex	s1;
	double		xcase;

	xcase = (double)(WIN2D / 10);
	s1.x = ct.x + (xcase / 3);
	s1.y = ct.y;
	s1.z = pos->z;
	s1 = rotate_around_new_center(&s1, &ct, flg);
	return (s1);
}

static t_vertex		calc_s2(t_vertex *pos, double flg, t_vertex ct)
{
	t_vertex	s2;
	double		xcase;

	xcase = (double)(WIN2D / 10);
	s2.x = ct.x - (xcase / 3);
	s2.y = ct.y - (xcase / 3);
	s2.z = pos->z;
	s2 = rotate_around_new_center(&s2, &ct, flg);
	return (s2);
}

static t_vertex		calc_s3(t_vertex *pos, double flg, t_vertex ct)
{
	t_vertex	s3;
	double		xcase;

	xcase = (double)(WIN2D / 10);
	s3.x = ct.x - (xcase / 3);
	s3.y = ct.y + (xcase / 3);
	s3.z = pos->z;
	s3 = rotate_around_new_center(&s3, &ct, flg);
	return (s3);
}

void				calc_player_pos(t_map *m, t_player *p, int x, int y)
{
	p->x = x;
	p->y = y;
	p->pos.x = ((double)x * (double)(m->xcase)) + ((double)(m->xcase) / 2);
	p->pos.y = ((double)y * (double)(m->ycase)) + ((double)(m->ycase) / 2);
	p->pos.z = 0;
}

void				refresh_player_pos(t_player *p)
{
	double		xcase;
	t_vertex	center;

	xcase = (double)(WIN2D / 10);
	center.x = (5.0 * xcase) + (xcase / 2);
	center.y = (5.0 * xcase) + (xcase / 2);
	center.z = 0.0;
	p->x = (int)p->pos.x;
	p->y = (int)p->pos.y;
	p->s1 = calc_s1(&(p->pos), p->flg_dir, center);
	p->s2 = calc_s2(&(p->pos), p->flg_dir, center);
	p->s3 = calc_s3(&(p->pos), p->flg_dir, center);
}
