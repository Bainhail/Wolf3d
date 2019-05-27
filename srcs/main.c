/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 11:13:50 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_init_param_game(t_print *s_win)
{
	s_win->show = 0;
	s_win->player.fov = 60.0;
}

void			ft_init_window_and_renderer(t_print *s_win)
{
	s_win->window[MAP_2D] = NULL;
	s_win->window[MAP_3D] = NULL;
	s_win->renderer[MAP_2D] = NULL;
	s_win->renderer[MAP_3D] = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(s_win->window[MAP_2D] = SDL_CreateWindow("Window 2D", \
											SDL_WINDOWPOS_CENTERED, \
											SDL_WINDOWPOS_CENTERED, \
											WIN2D, WIN2D, SDL_WINDOW_HIDDEN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->window[MAP_3D] = SDL_CreateWindow("Window 3D", \
											SDL_WINDOWPOS_CENTERED, \
											SDL_WINDOWPOS_CENTERED, \
											WINX, WINY, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[MAP_3D] = SDL_CreateRenderer(s_win->window[MAP_3D], \
											0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[MAP_2D] = SDL_CreateRenderer(s_win->window[MAP_2D], \
											0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
}

void    ft_draw_wall_and_ceilling(t_print *w)
{
	SDL_Rect        srcrect;
	SDL_Rect        dstrect;    srcrect.x = 0;

	srcrect.y = 0;
	srcrect.w = 54;
	srcrect.h = 42;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = WINX;
	dstrect.h = WINY / 2;
	SDL_RenderCopy(w->renderer[MAP_3D], w->texture[CEILLING], &(srcrect), &(dstrect));
}

void			refresh_screen(t_print *w)
{
	refresh_player_pos(&(w->player));
	SDL_SetRenderDrawColor(w->renderer[MAP_3D], 0, 0, 0, 100);
	SDL_RenderClear(w->renderer[MAP_3D]);
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 255, 255, 255, 100);
	SDL_RenderClear(w->renderer[MAP_2D]);
	ft_draw_wall_and_ceilling(w);
	ft_raycast(w, &(w->player), &(w->m), w->player.flg_dir);
	SDL_SetRenderDrawColor(w->renderer[MAP_3D], 0, 0, 0, 100);
	SDL_RenderPresent(w->renderer[MAP_3D]);
	if (w->show == 1)
	{
		init_renderer(w->renderer[MAP_2D], &(w->m), &(w->player));
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 255, 0, 0, 50);
		print_line(w, w->renderer[MAP_2D], w->player.s1, w->player.s2);
		print_line(w, w->renderer[MAP_2D], w->player.s1, w->player.s3);
		print_line(w, w->renderer[MAP_2D], w->player.s3, w->player.s2);
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 0, 0, 100);
		SDL_RenderPresent(w->renderer[MAP_2D]);
	}
}

void			init_renderer(SDL_Renderer *r, t_map *m, t_player *p)
{
	int		x;
	int		y;
	int		xmap;
	int		ymap;

	y = (int)(p->y / m->ycase) - 5;
	ymap = 0;
	while (ymap < 11)
	{
		x = (int)(p->x / m->xcase) - 5;
		xmap = 0;
		while (xmap < 11)
		{
			if ((y == -1 || y == m->ymax) && (x >= -1 && x <= m->xmax))
				draw_square(r, p, xmap, ymap);
			else if ((y >= -1 && y <= m->ymax) && (x == -1 || x == m->xmax))
				draw_square(r, p, xmap, ymap);
			else if ((y >= 0 && x >= 0 && y < m->ymax && x < m->xmax) && (m->tab[y][x].z > 0))
				draw_square(r, p, xmap, ymap);
			x++;
			xmap++;
		}
		y++;
		ymap++;
	}
}

int				ft_check_define()
{
	if (ERREUR != -1)
		return (-1);
	if (WINX < 500)
		return (ERREUR);
	if (WINY < 500)
		return (ERREUR);
	if(WIN2D < 300)
		return (ERREUR);
	if (PLAYER >= 0)
		return (ERREUR);
	if (NORD != 90)
		return (ERREUR);
	if (SUD != -90)
		return (ERREUR);
	if(EST != 0)
		return (ERREUR);
	if (OUEST != 180)
		return (ERREUR);
	if (WALL != 100)
		return (ERREUR);
	if (EYE != 300)
		return (ERREUR);
	if (TRUE != 1)
		return (ERREUR);
	if (FALSE != 0)
		return (ERREUR);
	return (TRUE);
}

int				main(int ac, char **av)
{
	t_print			s_win;

	if (ac != 2)
		return (0);
	if (ft_check_define() == -1)
	{
		ft_putstr("Erreur de define\n");
		return (-1);
	}
	if (ft_get_the_map(av, &s_win) == -1)
		return (-1);
	if (ft_check_if_player(s_win.m))
		return (-1);
	ft_init_param_game(&s_win);
	ft_init_window_and_renderer(&s_win);
	SDL_RenderPresent(s_win.renderer[MAP_3D]);
	ft_load_bmp(&s_win);
	init_renderer(s_win.renderer[MAP_2D], &(s_win.m), &(s_win.player));
	ft_init_player_pos(&s_win, &(s_win.player), &(s_win.m));
	ft_raycast(&s_win, &(s_win.player), &(s_win.m), EST);
	SDL_RenderPresent(s_win.renderer[MAP_2D]);
	refresh_screen(&s_win);
	ft_event_loop(&s_win);
	ft_quit("", &s_win);
	return (0);
}
