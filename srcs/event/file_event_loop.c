/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_event_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:19:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/04/11 17:27:49 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ft_move(int move, t_print *w)
{
	if (move == UP)
	{
		w->player.pos.x += cos(conv_deg_to_rad(w->player.flg_dir)) * 20;
		w->player.pos.y += sin(conv_deg_to_rad(w->player.flg_dir)) * 20;
	}
	else if (move == DOWN)
	{
		w->player.pos.x -= cos(conv_deg_to_rad(w->player.flg_dir)) * 20;
		w->player.pos.y -= sin(conv_deg_to_rad(w->player.flg_dir)) * 20;
	}
	else if (move == TRIGO)
	{
		w->player.flg_dir += 5;
	}
	else if (move == ANTI)
	{
		w->player.flg_dir -= 5;
	}
	while (w->player.flg_dir < 0)
		w->player.flg_dir += 360;
	w->player.flg_dir = w->player.flg_dir % 360;
	refresh_screen(w);
}

void	ft_update_event(t_my_event *s_event, t_print *w, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		s_event->quit = SDL_TRUE;
	else if (event->type == SDL_KEYDOWN)
	{
		event->key.keysym.scancode == SDL_SCANCODE_W ? ft_move(UP, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_S ? ft_move(DOWN, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_D ? ft_move(TRIGO, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_A ? ft_move(ANTI, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_V ? w->m.debug *= -1 : 0;
		s_event->key[event->key.keysym.scancode] = SDL_TRUE;
	}
}

void	ft_init_event(t_my_event *s_event)
{
	s_event->key[SDL_SCANCODE_ESCAPE] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_W] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_S] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_D] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_A] = SDL_FALSE;
}

void	ft_event_loop(t_print *w)
{
	t_my_event		s_event;
	SDL_Event		event;

	ft_init_event(&s_event);
	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		while (SDL_PollEvent(&event))
			ft_update_event(&s_event, w, &event);
		s_event.key[SDL_SCANCODE_ESCAPE] ? s_event.quit = SDL_TRUE : 0;
		ft_init_event(&s_event);
		SDL_Delay(2);
	}
}
