#include "gpio_driver.h"

// ===========================================================
// Pin Mapping Arrays
// ===========================================================

// We use arrays to access pins easily with an index (1, 2, 3, 4).
// Index 0 is empty (0) because cylinder numbers start at 1.

static uint16_t INJ_PINS[]  = { 0, INJ_1_PIN,  INJ_2_PIN,  INJ_3_PIN,  INJ_4_PIN  };
static uint16_t COIL_PINS[] = { 0, COIL_1_PIN, COIL_2_PIN, COIL_3_PIN, COIL_4_PIN };

// ===========================================================
// Driver Functions
// ===========================================================

void gpio_init(void) {
    // Safety First: Turn everything OFF immediately on startup.
    // This prevents flooding the engine or overheating coils if the MCU resets.
    
    for (int i = 1; i <= 4; i++) {
        set_injector(i, STATE_OFF);
        set_coil(i, STATE_OFF);
    }
}

void set_injector(uint8_t injector_id, uint8_t state) {
    // 1. Safety Check: Is the ID valid?
    if (injector_id < 1 || injector_id > 4) {
        return; // Ignore invalid IDs
    }

    // 2. Apply the state
    if (state == STATE_ON) {
        // Open the injector (Spray fuel)
        HAL_GPIO_WritePin(INJ_PORT, INJ_PINS[injector_id], GPIO_PIN_SET);
    } else {
        // Close the injector (Stop spray)
        HAL_GPIO_WritePin(INJ_PORT, INJ_PINS[injector_id], GPIO_PIN_RESET);
    }
}

void set_coil(uint8_t coil_id, uint8_t state) {
    // 1. Safety Check
    if (coil_id < 1 || coil_id > 4) {
        return;
    }

    // 2. Apply the state
    // IMPORTANT: Ignition systems usually work with "Dwell".
    // ON  = Current flows into coil (Charging)
    // OFF = Current stops -> Magnetic field collapses -> SPARK!
    
    if (state == STATE_ON) {
        // Start Dwell (Charge Coil)
        HAL_GPIO_WritePin(COIL_PORT, COIL_PINS[coil_id], GPIO_PIN_SET);
    } else {
        // Stop Dwell (Fire Spark!)
        HAL_GPIO_WritePin(COIL_PORT, COIL_PINS[coil_id], GPIO_PIN_RESET);
    }
}