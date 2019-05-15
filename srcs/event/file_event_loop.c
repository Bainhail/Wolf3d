/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_event_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:19:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/15 14:33:53 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ft_list_event(t_my_event *s_event, t_print *w, \
						SDL_Event *event, int *mouse)
{
	event->key.keysym.scancode == SDL_SCANCODE_O ? \
		ft_enable_mouse_motion(SDL_TRUE, mouse) : 0;
	event->key.keysym.scancode == SDL_SCANCODE_P ? \
		ft_enable_mouse_motion(SDL_FALSE, mouse) : 0;
	event->key.keysym.scancode == SDL_SCANCODE_W ? ft_move(UP, w) : 0;
	event->key.keysym.scancode == SDL_SCANCODE_UP ? ft_move(UP, w) : 0;
	event->key.keysym.scancode == SDL_SCANCODE_S ? ft_move(DOWN, w) : 0;
	event->key.keysym.scancode == SDL_SCANCODE_DOWN ? ft_move(DOWN, w) : 0;
	if (*mouse == 1)
	{
		event->key.keysym.scancode \
			== SDL_SCANCODE_D ? ft_move(TRIGO, w) : 0;
		event->key.keysym.scancode \
			== SDL_SCANCODE_RIGHT ? ft_move(TRIGO, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_A ? ft_move(ANTI, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_LEFT ? ft_move(ANTI, w) : 0;
	}
	event->key.keysym.scancode == SDL_SCANCODE_M ? ft_map_trigger(w) : 0;
	event->key.keysym.scancode == SDL_SCANCODE_V ? w->m.debug *= -1 : 0;
	event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ? s_event->quit = \
		SDL_TRUE : 0;
}

void	ft_update_event(t_my_event *s_event, t_print *w, SDL_Event *event)
{
	static int		mouse = 1;

	if (event->window.event == SDL_WINDOWEVENT_CLOSE)
		s_event->quit = SDL_TRUE;
	if (event->type == SDL_WINDOWEVENT_CLOSE)
		s_event->quit = SDL_TRUE;
	else if (event->type == SDL_KEYDOWN)
		ft_list_event(s_event, w, event, &mouse);
	if (mouse == 0 && event->type == SDL_MOUSEMOTION)
	{
		if (event->motion.xrel > 0 && event->motion.xrel < 32767)
			ft_mouse_move(event->motion.xrel, w);
		else if (event->motion.xrel < 0)
			ft_mouse_move(event->motion.xrel, w);
		refresh_screen(w);
	}
}

void	ft_event_loop(t_print *w)
{
	t_my_event		s_event;
	SDL_Event		event;

	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		while (SDL_PollEvent(&event))
			ft_update_event(&s_event, w, &event);
		SDL_Delay(1);
	}
}
