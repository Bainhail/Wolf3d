/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_3d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:05:57 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/21 18:28:23 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		loadBMP()
{
	SDL_Surface		*tmp = SDL_LoadBMP("untitled.bmp");
	if(NULL == tmp)
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
	else
		printf("load BMP ok\n\n");
	
	SDL_Surface *surface = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);

	SDL_Texture *txt;
	SDL_Renderer *renderer;
	SDL_Window	*window;


SDL_Event	ev;
	window = SDL_CreateWindow("Affiche texture", SDL_WINDOWPOS_CENTERED, \
						   SDL_WINDOWPOS_CENTERED, WINX, WINY, \
						   SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);
	txt = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_RenderCopy(renderer, txt, NULL, NULL);

	SDL_UpdateWindowSurface(window);
	SDL_RenderPresent(renderer);
	SDL_PollEvent(&ev);
}

