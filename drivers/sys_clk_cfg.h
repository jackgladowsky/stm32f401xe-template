// SystemClockConfig.h

#ifndef __SYS_CLK_CFG_H__
#define __SYS_CLK_CFG_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f401xe.h>

#define HSI_VALUE    ((uint32_t)16000000) // HSI Value 16 MHz

#define PLL_HPERF_M        16
#define PLL_HPERF_N        336
#define PLL_HPERF_P        4

#define PLL_NTRL_M 8            // Division factor for the main PLL input clock
#define PLL_NTRL_N 84           // Main PLL multiplication factor for VCO
#define PLL_NTRL_P 4            // Main PLL division factor for main system clock

// Function prototypes for system clock configuration
void sys_clk_hperf_cfg(void);

void sys_clk_ntrl_cfg(void);

#ifdef __cplusplus
}
#endif

#endif // __SYSTEM_CLOCK_CONFIG_H__
