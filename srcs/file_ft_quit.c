/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ft_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:57:49 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/27 11:58:26 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		ft_quit(t_print *p)
{
	SDL_DestroyRenderer(p->ren);
	SDL_DestroyRenderer(p->renderer_3d);
	SDL_DestroyWindow(p->window_3d);
	SDL_Quit();
}
