#define ASM 1
#include "multiboot.h"

    .text
    .code32
    .intel_syntax noprefix
    .global _start
_start:
    jmp entry
    .align 4
    .long MULTIBOOT_HEADER_MAGIC
    .long MULTIBOOT_HEARDER_FLAGS
    .long MULTIBOOT_HEADER_CHECKSUM

entry:
    push    ebx
    push    eax
    call startup
loop:
    hlt
    jmp     loop