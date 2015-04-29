#include "SDL/SDL.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "config.h"
#include "image_proc.h"
#include "sdl_output.h"
 
static SDL_Surface *buffer_surface;

void render(void)
{
	SDL_Surface * screen = SDL_GetVideoSurface();
	if(SDL_BlitSurface(buffer_surface, NULL, screen, NULL) == 0)
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(1);
}

static int event_filter(const SDL_Event * event)
{ 
	return event->type == SDL_QUIT; 
}

int start_showing(buffer *b, const char *name)
{
	atexit(SDL_Quit);
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);

	SDL_WM_SetCaption(name, name);

	buffer_surface = SDL_CreateRGBSurfaceFrom( b->start, 
			SCREEN_WIDTH, SCREEN_HEIGHT, 24, SCREEN_WIDTH*3,
			0xFF0000, 0x00FF00, 0x0000FF, 0);

	SDL_SetEventFilter(event_filter);
	
	return 0;
}


