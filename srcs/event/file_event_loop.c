/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_event_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:19:33 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/09 17:56:52 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static int	ft_correction_pos(double x, double y, t_print *w)
{
	if (y > 0.01 && x > 0.01 \
		&& (int)(y / w->m.ycase) < w->m.ymax \
		&& (int)(x / w->m.xcase) < w->m.xmax \
		&& w->m.tab[(int)(y / w->m.ycase)][(int)(x / w->m.xcase)].z == 0)
		return (TRUE);
	return (FALSE);
}

static void	ft_mouse_move(int rot, t_print *w)
{
	w->player.flg_dir += rot;
	while (w->player.flg_dir < 0)
		w->player.flg_dir += 360;
	w->player.flg_dir = w->player.flg_dir % 360;
}

void	ft_move(int move, t_print *w)
{
	double	x;
	double	y;

	if (move == UP)
	{
		x = w->player.pos.x + cos(conv_deg_to_rad(w->player.flg_dir)) * 20;
		y = w->player.pos.y + sin(conv_deg_to_rad(w->player.flg_dir)) * 20;
		if (ft_correction_pos(x, y, w) == TRUE)
		{
			w->player.pos.x = x;//+= cos(conv_deg_to_rad(w->player.flg_dir)) * 20;
			w->player.pos.y = y;//+= sin(conv_deg_to_rad(w->player.flg_dir)) * 20;
			refresh_screen(w);
		}
	}
	else if (move == DOWN)
	{
		x = w->player.pos.x - cos(conv_deg_to_rad(w->player.flg_dir)) * 20;
		y = w->player.pos.y - sin(conv_deg_to_rad(w->player.flg_dir)) * 20;
		if (ft_correction_pos(x, y, w) == TRUE)
		{
			w->player.pos.x = x;//-= cos(conv_deg_to_rad(w->player.flg_dir)) * 20;
			w->player.pos.y = y;//-= sin(conv_deg_to_rad(w->player.flg_dir)) * 20;
			refresh_screen(w);
		}
	}
	else if (move == TRIGO || move == ANTI)
	{
		if (move == TRIGO)
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
}

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

void	ft_update_event(t_my_event *s_event, t_print *w, SDL_Event *event)
{
	static int		mouse = 1;

	if (event->window.event == SDL_WINDOWEVENT_CLOSE)
		s_event->quit = SDL_TRUE;
	if (event->type == SDL_WINDOWEVENT_CLOSE)
		s_event->quit = SDL_TRUE;
	else if (event->type == SDL_KEYDOWN)
	{
		event->key.keysym.scancode == SDL_SCANCODE_O ? \
			ft_enable_mouse_motion(SDL_TRUE, &mouse) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_P ? \
			ft_enable_mouse_motion(SDL_FALSE, &mouse) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_W ? ft_move(UP, w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_S ? ft_move(DOWN, w) : 0;
		if (mouse == 1)
		{
			event->key.keysym.scancode \
				== SDL_SCANCODE_D ? ft_move(TRIGO, w) : 0;
			event->key.keysym.scancode == SDL_SCANCODE_A ? ft_move(ANTI, w) : 0;
		}
		event->key.keysym.scancode == SDL_SCANCODE_M ? ft_map_trigger(w) : 0;
		event->key.keysym.scancode == SDL_SCANCODE_V ? w->m.debug *= -1 : 0;
		event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ? s_event->quit \
			= SDL_TRUE : 0;
	}
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
