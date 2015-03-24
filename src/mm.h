typedef struct memory_info {
  unsigned int system_memory_size;
  unsigned int system_memory_blocks;
  unsigned int allocated_blocks;
  unsigned int free_blocks;
  unsigned int *memory_map;
  unsigned int memory_map_size;
} memory_info;


typedef enum {
  SUCCESS,
  FAIL
} STATUS;

extern void* alloc_memory_block();
