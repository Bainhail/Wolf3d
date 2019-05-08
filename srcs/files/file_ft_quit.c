/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ft_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:57:49 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/07 17:42:49 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_quit(char *txt, t_print *s_win)
{
	ft_putstr(txt);
	if (s_win->window[MAP_2D] != NULL)
		SDL_DestroyWindow(s_win->window[MAP_2D]);
	if (s_win->renderer[MAP_2D] != NULL)
		SDL_DestroyRenderer(s_win->renderer[MAP_2D]);
	if (s_win->window[MAP_3D] != NULL)
		SDL_DestroyWindow(s_win->window[MAP_3D]);
	if (s_win->renderer[MAP_3D] != NULL)
		SDL_DestroyRenderer(s_win->renderer[MAP_3D]);
	SDL_Quit();
	exit(1);
}
