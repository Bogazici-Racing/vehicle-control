#include "injector.h"
#include "gpio_driver.h"
#include "crank_decoder.h"

// ===========================================================
// Static Data
// ===========================================================
static InjectorData injector_output;
static float calculated_duration_ms = CONF_IDLE_FUEL_MS; // Default from Config
static float injection_duration_angle = 0.0f;

// ===========================================================
// Logic Converters
// ===========================================================

// Converts Time (ms) to Crank Angle (degrees) based on RPM.
void calculate_injection_angle_width(void) {
    float rpm = get_engine_rpm();
    
    // Safety lower limit
    if (rpm < 100.0f) rpm = 100.0f; 

    // Degrees per millisecond at current RPM
    float deg_per_ms = (rpm * 360.0f) / 60000.0f;
    
    // Update global duration in degrees
    injection_duration_angle = calculated_duration_ms * deg_per_ms;
}

// ===========================================================
// Process Functions (Slow Loop)
// ===========================================================

float process_InjectionTime(void) {
    // Placeholder: Use Configured IDLE Fuel
    // In future, you will read Maps here.
    float result = CONF_IDLE_FUEL_MS;
    
    // Update global struct
    injector_output.injection_time_ms = result;
    calculated_duration_ms = result;
    
    return result;
}

float get_output_InjectionTime(void) {
    return injector_output.injection_time_ms;
}

void update_injector(void) {
    // 1. Calculate how long to open (ms)
    process_InjectionTime();
    
    // 2. Convert to angle for the fast loop
    calculate_injection_angle_width();
}

// ===========================================================
// Trigger Logic (Fast Interrupt Loop)
// ===========================================================

void check_injection_timing(float current_angle) {
    
    // --- CYLINDER 1 ---
    float end1 = INJ_1_START + injection_duration_angle;
    // Check if we are in the window (Simple check, no wrap-around logic yet)
    if (current_angle >= INJ_1_START && current_angle < end1) {
        set_injector(1, 1); // OPEN
    } else {
        set_injector(1, 0); // CLOSE
    }

    // --- CYLINDER 2 ---
    float end2 = INJ_2_START + injection_duration_angle;
    if (current_angle >= INJ_2_START && current_angle < end2) {
        set_injector(2, 1);
    } else {
        set_injector(2, 0);
    }

    // --- CYLINDER 4 --- (Ordering follows Firing Order usually, but here checked by ID)
    float end4 = INJ_4_START + injection_duration_angle;
    if (current_angle >= INJ_4_START && current_angle < end4) {
        set_injector(4, 1);
    } else {
        set_injector(4, 0);
    }

    // --- CYLINDER 3 ---
    float end3 = INJ_3_START + injection_duration_angle;
    if (current_angle >= INJ_3_START && current_angle < end3) {
        set_injector(3, 1);
    } else {
        set_injector(3, 0);
    }
}