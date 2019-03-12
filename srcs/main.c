/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/03/12 10:44:31 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			draw_square(SDL_Renderer *r, t_map *m, int x, int y)
{
	int		ytmp;
	int		xct;
	int		yct;

	ytmp = y;
	xct = (x + m->xcase >= WINX) ? WINX : (x + m->xcase);
	yct = y + m->ycase;
	if (m->tab[(int)(y / m->ycase)][(int)(x / m->xcase)].z == 0)
		SDL_SetRenderDrawColor(r, 0, 0, 0, 100);
	else
		SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
	while (x <= xct && x < WINX)
	{
		y = ytmp;
		while (y <= yct && y < WINY)
		{
			SDL_RenderDrawPoint(r, x, y);
			y++;
		}
		x++;
	}
	printf("x = %d, y = %d\n", x, y);
	return (0);
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
	t_print		p;

	if (ac != 2)
		return (0);
	if (file_to_tab(av[1], &(p.m)) == -1)
		printf("ERROR FILE\n");
	SDL_Init(SDL_INIT_EVERYTHING);
	p.w = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN);
	p.ren = SDL_CreateRenderer(p.w, 0, SDL_RENDERER_SOFTWARE);
	init_renderer(p.ren, &(p.m));
	SDL_RenderPresent(p.ren);
	SDL_Delay(6000);
	SDL_DestroyWindow(p.w);
	SDL_Quit();
	return (0);
}
