#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>
#include "stm32f4xx_hal.h" // HAL Library access

// ===========================================================
// Configuration
// ===========================================================

// TODO: Check your STM32CubeMX settings! 
// This number MUST match the "Number of Conversions" in ADC settings.
// Currently counting 14 sensors from sensors.h (8 Mandatory + 6 Advanced)
#define ADC_CHANNEL_COUNT 14 

// ===========================================================
// External Buffer Access
// ===========================================================

// This array holds the raw sensor values automatically updated by DMA.
// 'extern' allows other files (like sensors.c) to read from it.
extern volatile uint32_t adc_raw_buffer[ADC_CHANNEL_COUNT];

// ===========================================================
// Function Prototypes
// ===========================================================

void adc_start(void); // Starts the ADC in DMA Circular Mode

#endif // ADC_DRIVER_H