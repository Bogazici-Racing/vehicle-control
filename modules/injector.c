#include "injector.h"

// ===========================================================
// Static data
// ===========================================================
static InjectorData injector_output;

// ===========================================================
// Process functions (placeholder)
// ===========================================================
float process_InjectionTime(void) {
    // Placeholder: read sensor outputs
    float tps   = get_output_TPS();         // Throttle Position
    float map   = get_output_MAP();         // Manifold Absolute Pressure
    float rpm   = get_output_CKP();         // Crankshaft Position used as RPM placeholder
    float ect   = get_output_ECT();         // Engine Coolant Temperature
    float fuel_pressure = get_output_FuelPressure();

    // Placeholder calculation: sum of inputs as dummy logic
    float injection_time = tps + map + rpm + ect + fuel_pressure; 
    injector_output.injection_time = injection_time; 
    return injection_time;
}

float process_PulseWidth(float injection_time) {
    // Placeholder: direct mapping
    float pulse = injection_time; // ToDo: implement PWM mapping if needed
    injector_output.pulse_width = pulse;
    return pulse;
}

// ===========================================================
// Get output functions
// ===========================================================
float get_output_InjectionTime(void) {
    return injector_output.injection_time;
}

float get_output_PulseWidth(void) {
    return injector_output.pulse_width;
}

// ===========================================================
// Update injector outputs
// ===========================================================
void update_injector(void) {
    float inj_time = process_InjectionTime();
    process_PulseWidth(inj_time);
}
