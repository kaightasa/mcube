/**
 * @file include/x86/dump.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_X86_DUMP_H__
#define __MCUBE_X86_DUMP_H__
/**
 *  @brief      Debugging memory and CPU state dump routines.
 *
 *  Copyright 2016 Brett Vickers.
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the MonkOS LICENSE file.
 */

#ifndef __ASSEMBLY__

/**
 *  @fn         dump_registers
 *  @brief      Dump the contents of a CPU registers structure to a string
 *              buffer.
 *  @param[in]  regs    Pointer to a CPU registers structure.
 */
void dump_registers(const registers_t *regs);

/**
 *  @fn         dump_cpuflags
 *  @brief      Dump the contents of the CPU flags register.
 *  @param[in]  rflags  The 64-bit rflags register value.
 */
void dump_cpuflags(uint64_t rflags);

/**
 *  @enum       dumpstyle
 *  @brief      Memory dump output style.
 *  @details    Used to select how the memory address is displayed in a
 *              a memory dump.
 */
enum dumpstyle {
  DUMPSTYLE_NOADDR = 0,        ///< No address or offset in memory dump.
  DUMPSTYLE_ADDR   = 1,        ///< Include full address in memory dump.
  DUMPSTYLE_OFFSET = 2,        ///< Include address offset in memory dump.
};

/**
 *  @fn         dump_memory
 *  @brief      Dump the contents of memory.
 *  @param[in]  buf     Pointer to the character buffer to hold the resulting
 *                      null-terminated string.
 *  @param[in]  bufsize Size of the buffer used to hold the string.
 *  @param[in]  mem     Pointer to the first byte of memory to dump.
 *  @param[in]  memsize Number of memory bytes to dump.
 *  @param[in]  style   The output style used for the memory dump.
 *  @returns    The number of characters that would have been written to the
 *              buffer if n had been sufficiently large.
 */
int dump_memory(char *buf, size_t bufsize, const void *mem, size_t memsize,
                enum dumpstyle style);
#endif	/* !__ASSEMBLY__ */

#endif	/* __MCUBE_X86_DUMP_H__ */
