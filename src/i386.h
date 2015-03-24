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

static __inline__ unsigned char get_low_mem_size()
{
	long success;
	unsigned char size;
	unsigned char status;
	int ax;
	__asm__ __volatile__("int $0x12":"=a"(ax));

	status = ((ax>>4)&0xff);	
	size = (ax&0xff);
	return size;
}

static __volatile__ unsigned int get_extend_mem_size()
{
	char ax;	

	__asm__ __volatile__("movb %%al,%0 \n\t" 
			     "int $0x15\n\t"
			     : "=a"(ax)
			     : "g"(18));

	return ax;
}


/* static __volatile__ get_mem() */
/* { */
/*   __asm__ __volatile__( */
/* 		       "pushad" */
/* 		       "xor %ebx %ebx" */
/* 		       "xor bp" */
/* 		       "mov 'PAMS,' %edx" */
/* 		       "mov $0xe820, %eax" */
/* 		       "mov $24, $ecx" */
/* 		       "int $0x15" */
/* 		       "jc error" */
/* 		       "cmp 'PAMS', %eax" */
/* 		       "jne error" */
/* 		       "test %ebx,%ebx" */
/* 		       "je error" */
/* 		       "jmp start" */
/* 		       ); */
  
/* } */


#endif
