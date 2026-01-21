#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H

#include "stm32f4xx_hal.h"

// ===========================================================
// Hardware Configuration (Crank Sensor)
// ===========================================================

// TODO: Update these pins according to your PCB wiring!
// IMPORTANT: In STM32CubeMX, configure this pin as "GPIO_EXTI" mode.

#define CRANK_SENSOR_PIN    GPIO_PIN_0     // Example: PA0 is the Crank Signal
#define CRANK_SENSOR_PORT   GPIOA          // Example Port

// ===========================================================
// Function Prototypes
// ===========================================================

// No init needed here (Main MX_GPIO_Init handles it).
// The callback is handled in exti_driver.c

#endif // EXTI_DRIVER_H