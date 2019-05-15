/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/05/15 17:19:55 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_init_param_game(t_print *s_win)
{
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
											WINX, WINY, SDL_WINDOW_HIDDEN)))
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

void			refresh_screen(t_print *w)
{
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 0, 0, 100);
	SDL_SetRenderDrawColor(w->renderer[MAP_3D], 0, 0, 0, 100);
	SDL_RenderClear(w->renderer[MAP_2D]);
	SDL_RenderClear(w->renderer[MAP_3D]);
	init_renderer(w->renderer[MAP_2D], &(w->m));
	refresh_player_pos(&(w->m), &(w->player));
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 255, 0, 0, 50);
	print_line(w, w->renderer[MAP_2D], w->player.s1, w->player.s2);
	print_line(w, w->renderer[MAP_2D], w->player.s1, w->player.s3);
	print_line(w, w->renderer[MAP_2D], w->player.s3, w->player.s2);
	ft_raycast(w, &(w->player), &(w->m), w->player.flg_dir);
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 0, 0, 100);
	SDL_SetRenderDrawColor(w->renderer[MAP_3D], 0, 0, 0, 100);
	SDL_RenderPresent(w->renderer[MAP_2D]);
	SDL_RenderPresent(w->renderer[MAP_3D]);
}

void			init_renderer(SDL_Renderer *r, t_map *m)
{
	int		x;
	int		y;

	y = 0;
	while (y < m->ymax)
	{
		x = 0;
		while (x < m->xmax)
		{
			draw_square(r, m, x, y);
			x++;
		}
		y++;
	}
}

int				main(int ac, char **av)
{
	t_print			s_win;

	if (ac != 2)
		return (0);
	if (ft_get_the_map(av, &s_win) == -1)
		return (-1);
	if (ft_check_if_player(s_win.m))
		return (-1);
	ft_init_param_game(&s_win);
	ft_init_window_and_renderer(&s_win);
	SDL_RenderPresent(s_win.renderer[MAP_3D]);
	ft_load_bmp(&s_win);
	init_renderer(s_win.renderer[MAP_2D], &(s_win.m));
	ft_init_player_pos(&s_win, &(s_win.player), &(s_win.m));
	ft_raycast(&s_win, &(s_win.player), &(s_win.m), EST);
	SDL_RenderPresent(s_win.renderer[MAP_2D]);
	refresh_screen(&s_win);
	ft_event_loop(&s_win);
	ft_quit("", &s_win);
	return (0);
}
