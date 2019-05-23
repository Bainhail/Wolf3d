/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_event_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:19:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/23 11:46:04 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ft_list_event(t_my_event *s_event, t_print *w, \
						const Uint8 *event, int *mouse)
{
	event[SDL_SCANCODE_O] == 1 ? \
		ft_enable_mouse_motion(SDL_TRUE, mouse) : 0;
	event[SDL_SCANCODE_P] == 1 ? \
		ft_enable_mouse_motion(SDL_FALSE, mouse) : 0;
	event[SDL_SCANCODE_W] == 1 ? ft_move(UP, w) : 0;
	event[SDL_SCANCODE_UP] == 1 ? ft_move(UP, w) : 0;
	event[SDL_SCANCODE_S] == 1 ? ft_move(DOWN, w) : 0;
	event[SDL_SCANCODE_DOWN] == 1 ? ft_move(DOWN, w) : 0;
	if (*mouse == 1)
	{
		event[SDL_SCANCODE_D] == 1 ? ft_move(TRIGO, w) : 0;
		event[SDL_SCANCODE_RIGHT] == 1 ? ft_move(TRIGO, w) : 0;
		event[SDL_SCANCODE_A] == 1 ? ft_move(ANTI, w) : 0;
		event[SDL_SCANCODE_LEFT] == 1 ? ft_move(ANTI, w) : 0;
	}
	event[SDL_SCANCODE_M] == 1 ? ft_map_trigger(w) : 0;
	event[SDL_SCANCODE_V] == 1 ? w->m.debug *= -1 : 0;
	event[SDL_SCANCODE_ESCAPE] == 1 ? s_event->quit = SDL_TRUE : 0;
}

void	ft_update_event(t_my_event *s_event, t_print *w, const Uint8 *event)
{
	static int		mouse = 1;
	int				x;

	if (event[SDL_WINDOWEVENT_CLOSE] == 1)
		s_event->quit = SDL_TRUE;
	else
		ft_list_event(s_event, w, event, &mouse);
	if (mouse == 0)
	{
		SDL_GetRelativeMouseState(&x, NULL);
		if (x > 10 || x < -10)
			x = x / 10;
		if (x > 0)
			ft_mouse_move(x, w);
		else if (x < 0)
			ft_mouse_move(x, w);
	}
}

void	ft_event_loop(t_print *w)
{
	t_my_event		s_event;
	SDL_Event		event;
	const Uint8		*key_state = SDL_GetKeyboardState(NULL);

	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_WINDOWEVENT
			&& event.window.event == SDL_WINDOWEVENT_CLOSE)
			s_event.quit = SDL_TRUE;
		else
		{
			SDL_PumpEvents();
			ft_update_event(&s_event, w, key_state);
			refresh_screen(w);
		}
		SDL_Delay(1);
	}
}
