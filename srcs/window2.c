/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:35:58 by msrun             #+#    #+#             */
/*   Updated: 2018/12/18 12:38:13 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

SDL_Color	get_color(unsigned char r, unsigned char g, unsigned char b,
		unsigned char s)
{
	const SDL_Color color = {r, g, b, s};

	return (color);
}

SDL_Rect	get_rect(int x, int y, int h, int w)
{
	const SDL_Rect	rect = {x, y, h, w};

	return (rect);
}

void		create_use_surface(SDL_Renderer *renderer, SDL_Surface *surface,
		SDL_Texture **texture)
{
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void		get_txt(t_sdl *sdl)
{
	TTF_Font	*font;

	TTF_Init();
	if (!(font = TTF_OpenFont("font.ttf", 10)))
	{
		TTF_Quit();
		return ;
	}
	sdl->data.color[WHITE] = get_color(255, 255, 255, 255);
	sdl->data.color[BLACK] = get_color(0, 0, 0, 0);
	sdl->data.color[RED] = get_color(255, 0, 0, 255);
	sdl->data.color[GREEN] = get_color(0, 255, 0, 255);
	sdl->data.color[BLUE] = get_color(0, 0, 255, 255);
	create_use_surface(sdl->renderer, TTF_RenderText_Shaded(font,
			str_of_state(EATING), sdl->data.color[GREEN],
			sdl->data.color[WHITE]), &sdl->data.texture_txt[EATING]);
	create_use_surface(sdl->renderer, TTF_RenderText_Shaded(font,
			str_of_state(THINKING), sdl->data.color[RED],
			sdl->data.color[WHITE]), &sdl->data.texture_txt[THINKING]);
	create_use_surface(sdl->renderer, TTF_RenderText_Shaded(font,
			str_of_state(RESTING), sdl->data.color[BLUE],
			sdl->data.color[WHITE]), &sdl->data.texture_txt[RESTING]);
	TTF_CloseFont(font);
	TTF_Quit();
}

void		get_data(t_sdl *sdl)
{
	create_use_surface(sdl->renderer, SDL_LoadBMP("assiette.bmp"),
			&sdl->data.texture[EATING]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("think.bmp"),
			&sdl->data.texture[THINKING]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("zzz.bmp"),
			&sdl->data.texture[RESTING]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("baguette.bmp"),
			&sdl->data.texture[3]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("aristote.bmp"),
			&sdl->data.texture[4]);
	get_txt(sdl);
}
