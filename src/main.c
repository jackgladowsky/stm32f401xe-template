#include "stm32f401xe.h"
//#include <stdio.h>
#include "sys_clk_cfg.h"
#include "gpio.h"
#include "utilities.h"

/*
 * The BUTTON,
 * -> see schematic of NUCLEO-F401RE board
 */

GPIO_PIN_CFG button_pin_cfg = {
    .pin = 13, // PC13
    .mode = GPIO_MODE_INPUT,
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

    GPIO_HNDL button_gpio_handle;
    button_gpio_handle.gpiox = GPIOC; // Point to GPIOC port for PC13
    button_gpio_handle.gpio_pin_config = button_pin_cfg; // Assign pin configuration

    sys_clk_ntrl_cfg();
    // sys_clk_hprf_cfg();

    gpio_init(&button_gpio_handle); // Initialize the GPIO pin for the button

    while(1) {

        uint8_t state;
        GPIO_ERR err = gpio_read_pin(GPIOC, 13, &state);

        if (!err == GPIO_OK)
        {
            return 0;
        }

        if (state == 0)
        {

        }

        delay(100);
    
    }
}

