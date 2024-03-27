#include "gpio.h"

GPIO_ERR gpio_init(GPIO_HNDL *gpio_handle) 
{
    // Check if the GPIO handle and associated GPIO port are valid
    if (gpio_handle == NULL || gpio_handle->gpiox == NULL) 
    {
        return GPIO_ERR_INVALID_PARAM;
    }

    // 1. Enable the GPIO clock
    if (gpio_handle->gpiox == GPIOA) 
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    } 
    else if (gpio_handle->gpiox == GPIOB) 
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    }
    else if (gpio_handle->gpiox == GPIOC) 
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    }

    // TODO 
    // Add the rest of the GPIO clocks

    // 2. Configure the GPIO pin mode
    gpio_handle->gpiox->MODER &= ~(0x3 << (2 * gpio_handle->gpio_pin_config.pin)); // Clear mode
    gpio_handle->gpiox->MODER |= (gpio_handle->gpio_pin_config.mode << (2 * gpio_handle->gpio_pin_config.pin)); // Set new mode

    // 3. Configure the output type if applicable
    if (gpio_handle->gpio_pin_config.mode == GPIO_MODE_OUTPUT) 
    {
        gpio_handle->gpiox->OTYPER &= ~(0x1 << gpio_handle->gpio_pin_config.pin); // Clear output type
        gpio_handle->gpiox->OTYPER |= (gpio_handle->gpio_pin_config.otype << gpio_handle->gpio_pin_config.pin); // Set new output type
    }

    // 4. Configure the pull-up/pull-down resistors
    gpio_handle->gpiox->PUPDR &= ~(0x3 << (2 * gpio_handle->gpio_pin_config.pin)); // Clear pull-up/pull-down
    gpio_handle->gpiox->PUPDR |= (gpio_handle->gpio_pin_config.pull << (2 * gpio_handle->gpio_pin_config.pin)); // Set new pull-up/pull-down

    // 5. Configure the output speed
    gpio_handle->gpiox->OSPEEDR &= ~(0x3 << (2 * gpio_handle->gpio_pin_config.pin)); // Clear speed
    gpio_handle->gpiox->OSPEEDR |= (gpio_handle->gpio_pin_config.speed << (2 * gpio_handle->gpio_pin_config.pin)); // Set new speed

    // 6. Configure the alternate function if the mode is set to alternate function
    if (gpio_handle->gpio_pin_config.mode == GPIO_MODE_AF) 
    {
        uint32_t afr_idx = gpio_handle->gpio_pin_config.pin / 8; // AFR Index
        uint32_t afr_sft = (gpio_handle->gpio_pin_config.pin % 8) * 4; // AFR Shift
        gpio_handle->gpiox->AFR[afr_idx] &= ~(0xF << afr_sft); // Clear alternate function
        gpio_handle->gpiox->AFR[afr_idx] |= (gpio_handle->gpio_pin_config.alternate << afr_sft); // Set new alternate function
    }

    return GPIO_OK;
}

GPIO_ERR gpio_deinit(GPIO_TypeDef *gpiox) 
{

    if (gpiox == GPIOA) 
    {
        RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOARST;
        RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOARST;
    } 
    else if (gpiox == GPIOB) 
    {
        RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOBRST;
        RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOBRST;
    }
    else if (gpiox == GPIOC) 
    {
        RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOCRST;
        RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOCRST;
    }
    // TODO
    // Similar conditions would be applied for other GPIO ports

    return GPIO_OK;
}

GPIO_ERR gpio_read_pin(GPIO_TypeDef *gpiox, uint16_t pin_number, uint8_t *value) 
{
    if (!gpiox) 
        return GPIO_ERR_INVALID_PORT;

    if (!value) 
        return GPIO_ERR_INVALID_PARAM;

    *value = (uint8_t)((gpiox->IDR >> pin_number) & 0x00000001);

    return GPIO_OK;
}

GPIO_ERR gpio_write_pin(GPIO_TypeDef *gpiox, uint16_t pin_number, uint8_t value) 
{
    if (!gpiox) 
        return GPIO_ERR_INVALID_PORT;

    if (value) 
    {
        gpiox->ODR |= (1 << pin_number);
    } 
    else 
    {
        gpiox->ODR &= ~(1 << pin_number);
    }

    return GPIO_OK;
}

GPIO_ERR gpio_toggle_pin(GPIO_TypeDef *gpiox, uint16_t pin_number) 
{
    if (!gpiox) 
        return GPIO_ERR_INVALID_PORT;

    gpiox->ODR ^= (1 << pin_number);

    return GPIO_OK;
}
