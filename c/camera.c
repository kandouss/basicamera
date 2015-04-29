#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "config.h"
#include "image_proc.h"
#include "cam_input.h"
#include "sdl_output.h"

void mainloop(void)
{
	buffer raw,rgb;
	init_buffer(&rgb,CAM_WIDTH*CAM_HEIGHT*3);
	int ok = start_showing(&rgb,"SDL buffer");
	if(ok==-1)
		fprintf(stderr,"EVERYTHING IS FUCKED\n");

	for(;;)
	{	
		raw = get_frame(3);
		yuy2_to_rgb(&raw,&rgb);
		render();	
	}

	kill_buffer(&rgb);
}

int main(int argc, char **argv)
{
	open_device();
        mainloop();
	close_device();
	
        fprintf(stderr, "\n");
        return 0;
}
