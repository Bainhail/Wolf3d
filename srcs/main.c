/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/03/07 16:06:29 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int ac, char **av)
{
	t_map	m;
	SDL_Window *test;

	if (ac != 2)
		return (0);
	if (file_to_tab(av[1], &m) == -1)
		printf("ERROR FILE\n");
	SDL_Init(SDL_INIT_EVERYTHING);
	test = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_CreateRenderer(test, 0, SDL_RENDERER_SOFTWARE);
	SDL_Delay(3000);
	SDL_DestroyWindow(test);
	SDL_Quit();
	return (0);
}
