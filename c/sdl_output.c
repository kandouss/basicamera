#include <SDL/SDL.h>

SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *cam_surface = NULL;

void createCamImage (int w,int h)
{
	int bpp,pitch;
	Uint32 rmask, gmask, bmask, amask;
	int x,y;
	int b;

	bpp=32;
	pitch = w * 4;

	amask = 0xff000000;
	bmask = 0x00ff0000;
	gmask = 0x0000ff00;
	rmask = 0x000000ff;
	mypixels = (char*)malloc (w*h*4);
	
	for (b=0;b<w*h*4;b++)
		mypixels[b]=255;	

	cam_surface = SDL_CreateRGBSurfaceFrom (mypixels,w,h,bpp,pitch,rmask,gmask,bmask,amask);
	for (y=0;y<h;y++)
	{
		for (x=0;x<w;x++)
		{
			mypixels[y*pitch+x*4]=0;
			mypixels[y*pitch+x*4+1]=0;
			mypixels[y*pitch+x*4+2]=0;
			mypixels[y*pitch+x*4+3]=255;
			
		}
	}
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	
	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, NULL, destination, &offset );
}


int open_sdl_output()
{
	SDL_Event event;
	if (SDL_INIT( SDL_INIT_EVERYTHING ) == -1 )
	{
		return -1;
	}	

	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	if (screen == NULL)
	{
		return -1;
	}

	createCamImage(CAM_WIDTH, CAM_HEIGHT)

	apply_surface(0,0,cam_surface, screen);

	if( SDL_Flip( screen ) == -1)
	{
		return -1;
	}
}

int close_sdl_output(void)
{
	SDL_FreeSurface(cam_surface);
	SDL_Quit();

	return 0;
}
