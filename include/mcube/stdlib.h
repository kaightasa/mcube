/**
 * @file include/mcube/stdlib.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_MCUBE_STDLIB_H__
#define __MCUBE_MCUBE_STDLIB_H__

#ifndef __ASSEMBLY__

typedef int (*sortcmp)(const void *a, const void *b);

void *kmalloc(size_t size);
void kfree(void *addr);


char *itoa(int val, char *buf, int radix);
char *ltoa(long val, char *buf, int radix);
char *ultoa(unsigned long val, char *buf, int radix);


#if CONFIG_ARCH_SIM

#include <stdlib.h>

#elif CONFIG_ARCH_X86 || CONFIG_ARCH_ARM_RASPI3 || CONFIG_ARCH_ARM_SYNQUACER || CONFIG_ARCH_AXIS

long strtol(const char *cp, char **endp, int base);
unsigned long strtoul(const char *cp, char **endp, int base);
void exit(int status);

void *sbrk(intptr_t increment);

void *malloc(size_t size);
void *calloc(size_t num, size_t nsize);
void *realloc(void *block, size_t size);
void free(void *objp);


void qsort(void *base, size_t num, size_t size, sortcmp cmp);

void init_malloc(void);

#endif /* CONFIG_ARCH_SIM */




/**
 * @brief mem_block_header
 *
 * The mem_block structure has memory block information for dynamic allocation.
 */
struct mem_block_header {
  size_t size;
  unsigned int is_free;
  struct mem_block_header *next;
};

typedef struct mem_block_header mem_block_header;


/* 4k */
#define BLOCK_NUM 0x8
#define MALLOC_SIZE (0x1000 + (BLOCK_NUM - 1) * sizeof(struct mem_block_header))

extern unsigned char user_malloc[MALLOC_SIZE];

extern spinlock_t global_malloc_lock;

struct mem_block_header *get_free_block(size_t size);


#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_MCUBE_STDLIB_H__ */
