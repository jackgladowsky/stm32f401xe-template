#include "sys_clk_cfg.h"

void sys_clk_hperf_cfg(void) {
    // 1. Enable HSI
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait till HSI is ready

    // 2. Set the power enable clock and voltage scale 1
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    // 3. Configure the PLL for 84MHz SysClk from HSI
    RCC->PLLCFGR = (PLL_HPERF_M | (PLL_HPERF_N << 6) | (((PLL_HPERF_P >> 1) -1) << 16) |
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

void sys_clk_ntrl_cfg(void) {
    // 1. Enable HSI as a fallback
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait till HSI is ready

    // 2. Power interface clock enable
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    // 3. Configure the main PLL
    RCC->PLLCFGR = (PLL_NTRL_M | (PLL_NTRL_N << 6) | (((PLL_NTRL_P >> 1) -1) << 16) |
                   RCC_PLLCFGR_PLLSRC_HSI | (7 << 24));

    // 4. Enable the PLL and wait for it to become ready
    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 0);

    // 5. Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
    RCC->CFGR |= RCC_CFGR_SW_PLL; // Select PLL as system clock source
    while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL); // Wait for PLL as system clock source
    
    RCC->CFGR |= RCC_CFGR_HPRE_DIV2; // AHB prescaler to half the system clock
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 prescaler to half the HCLK
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 prescaler equal to HCLK

    // 6. Optional: Configure Flash prefetch, instruction cache, data cache, and latency
    FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_1WS;
}


