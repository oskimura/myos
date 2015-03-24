#include "mm.h"
#include "mem.h"

#define MEMORY_BLOCK_SIZE 4096
#define	KERNEL_START	0x00100000

extern void _text_start;
extern void _text_end;
extern void _bss_start;
extern void _bss_end;


static memory_info mm;



int __inline__ get_kernel_size() 
{
  return &_bss_end - &_text_start;
}


void init_memory(unsigned int size) 
{
  mm. system_memory_size = size;
  mm. system_memory_blocks = size / MEMORY_BLOCK_SIZE;
  mm. allocated_blocks = size / MEMORY_BLOCK_SIZE;
  mm. free_blocks = 0;
  mm. memory_map = KERNEL_START + get_kernel_size();
  mm. memory_map_size = mm.system_memory_blocks /32;

  memsetw(mm.memory_map,
	 0xff,
	 mm.memory_map_size);
}



/* void print_memory(video* v) */
/* { */
/*   printf(v, "system_memory_size %x\n",mm.system_memory_size); */
/*   printf(v, "system_memory_blocks %x\n", mm.system_memory_blocks); */
/*   printf(v, "allocated_blocks %x\n", mm.allocated_blocks); */
/*   printf(v, "free_blocks %x\n", mm.free_blocks); */
/*   printf(v, "memory_map　%x\n", mm.memory_map); */
/*   printf(v, "memory_map_size %x\n", mm.memory_map_size); */
/* } */


static void set_bit(int number) 
{
  mm.memory_map[number/32] |= (1<<(number%32));
  
}

static void clear_bit(int number) 
{
  mm.memory_map[number/32]&= ~(1<<(number%32));
}


static char test_bit(int number)
{
  unsigned int test;
  test = mm.memory_map[number/32] & (1<<(number%32));
  return (test>0);
}
  
static STATUS find_first_free_memory(unsigned int *number)
{
  unsigned int index;
  unsigned int count;
  unsigned int found;

  for (index=0;
       index < mm. memory_map_size;
       index++) {
    if (mm.memory_map[index] !=  0xFFFFFFFF) {
      for (count=0; count<32; count++) {
	if (!test_bit(count)) {
	  *number = (unsigned int) index * sizeof(unsigned int)* 8 +count;
	  return SUCCESS;
	}
      }
    }
  }
  return FAIL;
}

void init_freed_memory_region(void *address, unsigned int size)
{
  unsigned int number;
  
  number = (unsigned int) address / MEMORY_BLOCK_SIZE;
  int block_size;
  block_size = size / MEMORY_BLOCK_SIZE;
  
  int i;
  for (i=block_size;0<i;i--) {
    clear_bit(number);
    number++;
    mm.allocated_blocks--;
    mm.free_blocks++;
  }
}


void init_allocated_memory_regoin(void *address, int size)
{
  unsigned int number;
  int block_size;
  int i;
  
  number = (unsigned int) address / MEMORY_BLOCK_SIZE;
  block_size = size / MEMORY_BLOCK_SIZE;

  for (i= block_size; 0<i; i--) {
    set_bit(number);

    number++;
    mm.allocated_blocks++;
    mm.free_blocks--;
  }
}

void* alloc_memory_block() 
{
  unsigned int number;
  void *address;
  int status;
  
  if (mm.free_blocks <= 0) {
    return 0;
  }
  
  status = find_first_free_memory(&number);
  if (status != SUCCESS) {
    return 0;
  }
  set_bit(number);
  address = number * MEMORY_BLOCK_SIZE;

  mm.allocated_blocks++;
  mm.free_blocks--;

  return address;
}

void free_memory_block(void* address)
{
  unsigned int number;
  
  number = (unsigned int) address / MEMORY_BLOCK_SIZE;
  clear_bit(number);
  mm.allocated_blocks--;
  mm.free_blocks++;
}
