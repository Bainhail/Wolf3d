/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/04/22 18:04:10 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_init_param_game(t_print *s_win)
{
	s_win->player.fov = 60.0;
}

void			ft_init_window_and_renderer(t_print *s_win)
{
	s_win->window[MAP_2D] =  NULL;
	s_win->window[MAP_3D] =  NULL;
	s_win->renderer[MAP_2D] =  NULL;
	s_win->renderer[MAP_3D] =  NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!(s_win->window[MAP_2D] = SDL_CreateWindow("Window 2D",
SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->window[MAP_3D] = SDL_CreateWindow("Window 3D",
SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[MAP_3D] = SDL_CreateRenderer(s_win->window[MAP_3D],
0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
	if (!(s_win->renderer[MAP_2D] = SDL_CreateRenderer(s_win->window[MAP_2D],
0, SDL_RENDERER_SOFTWARE)))
		ft_quit("Erreur alloc window\n", s_win);
}

int				main(int ac, char **av)
{
	t_print			s_win;

	if (ac != 2)
		return (0);
	ft_init_param_game(&s_win);
	ft_get_the_map(av, &s_win);
	ft_init_window_and_renderer(&s_win);
	SDL_RenderPresent(s_win.renderer[MAP_3D]);
	ft_load_bmp(&s_win);
	init_renderer(s_win.renderer[MAP_2D], &(s_win.m));
	ft_init_player_pos(&s_win, &(s_win.player), &(s_win.m));
	ft_raycast(&s_win, &(s_win.player), &(s_win.m), EST);
	refresh_screen(&s_win);
	SDL_RenderPresent(s_win.renderer[MAP_2D]);
	ft_event_loop(&s_win);
	ft_quit("", &s_win);
	return (0);
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

int				init_renderer(SDL_Renderer *r, t_map *m)
{
	int		x;
	int		y;

	y = 0;
	while (y < m->ymax)
	{
		x = 0;
		while (x < m->xmax)
		{
			if (draw_square(r, m, x, y) == -1)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

void			print_tab(t_vertex **tab)
{
	int		x;
	int		y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 18)
		{
			printf("%.1f\t", tab[y][x].z);
			x++;
		}
		printf("\n");
		y++;
	}
}
