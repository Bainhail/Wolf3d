/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/03/18 17:25:43 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		refresh_screen(t_print *w)
{
/* Refresh Render START */
	SDL_RenderClear(w->ren);
	init_renderer(w->ren, &(w->m));
	refresh_player_pos(&(w->m), &(w->pl));
	print_line(w, w->pl.s1, w->pl.s2);
	print_line(w, w->pl.s1, w->pl.s3);
	print_line(w, w->pl.s3, w->pl.s2);
	wall_detect(w, &(w->pl));
	SDL_RenderPresent(w->ren);
/* Refresh Render END */
}

int			init_renderer(SDL_Renderer *r, t_map *m)
{
	int		x;
	int		y;

	x = 0;
	while (x < m->xmax)
	{
		y = 0;
		while (y < m->ymax)
		{
			if (draw_square(r, m, (x * m->xcase), (y * m->ycase)) == -1)
				return (-1);
			y++;
		}
		x++;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_print			p;

	if (ac != 2)
		return (0);
	if (file_to_tab(av[1], &(p.m)) == -1)
	{
		printf("ERROR FILE\n");
		return (-1);
	}
	SDL_Init(SDL_INIT_EVERYTHING);
	p.w = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, \
						   SDL_WINDOWPOS_CENTERED, WINX, WINY, \
						   SDL_WINDOW_SHOWN);
	p.ren = SDL_CreateRenderer(p.w, 0, SDL_RENDERER_SOFTWARE);
	init_renderer(p.ren, &(p.m));
	get_player_pos(&p, &(p.pl), &(p.m));
	SDL_RenderPresent(p.ren);
	ft_event_loop(&p);
	SDL_DestroyRenderer(p.ren);
	SDL_DestroyWindow(p.w);
	SDL_Quit();
	return (0);
}
