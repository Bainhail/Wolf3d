/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_3d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:05:57 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/22 11:42:19 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Texture		*loadBMP(SDL_Window *window, SDL_Renderer *tmp_renderer)
{
	//SDL_Surface			*surface;
	SDL_Texture			*txt;
	//SDL_Window			*window;


	(void)window;


	SDL_Surface			*tmp;
	tmp = SDL_LoadBMP("untitled.bmp");
	if(NULL == tmp)
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
	else
		printf("load BMP ok\n\n");

	//window = SDL_CreateWindow("Affiche texture", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINX, WINY, SDL_WINDOW_SHOWN);


	//SDL_Renderer		*tmp_renderer;
	//tmp_renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);


	txt = SDL_CreateTextureFromSurface(tmp_renderer, tmp);
	if (txt == NULL)
	{
		printf("LA TEXTURE bouuu ?!\n");
		exit(0);
	}

//	 SDL_Rect	srcrect;
//	 SDL_Rect	dstrect;
//
//	srcrect.x = 0;
//	srcrect.y = 0;
//	srcrect.w = 40;
//	srcrect.h = 54;
//
//	dstrect.x = 10;
//	dstrect.y = 10;
//	dstrect.w = 40;
//	dstrect.h = 54;
//	SDL_RenderCopy(renderer, txt, &srcrect, &dstrect);
//
//	SDL_RenderPresent(renderer);

	return (txt);
}

