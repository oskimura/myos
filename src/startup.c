#include "i386.h"
#include "video.h"
#include "interrupt.h"
#include "multiboot.h"


extern void startup(unsigned long mboot_magic, multiboot_info *mboot_info);
void startup(unsigned long mboot_magic, multiboot_info *mboot_info) {
	unsigned short *video = (unsigned short *)0xb8000;
	unsigned char *str = "hello\r\n";
	unsigned char c;
	struct video_ v;
	init_gdtr();
	init(&v);
	puts(&v,str);

                    
 if(mboot_magic != MULTI_BOOTLOADER_MAGIC) {
   printf(&v,"Error: Invalid magic number");
    return;
  }
 printf(&v,"lower=0x%x[KB], upper=0x%x[KB], TotalMemory=%d[MB]\n\n",
         mboot_info->mem_lower,
         mboot_info->mem_upper,
         (mboot_info->mem_lower + mboot_info->mem_upper + 1024)/1024);

 printf(&v, "MemoryMap[B]:\n");
 init_memory((mboot_info->mem_lower + mboot_info->mem_upper + 1024)*1024);
  memory_map *mmap;
 
  for(mmap = (memory_map *) mboot_info->mmap_addr;
      (unsigned) mmap < (mboot_info->mmap_addr + mboot_info->mmap_length);
      mmap++) {
    printf(&v,"base_addr=0x%x%x, length=0x%x%x, type=%d\n",
           mmap->base_addr_high, mmap->base_addr_low,
           mmap->length_high, mmap->length_low,
           mmap->type);
    if(mmap->type == 1) {
      init_freed_memory_region((mmap->base_addr_high<<32)+mmap->base_addr_low, 
			       (mmap->length_high<<32)+mmap->length_low);

    }
  }
	init_interrupts();


	
	puts(&v, "end\n");
	while(1) {
		hlt();
	}
}


void init_bss()
{


}
