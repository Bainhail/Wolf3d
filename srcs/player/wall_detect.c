/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/21 18:51:58 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


static void		ft_draw_wall(t_print *w, double dist, double x)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		hmp;// hauteur du mur percu par le joueur.

	hmp = (((double)EYE * (double)WALL) / dist) / 2.0;
	w_up = init_vtex(x, ((double)WINY / 2.0) - hmp, 0);
	w_bot = init_vtex(x, ((double)WINY / 2.0) + hmp, 0);

	SDL_SetRenderDrawColor(w->renderer_3d, 50, 50, 200, 75);
	print_line(w, w->renderer_3d, init_vtex(x, 0, 0), w_up);

	SDL_SetRenderDrawColor(w->renderer_3d, 127, 0, 127, 75);
	print_line(w, w->renderer_3d, w_up, w_bot);

	SDL_SetRenderDrawColor(w->renderer_3d, 200, 200, 200, 75);
	print_line(w, w->renderer_3d, w_bot, init_vtex(x, WINY, 0));
}

static int		ft_colision_detection(t_map *m, int tmp_x, int tmp_y)
{
	if(tmp_x < 0 || tmp_x > (WINX - 1))
		return(TRUE);
	else if (tmp_y < 0 || tmp_y > (WINY - 1))
		return(TRUE);
	else if (m->tab[(int)(tmp_y / m->ycase)][(int)(tmp_x / m->xcase)].z >= 1)
		return (TRUE);
	return (FALSE);
}

static double		dist_calc(double xa, double ya, double xb, double yb)
{
	double	dist;
	double	x;
	double	y;

	x = (xb - xa) * (xb - xa);
	y = (yb - ya) * (yb - ya);
	dist = sqrt(x + y);
	return (dist);
}

static double	recalc_ray_distance(double dist, int win_step)
{
	double		dist_cor;
	double		step;

	step = 60.0 / (double)WINX;
	if (win_step <= WINX/2)
	{
		step *= win_step;
		dist_cor = cos(conv_deg_to_rad(30.0 - step)) * dist;
		printf("alpha = %.1f\n", 30.0 - step);
	}
	else
	{
		step *= (win_step - WINX / 2);
		dist_cor = cos(conv_deg_to_rad(step)) * dist;
		printf("alpha = %.1f\n", step);
	}
	printf("dist = %.1f\n", dist);
	printf("dist = %.1f\n\n", dist_cor);
	return (dist_cor);
}

static void		 wall_detect(t_print *w, t_player *p, t_map *m, double alpha, int window_x)
{
	double		ray_distance;
   	double		ray_distance_max;
	double		x;
	double		y;
	int			colision;

	ray_distance = 0;
	colision = FALSE;
	ray_distance_max = 99999;
	while (ray_distance < ray_distance_max && colision == FALSE)
	{
		x = (cos(conv_deg_to_rad(alpha - 90)) * ray_distance) + p->pos.x;
		y = (sin(conv_deg_to_rad(alpha - 90)) * ray_distance) + p->pos.y;
		if ((colision = ft_colision_detection(m, x, y)) == FALSE)
			SDL_RenderDrawPoint(w->ren, x, y);
		else
			if ((ray_distance = dist_calc(p->pos.x, p->pos.y, x, y)) > 0)
				ft_draw_wall(w, recalc_ray_distance(ray_distance, window_x), (double)window_x);
		ray_distance++;
	}
}

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha)
{
	double	step;
	double	angle;
	double	max;
	int		window_x;

	window_x = 0;
	step = 60.0 / (double)WINX;
	angle = (double)alpha - 30;
	max = angle + 60;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 50);
	while (angle < max && window_x < WINX)
	{
		wall_detect(w, p, m, angle, window_x);
		angle += step;
		window_x++;
	}
}
