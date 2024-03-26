#include "sys_clk_cfg.h"

#define HSI_VALUE    ((uint32_t)16000000) // HSI Value 16 MHz
#define PLL_M        16
#define PLL_N        336
#define PLL_P        4

void SystemClock_Config(void) {
    // 1. Enable HSI
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait till HSI is ready

    // 2. Set the power enable clock and voltage scale 1
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    // 3. Configure the PLL for 84MHz SysClk from HSI
    RCC->PLLCFGR = (PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSI) | (7 << 24));

    // 4. Enable the PLL and wait for it to become ready
    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 0);

    // 5. Select the PLL as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    // 6. Configure Flash prefetch, Instruction cache, Data cache and wait state
    FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_2WS;

    // Configure the clocks for the AHB, APB1 and APB2 buses
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // AHB prescaler
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 prescaler
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 prescaler
}
