/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/03/27 12:46:01 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			refresh_screen(t_print *w)
{
	SDL_RenderClear(w->ren);
	SDL_RenderClear(w->renderer_3d);
	init_renderer(w->ren, &(w->m));
	refresh_player_pos(&(w->m), &(w->pl));
	print_line(w, w->ren, w->pl.s1, w->pl.s2);
	print_line(w, w->ren, w->pl.s1, w->pl.s3);
	print_line(w, w->ren, w->pl.s3, w->pl.s2);
	ft_raycast(w, &(w->pl), &(w->m), w->pl.flg_dir, w->txt);
	SDL_SetRenderDrawColor(w->ren, 0, 0, 0, 100);
	SDL_SetRenderDrawColor(w->renderer_3d, 0, 0, 0, 100);
	SDL_RenderPresent(w->ren);
	SDL_RenderPresent(w->renderer_3d);
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

void			ft_load_bmp(t_print *p)
{
	p->txt = loadBMP(p->renderer_3d, "untitled.bmp");
	p->txt_x_west = loadBMP(p->renderer_3d, "west_x.bmp");
	p->txt_x_east = loadBMP(p->renderer_3d, "east_x.bmp");
	p->txt_y_south = loadBMP(p->renderer_3d, "south_y.bmp");
	p->txt_y_north = loadBMP(p->renderer_3d, "north_y.bmp");
}

int				main(int ac, char **av)
{
	t_print			p;

	if (ac != 2)
		return (0);
	ft_get_the_map(av, &p);
	SDL_Init(SDL_INIT_EVERYTHING);
	p.w = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN);
	p.window_3d = SDL_CreateWindow("Window 3D", SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN);
	p.renderer_3d = SDL_CreateRenderer(p.window_3d, 0, SDL_RENDERER_SOFTWARE);
	SDL_RenderPresent(p.renderer_3d);
	ft_load_bmp(&p);
	p.ren = SDL_CreateRenderer(p.w, 0, SDL_RENDERER_SOFTWARE);
	init_renderer(p.ren, &(p.m));
	get_player_pos(&p, &(p.pl), &(p.m));
	ft_raycast(&p, &(p.pl), &(p.m), EST, p.txt);
	SDL_RenderPresent(p.ren);
	ft_event_loop(&p);
	ft_quit(&p);
	return (0);
}
