#include "ignition.h"
#include "gpio_driver.h"
#include "ecu_config.h"
#include <math.h> // For fabs()

// ===========================================================
// Static Data
// ===========================================================

static IgnitionData ignition_output;
// Default target from Config
static float target_firing_angle = CONF_IGNITION_BASE_ANGLE; 

// ===========================================================
// Update Logic (Slow Loop)
// ===========================================================

void update_ignition(void) {
    // Placeholder: Keep using Base Angle defined in Config
    // In future: Read Map -> Update target_firing_angle
    
    ignition_output.ignition_angle = target_firing_angle;
    ignition_output.dwell_time = CONF_COIL_DWELL_MS;
}

float get_output_IgnitionAngle(void) {
    return ignition_output.ignition_angle;
}

float get_output_DwellTime(void) {
    return ignition_output.dwell_time;
}

// ===========================================================
// Trigger Logic (Fast Interrupt Loop)
// ===========================================================

void check_ignition_timing(float current_angle) {
    
    float tolerance = 2.0f; // Degree window

    // --- CYLINDER 1 ---
    // Target is Base Angle (e.g., 10 deg) relative to TDC
    // Note: This logic assumes simple single-cylinder like behavior for test.
    // Real implementation needs individual targets for Cyl 2, 3, 4 based on offsets.
    
    if (fabs(current_angle - target_firing_angle) < tolerance) {
        set_coil(1, 0); // FIRE! (Spark on Falling Edge)
    }
    
    // For now, only Cyl 1 is active in this simplified logic.
    // To enable others, check against (CONF_CYL2_ANGLE - target) etc.
}