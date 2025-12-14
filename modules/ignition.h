#ifndef IGNITION_H
#define IGNITION_H

#include <stdint.h>

// ===========================================================
// Ignition Data Structure
// ===========================================================

typedef struct {
    float ignition_angle;   // Current ignition angle (degrees)
    float dwell_time;       // Ignition coil dwell time (ms)
} IgnitionData;

// ===========================================================
// Function Prototypes
// ===========================================================

// Read sensor / input values
uint16_t read_CrankAngle(void);
uint16_t read_RPM(void);

// Convert raw values to meaningful units
float convert_CrankAngle(uint16_t raw_value);
float convert_RPM(uint16_t raw_value);

// Process ignition logic (placeholder)
float process_IgnitionAngle(float angle);
float process_DwellTime(float dwell);

// Get output values
float get_output_IgnitionAngle(void);
float get_output_DwellTime(void);

// Update all ignition outputs
void update_ignition(void);

#endif // IGNITION_H
