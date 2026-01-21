#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f4xx_hal.h" // HAL Library access

// ===========================================================
// Hardware Pin Configuration (Pin Mapping)
// ===========================================================

// TODO: Check your PCB Schematic! These are placeholders.
// Update these Ports and Pins to match your actual STM32 wiring.

// --- Ignition Coils (Spark) ---
#define COIL_PORT       GPIOA          // Port for Coils
#define COIL_1_PIN      GPIO_PIN_0     // Cylinder 1
#define COIL_2_PIN      GPIO_PIN_1     // Cylinder 2
#define COIL_3_PIN      GPIO_PIN_2     // Cylinder 3
#define COIL_4_PIN      GPIO_PIN_3     // Cylinder 4

// --- Fuel Injectors ---
#define INJ_PORT        GPIOB          // Port for Injectors
#define INJ_1_PIN       GPIO_PIN_0     // Cylinder 1
#define INJ_2_PIN       GPIO_PIN_1     // Cylinder 2
#define INJ_3_PIN       GPIO_PIN_2     // Cylinder 3
#define INJ_4_PIN       GPIO_PIN_3     // Cylinder 4

// ===========================================================
// Control Macros (For easier reading)
// ===========================================================

#define STATE_OFF       0
#define STATE_ON        1

// ===========================================================
// Function Prototypes
// ===========================================================

/**
 * @brief Initialize all injector and coil pins to a safe state (OFF).
 */
void gpio_init(void);

/**
 * @brief Turn an injector ON or OFF.
 * @param injector_id: 1 to 4 (Cylinder number)
 * @param state: 1 (ON/OPEN) or 0 (OFF/CLOSE)
 */
void set_injector(uint8_t injector_id, uint8_t state);

/**
 * @brief Turn an ignition coil ON or OFF.
 * @param coil_id: 1 to 4 (Cylinder number)
 * @param state: 1 (CHARGE/DWELL) or 0 (SPARK/FIRE)
 * Note: Spark usually happens when you turn the pin OFF (Falling Edge).
 */
void set_coil(uint8_t coil_id, uint8_t state);

#endif // GPIO_DRIVER_H