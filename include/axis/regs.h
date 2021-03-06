/**
 * @file include/axis/regs.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_AXIS_REGS_H__
#define __MCUBE_AXIS_REGS_H__

/**
 * @def REG_LENGTH
 * @brief Register length.
 */
#define REG_LENGTH 32

/**
 * @def NR_GENERAL_PURPOSE_REGS
 * @brief Number of general purpose registers.
 */
#define NR_GENERAL_PURPOSE_REGS 32

#ifndef __ASSEMBLY__


/**
 * @struct gpr_regs
 * @brief General purpose registers.
 */
struct gpr_regs {
  /**
   * General purpose registers in AXIS.
   */
  uint32_t regs[NR_GENERAL_PURPOSE_REGS];
};


/**
 * @def NR_SPECIAL_REGS
 * @brief Number of special registers.
 */
#define NR_SPECIAL_REGS 9

/**
 * @struct special_regs
 * @brief Special registers.
 */
struct special_regs {
  /**
   * Special registers in AXIS.
   */
  uint32_t regs[NR_SPECIAL_REGS];
};


/**
 * @def NR_SYSTEM_REGS
 * @brief Number of readable system registers.
 */
#define NR_SYSTEM_REGS 4

/**
 * @def NR_COMMON_SYSTEM_REGS
 * @brief Number of readable common system registers.
 */
#define NR_COMMON_SYSTEM_REGS 1

/**
 * @struct system_regs
 * @brief System registers.
 */
struct system_regs {
  /**
   * Special registers of each core in AXIS.
   */
  uint32_t regs[NR_CPUS][NR_SYSTEM_REGS];

  /**
   * Common special registers.
   */
  uint32_t common_regs[NR_COMMON_SYSTEM_REGS];
};


/**
 * @struct full_regs
 * @brief Full registers.
 */
struct full_regs {
  /**
   * General purpose registers in AXIS.
   */
  struct gpr_regs gpr_regs;

  /**
   * Special registers in AXIS.
   */
  struct special_regs spe_regs;

  /**
   * System registers in AXIS.
   */
  struct system_regs sys_regs;
};



#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_AXIS_REGS_H__ */
