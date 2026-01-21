#include "exti_driver.h"
#include "crank_decoder.h" // Access to the brain logic

// ===========================================================
// Interrupt Callback (The Bridge)
// ===========================================================

/**
 * @brief  EXTI Line detection callback.
 * This function is called AUTOMATICALLY by HAL when an interrupt occurs.
 * @param  GPIO_Pin: Specifies the pins connected to the EXTI line.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // Check if the interrupt comes from the Crank Sensor Pin
    if (GPIO_Pin == CRANK_SENSOR_PIN) {
        
        // 1. Hardware Signal Received!
        // 2. Notify the Decoder Module immediately.
        decoder_on_tooth_signal();
        
        // NOTE: Keep this function short. No printf, no heavy delays.
    }
}