#ifndef CRANK_DECODER_H
#define CRANK_DECODER_H

#include <stdint.h>
#include "ecu_config.h" // Access to CONF_CRANK_TEETH_COUNT

// ===========================================================
// Decoder State Structure
// ===========================================================

typedef struct {
    float current_angle;        // Engine position (0.0 - 720.0 degrees)
    float engine_rpm;           // Calculated RPM
    uint16_t current_tooth;     // Current tooth index
    uint8_t is_synced;          // 1: Trusted (Synced), 0: Not synced
    
    // Internal timing variables for RPM calculation
    uint32_t last_pulse_time;
    uint32_t current_pulse_time;
} DecoderState;

// Global access to engine state
extern volatile DecoderState engine_state;

// ===========================================================
// Function Prototypes
// ===========================================================

void decoder_init(void);
void decoder_on_tooth_signal(void); // Called by Interrupt
float get_engine_rpm(void);

#endif // CRANK_DECODER_H