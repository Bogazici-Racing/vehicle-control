#ifndef INJECTOR_H
#define INJECTOR_H

#include <stdint.h>
#include "sensors.h"

// ===========================================================
// Injector Data Structure
// ===========================================================
typedef struct {
    float injection_time;   // Calculated injection time (ms)
    float pulse_width;      // Injector pulse width (ms)
} InjectorData;

// ===========================================================
// Function Prototypes
// ===========================================================
float process_InjectionTime(void);         // Calculate injection time using sensor outputs (placeholder)
float process_PulseWidth(float injection_time);  // Convert injection time to pulse width (placeholder)

float get_output_InjectionTime(void);
float get_output_PulseWidth(void);

void update_injector(void); // Read sensors and update injector output

#endif // INJECTOR_H
