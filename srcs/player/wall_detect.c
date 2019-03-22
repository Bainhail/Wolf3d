/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/22 11:59:17 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


static void		ft_draw_wall(t_print *w, double distance_ray, double x_window)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		hmp;// hauteur du mur percu par le joueur.



	hmp = (((double)EYE * (double)WALL) / distance_ray) / 2.0;
	w_up = init_vtex(x_window, ((double)WINY / 2.0) - hmp, 0);
	w_bot = init_vtex(x_window, ((double)WINY / 2.0) + hmp, 0);



	if (w->txt == NULL)
	{
		printf("LA TEXTURE ?!\n");
		exit(0);
	}
	SDL_SetRenderDrawColor(w->renderer_3d, 50, 50, 200, 75);
	print_line(w, w->renderer_3d, init_vtex(x_window, 0, 0), w_up);



	//SDL_SetRenderDrawColor(w->renderer_3d, 27, 0, 127, 75);
	//print_line(w, w->renderer_3d, w_up, w_bot);



	SDL_SetRenderDrawColor(w->renderer_3d, 200, 200, 200, 75);
	print_line(w, w->renderer_3d, w_bot, init_vtex(x_window, WINY, 0));


	 SDL_Rect	srcrect;
	 SDL_Rect	dstrect;

	srcrect.x = (int)x_window % 42; //delta_y  // ou delta x
	printf("le x =%d\n", srcrect.x);
	srcrect.y = 0;  // ok
	srcrect.w = 1; //ok
	srcrect.h = 54; //ok 

	dstrect.x = x_window;  //ok
	dstrect.h = (int)hmp * 2;  //  ok
	dstrect.y = (int)((double)WINY / 2.0) - (hmp / 2.0);  // ok
	dstrect.w = 1;// ok


	SDL_RenderCopy(w->renderer_3d, w->txt, &srcrect, &dstrect);//&dstrect);
	//SDL_RenderPresent(w->renderer_3d);
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

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha, SDL_Texture *txt)
{
	double	step;
	double	angle;
	double	max;
	int		window_x;

	(void)txt;

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
