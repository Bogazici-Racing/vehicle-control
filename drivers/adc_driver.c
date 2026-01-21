#include "adc_driver.h"
#include "main.h" // To access 'hadc1' and 'Error_Handler'

// ===========================================================
// Buffer Definition
// ===========================================================

// The actual memory storage for sensor data
volatile uint32_t adc_raw_buffer[ADC_CHANNEL_COUNT] = {0};

// ===========================================================
// External Handles
// ===========================================================

// Defined in main.c by STM32CubeMX
extern ADC_HandleTypeDef hadc1; 

// ===========================================================
// Driver Functions
// ===========================================================

/**
 * @brief Starts the ADC peripheral in DMA Circular Mode.
 * This allows reading sensors in the background without CPU intervention.
 */
void adc_start(void) {
    // Start ADC conversion with DMA
    // - &hadc1: The ADC handle
    // - adc_raw_buffer: Where to save the data
    // - ADC_CHANNEL_COUNT: How many channels to scan
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_raw_buffer, ADC_CHANNEL_COUNT) != HAL_OK) {
        // If starting fails, go to Error Handler
        Error_Handler();
    }
}