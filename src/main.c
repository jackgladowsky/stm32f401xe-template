#include "stm32f401xe.h"
//#include <stdio.h>
#include "sys_clk_cfg.h"
#include "gpio.h"
#include "utilities.h"

/*
 * The green LED is connected to port A5,
 * -> see schematic of NUCLEO-F401RE board
 */

GPIO_PIN_CFG led_pin_cfg = {
    .pin = 5, // PA5
    .mode = GPIO_MODE_OUTPUT,
    .otype = GPIO_OTYPE_PP,
    .pull = GPIO_NOPULL,
    .speed = GPIO_SPEED_LOW,
    .alternate = 0 // Not used for basic output
};

/**
 * Main
 *
 * @return never
 */
int main(void) {

    GPIO_HNDL led_gpio_hndl;

    led_gpio_hndl.gpiox = GPIOA;
    led_gpio_hndl.gpio_pin_config = led_pin_cfg;

    sys_clk_ntrl_cfg();
    // sys_clk_hprf_cfg();

    gpio_init(&led_gpio_hndl);

    while(1) {

        gpio_toggle_pin(GPIOA, 5);

        delay(100);
    
    }
}

