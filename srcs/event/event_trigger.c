/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:59:37 by naali             #+#    #+#             */
/*   Updated: 2019/05/13 17:00:44 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ft_enable_mouse_motion(int boolean, int *mouse)
{
	if (boolean == SDL_TRUE)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		*mouse = 0;
	}
	if (boolean == SDL_FALSE)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		*mouse = 1;
	}
}

void	ft_map_trigger(t_print *w)
{
	static int		show = 0;

	if (show == 0)
	{
		SDL_ShowWindow(w->window[MAP_2D]);
		show = 1;
	}
	else
	{
		SDL_HideWindow(w->window[MAP_2D]);
		show = 0;
	}
	refresh_screen(w);
}
