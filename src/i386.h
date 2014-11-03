#ifndef I386_H
#define I386_H

static __inline__ void outb(unsigned short port, unsigned char val)
{
	__asm__ __volatile__("outb %1, %0"::"Nd"(port), "a"(val));
}

static __inline__ unsigned char inb(unsigned short port)
{
	register unsigned char val;
	__asm__ __volatile__("in al,dx": "=a"(val):"d"(port));
	return val;
}

static __inline__ void hlt() 
{
	__asm__ __volatile__("hlt");
}
#endif
