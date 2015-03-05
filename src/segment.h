#ifndef SEGMENT_H
#define SEGMENT_H

#include "types.h"

typedef struct segment_descriptor {
  unsigned short limit_low;
  unsigned short base_addr_low;
  unsigned char base_addr_mid;
  unsigned short flags;
  unsigned char base_addr_high;

} __attribute__((__packed__)) segment_descriptor;

#define NUM_GDT 3


typedef struct gdtr_ {
  unsigned short size;
  segment_descriptor* base;
  
} __attribute__((__packed__)) gdtr;

#endif
