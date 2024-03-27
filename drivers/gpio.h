#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f401xe.h" // Include the header file for STM32F401RE
#include "stdlib.h"

// GPIO Error Codes
typedef enum {
    GPIO_OK = 0,
    GPIO_ERR_INVALID_PORT,
    GPIO_ERR_INVALID_PIN,
    GPIO_ERR_INVALID_MODE,
    GPIO_ERR_INVALID_PARAM // Generic error for invalid parameter
} GPIO_ERR;

// Define GPIO pin modes
#define GPIO_MODE_INPUT     0x00
#define GPIO_MODE_OUTPUT    0x01
#define GPIO_MODE_AF        0x02
#define GPIO_MODE_ANALOG    0x03

// Define output types
#define GPIO_OTYPE_PP       0x00
#define GPIO_OTYPE_OD       0x01

// Define pull-up/pull-down configuration
#define GPIO_NOPULL         0x00
#define GPIO_PULLUP         0x01
#define GPIO_PULLDOWN       0x02

// Define GPIO speed
#define GPIO_SPEED_LOW      0x00
#define GPIO_SPEED_MEDIUM   0x01
#define GPIO_SPEED_FAST     0x02
#define GPIO_SPEED_HIGH     0x03

// GPIO Pin Configuration Structure
typedef struct {
    uint32_t pin;        // GPIO pin number
    uint32_t mode;       // Mode of GPIO pin
    uint32_t otype;      // Output type
    uint32_t pull;       // Pull-up/Pull-down
    uint32_t speed;      // Speed of GPIO
    uint32_t alternate;  // Alternate function mode
} GPIO_PIN_CFG;

// GPIO Handle Structure
typedef struct {
    GPIO_TypeDef *gpiox;               // Pointer to GPIO port base address
    GPIO_PIN_CFG gpio_pin_config; // GPIO pin configuration settings
} GPIO_HNDL;

// Function prototypes with error handling
GPIO_ERR gpio_init(GPIO_HNDL *gpio_handle);
GPIO_ERR gpio_deinit(GPIO_TypeDef *gpiox);
GPIO_ERR gpio_read_pin(GPIO_TypeDef *gpiox, uint16_t pin_number, uint8_t *value);
GPIO_ERR gpio_write_pin(GPIO_TypeDef *gpiox, uint16_t pin_number, uint8_t value);
GPIO_ERR gpio_toggle_pin(GPIO_TypeDef *gpiox, uint16_t pin_number);

#endif // __GPIO_DRIVER_H__
