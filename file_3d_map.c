/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_3d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:05:57 by jchardin          #+#    #+#             */
/*   Updated: 2019/04/06 13:46:42 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Texture		*loadBMP(SDL_Renderer *tmp_renderer, char *path)
{
	SDL_Texture			*txt;

	SDL_Surface			*tmp;
	tmp = SDL_LoadBMP(path);
	if(NULL == tmp)
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
	else
		/* printf("load BMP ok\n\n") */;

	txt = SDL_CreateTextureFromSurface(tmp_renderer, tmp);
	if (txt == NULL)
	{
		printf("LA TEXTURE bouuu ?!\n");
		exit(0);
	}
	return (txt);
}
