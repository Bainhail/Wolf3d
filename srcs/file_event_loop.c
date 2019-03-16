/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_event_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:19:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/16 12:34:38 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "wolf3d.h"

typedef struct			s_my_event
{
	SDL_bool			key[SDL_NUM_SCANCODES];
	SDL_bool			quit;
}						t_my_event;


void		ft_update_event_editor(t_my_event *s_event)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			s_event->quit = SDL_TRUE;
		else if (event.type == SDL_KEYDOWN)
			s_event->key[event.key.keysym.scancode] = SDL_TRUE;
	}
}

void		ft_init_event_editor(t_my_event *s_event)
{
	s_event->key[SDL_SCANCODE_ESCAPE] = SDL_FALSE;
//	s_event->key[SDL_SCANCODE_W] = SDL_FALSE;
}
void	ft_event_loop(void)
{
	t_my_event		s_event;

	ft_init_event_editor(&s_event);
	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		ft_update_event_editor(&s_event);
		s_event.key[SDL_SCANCODE_ESCAPE] ? s_event.quit = SDL_TRUE : 0 ;
//		s_event.key[SDL_SCANCODE_W] ? ft_move_player(UP, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		ft_init_event_editor(&s_event);
		SDL_Delay(2);
	}

}

