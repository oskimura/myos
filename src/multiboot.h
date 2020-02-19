#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEARDER_FLAGS 0x00000000
#define MULTIBOOT_HEADER_CHECKSUM (MULTIBOOT_HEADER_MAGIC+MULTIBOOT_HEARDER_FLAGS)
#define KERNEL_STACK_SIZE 0x100000
#define MULTI_BOOTLOADER_MAGIC 0x2BADB002

#ifndef ASM
typedef struct multiboot_info {
    unsigned long flags;
    unsigned long mem_lower;
    unsigned long mem_upper;
    unsigned long boot_device;
    unsigned long cmdline;
    unsigned long mods_count;
    unsigned long mods_addr;

    unsigned long num;
    unsigned long size;
    unsigned long addr;
    unsigned long shndx;

    unsigned long mmap_length;
    unsigned long mmap_addr;
} __attribute__((__packed__)) multiboot_info;

typedef struct  memory_map
{
    unsigned long size;
    unsigned long base_addr_low;
    unsigned long base_addr_high;
    unsigned long length_low;
    unsigned long length_high;
    unsigned long type;
    /* data */
} __attribute__((__packed__)) memory_map;

#endif
#endif