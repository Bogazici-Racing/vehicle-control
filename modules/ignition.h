#ifndef IGNITION_H
#define IGNITION_H

#include <stdint.h>
#include "ecu_config.h"

// ===========================================================
// Data Structure
// ===========================================================

typedef struct {
    float ignition_angle;   // Target timing (degrees)
    float dwell_time;       // Coil charge time (ms)
} IgnitionData;

// ===========================================================
// Function Prototypes
// ===========================================================

void update_ignition(void);
void check_ignition_timing(float current_angle);

float get_output_IgnitionAngle(void);
float get_output_DwellTime(void);

#endif // IGNITION_H