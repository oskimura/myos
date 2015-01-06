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

static __volatile__ void enable() 
{
	__asm__ __volatile__("sti");
}

static __inline__ void disable()
{
	__asm__ __volatile__("cli");
}

static __inline__ void hlt() 
{
	__asm__ __volatile__("hlt");
}
#endif
