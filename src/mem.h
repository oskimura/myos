#ifndef MEM_H
#define MEMH

static __inline__ void memsetw(void* dest, unsigned short val, unsigned int count)
{
	int d0,d1;
	__asm__ __volatile__(
	"cld	\n\t"	
	"rep stosl \n\t"
	: "=&D" (d0), "=&c" (d1), "=&a" (val)
	: "0" ((long) dest), "1" (count), "2" (val)
	: "memory"
	);
}

static __inline__ void *memcpy(void *dest, const void *src, unsigned int n)
{
	int d0, d1, d2;
	__asm__ __volatile__(
	"cld	\n\t"
	"rep movsd	\n\t"
	"test	%4,2	\n\t"
	"je	1f	\n\t"
	"1:		\n\t"
	"test %4,1	\n\t"
	"je 2f		\n\t"
	"movsb		\n"
	"2:		\t"
	: "=&c"(d0), "=&D"(d1), "=&S"(d2)
	: "0"(n/4), "q"(n), "1"((long)dest), "2"((long)src)
	: "memory"	
	);
	return dest;
}
#endif
