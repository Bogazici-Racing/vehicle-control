#ifndef INJECTOR_H
#define INJECTOR_H

#include <stdint.h>
#include "ecu_config.h" 

// ===========================================================
// Injection Mapping (Redirects to Config)
// ===========================================================

// Calculate absolute Start Angles using Config values
#define INJ_1_START     (CONF_CYL1_ANGLE + CONF_INJ_START_OFFSET)
#define INJ_2_START     (CONF_CYL2_ANGLE + CONF_INJ_START_OFFSET)
#define INJ_3_START     (CONF_CYL3_ANGLE + CONF_INJ_START_OFFSET)
#define INJ_4_START     (CONF_CYL4_ANGLE + CONF_INJ_START_OFFSET)

// ===========================================================
// Data Structures
// ===========================================================

typedef struct {
    float injection_time_ms;   // Required fuel time (ms)
    float duty_cycle;          // Usage percentage
} InjectorData;

// ===========================================================
// Function Prototypes
// ===========================================================

float process_InjectionTime(void);       
float get_output_InjectionTime(void);
void update_injector(void); 

// The Fast Trigger Function
void check_injection_timing(float current_angle);

#endif // INJECTOR_H