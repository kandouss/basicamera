#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"
#include "image_proc.h"

short table_yuv_rgb[256][256][3];
int yuv_rgb_exists = 0;

void init_buffer(buffer *b, size_t b_len)
{
	b->length = b_len;
	b->start = calloc(b_len,sizeof(uint8_t));
}

void kill_buffer(buffer *b)
{
	free(b->start);
}

static void gen_table_yuv_rgb(void)
{
	if(yuv_rgb_exists==1) return;
	fprintf(stderr,"Generating color table.\n");
	uint16_t y,u,v;
	for(u=0; u<256; u++)
	for(v=0; v<256; v++)
	{
		table_yuv_rgb[u][v][0] = (short)(1.14*(v-128));
		table_yuv_rgb[u][v][1] = (short)(-0.395*(u-128)-0.581*(v-128));
		table_yuv_rgb[u][v][2] = (short)(2.032*(u-128));
	}
	yuv_rgb_exists = 1;
}
static inline uint8_t short_to_uint8(short s)
{
	if(s>=255) return 255;
	else if(s <= 0) return 0;
	else return (uint8_t)s;
}

void yuy2_to_rgb (buffer *buf_in, buffer *buf_out)
{
	/* Byte ordering:
	0  1  2  3   |  4  5  6  7    
	Y0 U0 Y1 V0  |  Y2 U2 Y3 V2

	rgb pixels from sequence:
        (Y0,U0,V0); (Y1,U0,V0); (Y2,U2,V2), ..
	
	pixel	bytes
	0	(0,1,3)
	1	(2,1,3)
	2	(4,5,7)
	3	(6,5,7)
	...
	for the k-th pixel:
	k		(2*k, 4*floor(k/2)+1, 4*floor(k/2)+3)
	for the r-th pair:
	r		(r,   r+1, r+3)
			(r+2, r+1, r+3)
	 R = Y + 1.140V
	 G = Y - 0.395U - 0.581V
	 B = Y + 2.032U
	*/
	gen_table_yuv_rgb();
	uint8_t *b1_temp;
	uint8_t *b2_temp;
	uint8_t u,v,y0,y1;
	short r0,g0,b0;
	size_t i;

	for(i = 0; i < buf_in->length/2; i+=2)
	{
		b1_temp = (uint8_t *)(buf_in->start + i*2);
		b2_temp = (uint8_t *)(buf_out->start + i*3);

		v = b1_temp[1];
		u = b1_temp[3];
		y0 = b1_temp[0];
		y1 = b1_temp[2];
		
		r0 = table_yuv_rgb[u][v][0];
		g0 = table_yuv_rgb[u][v][1];
		b0 = table_yuv_rgb[u][v][2];

		//pixel 1
		b2_temp[0] = short_to_uint8(r0+y0);	//r
		b2_temp[1] = short_to_uint8(g0+y0);	//g
		b2_temp[2] = short_to_uint8(b0+y0);	//b

		//pixel 2
		b2_temp[3] = short_to_uint8(r0+y1);	//r
		b2_temp[4] = short_to_uint8(g0+y1);	//g
		b2_temp[5] = short_to_uint8(b0+y1);	//b
	}
}
