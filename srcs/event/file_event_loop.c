/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_event_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:19:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/27 12:18:40 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_move_player(int move, t_print *w)
{
	if (move == UP)
	{
		w->pl.pos.x += cos(conv_deg_to_rad(w->pl.flg_dir - 90)) * 16;
		w->pl.pos.y += sin(conv_deg_to_rad(w->pl.flg_dir - 90)) * 16;
	}
	else if (move == DOWN)
	{
		w->pl.pos.x -= cos(conv_deg_to_rad(w->pl.flg_dir - 90)) * 16;
		w->pl.pos.y -= sin(conv_deg_to_rad(w->pl.flg_dir - 90)) * 16;
	}
	else if (move == TRIGO)
	{
		w->pl.flg_dir += 13;
	}
	else if (move == ANTI)
	{
		w->pl.flg_dir -= 13;
	}
	refresh_screen(w);
}

void			ft_update_event_editor(t_my_event *s_event, t_print *w)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			s_event->quit = SDL_TRUE;
		else if (event.type == SDL_KEYDOWN)
		{
			event.key.keysym.scancode == SDL_SCANCODE_W ? ft_move_player(UP, w): 0;
			event.key.keysym.scancode == SDL_SCANCODE_S ? ft_move_player(DOWN, w): 0;
			event.key.keysym.scancode == SDL_SCANCODE_D ? ft_move_player(TRIGO, w) : 0;
			event.key.keysym.scancode == SDL_SCANCODE_A ? ft_move_player(ANTI, w) : 0;
			s_event->key[event.key.keysym.scancode] = SDL_TRUE;
		}
	}
}

void			ft_init_event_editor(t_my_event *s_event)
{
	s_event->key[SDL_SCANCODE_ESCAPE] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_W] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_S] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_D] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_A] = SDL_FALSE;
}

void			ft_event_loop(t_print *w)
{
	t_my_event		s_event;

	ft_init_event_editor(&s_event);
	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		ft_update_event_editor(&s_event, w);
		s_event.key[SDL_SCANCODE_ESCAPE] ? s_event.quit = SDL_TRUE : 0;
		ft_init_event_editor(&s_event);
		SDL_Delay(2);
	}
}
