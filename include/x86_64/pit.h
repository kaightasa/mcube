/**
 * @file include/x86_64/pit.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_X86_64_PIT_H__
#define __MCUBE_X86_64_PIT_H__


/**
 * @cond
 */
BEGIN_EXTERN_C
/**
 * @endcond
 */



#ifndef __ASSEMBLY__


/**
 * @def PIT_CLOCK_RATE
 * @brief Hz (ticks per second).
 */
#define PIT_CLOCK_RATE 1193182UL


/**
 * Extract a PIT-related bit from port 0x61
 */
enum {
  PIT_GATE2   = 0x1,    /* bit 0 - PIT's GATE-2 input */
  PIT_SPEAKER = 0x2,    /* bit 1 - enable/disable speaker */
  PIT_OUT2    = 0x20,    /* bit 5 - PIT's OUT-2 */
};

/*
 * The PIT's system interface: an array of peripheral I/O ports.
 * The peripherals chip translates accessing below ports to the
 * right PIT's A0 and A1 address pins, and RD/WR combinations.
 */
enum {
  PIT_COUNTER0 =  0x40,    /* read/write Counter 0 latch */
  PIT_COUNTER1 =  0x41,    /* read/write Counter 1 latch */
  PIT_COUNTER2 =  0x42,    /* read/write Counter 2 latch */
  PIT_CONTROL  =  0x43,    /* read/write Chip's Control Word */
};

/**
 * @union pit_cmd
 * @brief Control word format.
 */
union pit_cmd {
  /**
   * Raw.
   */
  uint8_t raw;
  struct {
    /**
     * Control word.
     */
    uint8_t bcd: 1,   /* BCD format for counter divisor? */
            mode: 3,   /* Counter modes 0 to 5 */
            rw: 2,   /* Read/Write latch, LSB, MSB, or 16-bit */
            timer: 2; /* Which timer of the three (0-2) */
  } __packed /** packed. */;
};

/*
 * Read/Write control bits
 */
enum {
  RW_LATCH =  0x0,    /* Counter latch command */
  RW_LSB   =  0x1,    /* Read/write least sig. byte only */
  RW_MSB   =  0x2,    /* Read/write most sig. byte only */
  RW_16bit =  0x3,    /* Read/write least then most sig byte */
};

/*
 * Counters modes
 */
enum {
  MODE_0 =  0x0,    /* Single interrupt on timeout */
  MODE_1 =  0x1,    /* Hardware retriggerable one shot */
  MODE_2 =  0x2,    /* Rate generator */
  MODE_3 =  0x3,    /* Square-wave mode */
};

/**
 * @var pit_ticks_count
 * @brief PIT ticks count.
 */
extern volatile int pit_ticks_count;

/**
 * @fn void pit_udelay(uint64_t us)
 * @brief PIT microsecond delay.
 *
 * @param us Microsecond.
 */
void pit_udelay(uint64_t us);

/**
 * @fn void pit_oneshot(uint64_t us)
 * @brief PIT oneshot timer.
 *
 * @param us Microsecond.
 */
void pit_oneshot(uint64_t us);

/**
 * @fn void pit_monotonic(uint64_t us)
 * @brief PIT monotonic timer.
 *
 * @param us Microsecond.
 */
void pit_monotonic(uint64_t us);

/**
 * @fn void __pit_periodic_handler(void)
 * @brief PIT periodic handler in C.
 */
void __pit_periodic_handler(void);

/**
 * @fn void pit_periodic_handler(void)
 * @brief PIT periodic handler in assembler.
 */
void pit_periodic_handler(void);

/**
 * @fn void init_pit_timer(unsigned long tick_us)
 * @brief initialize PIT timer.
 *
 * @param tick_us Tick [us].
 */
void init_pit_timer(unsigned long tick_us);

/**
 * @fn void start_pit_timer(void)
 * @brief start PIT timer.
 */
void start_pit_timer(void);

/**
 * @fn void stop_pit_timer(void)
 * @brief stop PIT timer.
 */
void stop_pit_timer(void);


#endif /* !__ASSEMBLY__ */

/**
 * @cond
 */
END_EXTERN_C
/**
 * @endcond
 */

#endif /* __MCUBE_X86_64_PIT_H__ */
