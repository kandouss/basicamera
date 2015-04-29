#include <stdio.h>
#include <stdlib.h>
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

#include "cam_input.h"

static void process_image(buffer b)
{
        fflush(stderr);
        fprintf(stderr, ".");
	fprintf(stdout,"buffer is (%u,%u)\n",b.start,b.length);
        fflush(stdout);
}

void mainloop(void)
{
	unsigned int count;
	
	count = 10;

	while(count --> 0) {
		fprintf(stdout,"loop index is %d\n",count);
		buffer b = get_frame(3);
		process_image(b);
	}
}

int main(int argc, char **argv)
{
	open_device();
        mainloop();
	close_device();
	
        fprintf(stderr, "\n");
        return 0;
}
