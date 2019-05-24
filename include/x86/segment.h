/**
 * @file include/x86/segment.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_X86_SEGMENT_H__
#define __MCUBE_X86_SEGMENT_H__

/*
 * Segmentation definitions; minimal by the nature of x86-64
 *
 * Copyright (C) 2009 Ahmed S. Darwish <darwish.07@gmail.com>
 */

/* offset */
#define KERNEL_CS  0x08
#define KERNEL_DS  0x10
#define KERNEL_CS16  0x18
#define KERNEL_DS16  0x20


/* GDT selectors */
#define GDT_NR                  7
#define GDT_NULL_SEL            (0 << 3)
#define GDT_RING0_CODE_SEL      (1 << 3)
#define GDT_RING0_DATA_SEL      (2 << 3)
#define GDT_RING3_CODE32_SEL    (3 << 3)
#define GDT_RING3_DATA32_SEL    (4 << 3)
#define GDT_RING3_CODE64_SEL    (5 << 3)
#define GDT_RING3_DATA64_SEL    (6 << 3)
#define GDT_TSS_SEL_BASE        (7 << 3)


#ifndef __ASSEMBLY__

struct gdtr *gdt_init(void);
void gdt_load(void);

struct gdt_descriptor {
  uint16_t limit;
  uint64_t base;
} __packed;

/*
 * FIXME: Reload the segment caches with the new GDT
 * values. Just changing the GDTR won't cut it.
 */
static inline void load_gdt(const struct gdt_descriptor *gdt_desc)
{
  asm volatile("lgdt %0"
               :
               :"m"(*gdt_desc));
}

static inline struct gdt_descriptor get_gdt(void)
{
  struct gdt_descriptor gdt_desc;

  asm volatile("sgdt %0"
               :"=m"(gdt_desc)
               :);

  return gdt_desc;
}

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_X86_SEGMENT_H__ */
