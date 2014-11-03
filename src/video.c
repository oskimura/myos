#include "i386.h"
#include "mem.h"
#include "video.h"

typedef struct video_ {
	unsigned short crt_port;
	unsigned char crt_width;
	unsigned char crt_height;
	unsigned short cur_pos;
	unsigned short *vram;
} video;

void set_cur(video *v)
{
	outb(v->crt_port,15);
	outb(v->crt_port+1,v->cur_pos);
	outb(v->cur_pos,14);
	outb(v->crt_port+1,v->cur_pos>>8);
}

void scroll_up(video *v) {
	memcpy((void*)(v->vram),
		(void*)(v->vram)+v->crt_width*2,
		v->crt_width*(v->crt_height-1)*2);
	memsetw((void*)(v->vram)+ v->crt_width*2*(v->crt_width-1),
		BLANK,
		v->crt_width);
	v->cur_pos -= v->crt_width;
	set_cur(v);
}

void clrscr(video *v)
{
	memsetw((void*)(v->vram),
		BLANK,
		v->crt_height * v->crt_width);
	v->cur_pos = 0;
	set_cur(v);
}

void putchar(video *v, char c)
{
	switch (c) {
	case 'r':
		v->cur_pos -= v->cur_pos % v->crt_width;
		break;
	case '\n':
		v->cur_pos += (v->crt_width - (v->cur_pos % v->crt_width));
		break;
	case '\b':
		if(v->cur_pos>0) {
			(v->vram)[--(v->cur_pos)] = ((0x0f)<<8)|0x20;
		}
	case 't':
		v->cur_pos += 8;
	default:
		(v->vram)[(v->cur_pos)++] = ((0x0f)<<8)|c;
	}
	if(v->cur_pos >= v->crt_width*v->crt_height) {
		scroll_up(v);
	}
	set_cur(v);
}

void init(video *v)
{
	v->crt_port = 0x3D4;
	v->crt_width = 80;
	v->crt_height = 25;
	v->vram = (unsigned short*)0xb8000;
	clrscr(v);	
}

void puts(video* v,const char *str) 
{
	while (*str) {
		putchar(v,*str++);
	}
}

