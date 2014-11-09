#ifndef VIDEO_H
#define VIDEO_H

#define BLANK ((0x0f)<<8)|0x20
typedef struct video_ {
	unsigned short crt_port;
	unsigned char crt_width;
	unsigned char crt_height;
	unsigned short cur_pos;
	unsigned short *vram;
} video;


#endif
