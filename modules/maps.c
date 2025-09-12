#include "maps.h"
#include "sensors.h"
#include <math.h>




// ===========================================================
// STATIC MAP DATA 
// ===========================================================

// Base fuel map - Conservative starting point for Formula Student engine
static const FuelMap_t base_fuel_map = {
    // RPM axis (500 to 10000 RPM)
    .rpm_axis = {500, 750, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 9500, 10000, 10500},
    
    // Load axis (10% to 100% in steps)
    .load_axis = {25, 38, 51, 64, 77, 89, 102, 128, 153, 179, 204, 255},
    
    // Fuel values [RPM][LOAD] - pulse width in microseconds
    .fuel_values = {
        // 500 RPM row
        {800, 1000, 1200, 1400, 1600, 1800, 2000, 2400, 2800, 3200, 3600, 4000},
        // 750 RPM row  
        {700, 900, 1100, 1300, 1500, 1700, 1900, 2300, 2700, 3100, 3500, 3900},
        // Continue pattern... (simplified for prototype)
        {650, 850, 1050, 1250, 1450, 1650, 1850, 2250, 2650, 3050, 3450, 3850},
        {600, 800, 1000, 1200, 1400, 1600, 1800, 2200, 2600, 3000, 3400, 3800},
        {550, 750, 950, 1150, 1350, 1550, 1750, 2150, 2550, 2950, 3350, 3750},
        {500, 700, 900, 1100, 1300, 1500, 1700, 2100, 2500, 2900, 3300, 3700},
        {480, 680, 880, 1080, 1280, 1480, 1680, 2080, 2480, 2880, 3280, 3680},
        {460, 660, 860, 1060, 1260, 1460, 1660, 2060, 2460, 2860, 3260, 3660},
        {450, 650, 850, 1050, 1250, 1450, 1650, 2050, 2450, 2850, 3250, 3650},
        {440, 640, 840, 1040, 1240, 1440, 1640, 2040, 2440, 2840, 3240, 3640},
        {430, 630, 830, 1030, 1230, 1430, 1630, 2030, 2430, 2830, 3230, 3630},
        {420, 620, 820, 1020, 1220, 1420, 1620, 2020, 2420, 2820, 3220, 3620},
        {410, 610, 810, 1010, 1210, 1410, 1610, 2010, 2410, 2810, 3210, 3610},
        {400, 600, 800, 1000, 1200, 1400, 1600, 2000, 2400, 2800, 3200, 3600},
        {390, 590, 790, 990, 1190, 1390, 1590, 1990, 2390, 2790, 3190, 3590},
        {380, 580, 780, 980, 1180, 1380, 1580, 1980, 2380, 2780, 3180, 3580}
    }
};

// Base ignition timing map
static const IgnitionMap_t base_ignition_map = {
    // Same RPM axis as fuel map
    .rpm_axis = {500, 750, 1000, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 9500, 10000, 10500},
    
    // Same load axis as fuel map  
    .load_axis = {25, 38, 51, 64, 77, 89, 102, 128, 153, 179, 204, 255},
    
    // Timing values [RPM][LOAD] - degrees * 2 (for 0.5 degree resolution)
    .timing_values = {
        // Conservative timing for Formula Student (degrees * 2)
        {20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0, -2},     // 500 RPM
        {24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2},    // 750 RPM
        {28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6},  // 1000 RPM
        {32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10}, // 1500 RPM
        {34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12}, // 2000 RPM
        {36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14}, // 2500 RPM
        {38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16}, // 3000 RPM
        {40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18}, // 4000 RPM
        {42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20}, // 5000 RPM
        {44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22}, // 6000 RPM
        {44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22}, // 7000 RPM
        {42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20}, // 8000 RPM
        {40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18}, // 9000 RPM
        {38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16}, // 9500 RPM
        {36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14}, // 10000 RPM
        {34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12}  // 10500 RPM
    }
};

// Temperature correction maps
static const TempCorrection_t ect_correction = {
    .temp_axis = {-200, -100, 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700}, // °C * 10
    .correction_values = {200, 180, 160, 145, 135, 128, 120, 115, 110, 108, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88} // 128 = 100%
};

static const TempCorrection_t iat_correction = {
    .temp_axis = {-200, -100, 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700}, // °C * 10
    .correction_values = {120, 115, 112, 110, 108, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 86, 84, 82, 80, 78} // 128 = 100%
};

// Static variables for current operating point
static MapOutput_t current_map_output;
static uint8_t current_rpm_index = 0;
static uint8_t current_load_index = 0;

// ===========================================================
// INITIALIZATION AND VALIDATION
// ===========================================================

void maps_init(void) {
    // Initialize map output structure
    current_map_output.fuel_pulse_width = 1000;  // Safe default (1ms)
    current_map_output.ignition_timing = 20;     // Safe default (10 degrees)
    current_map_output.target_lambda = 100;      // Stoichiometric
    current_map_output.ve_value = 80;            // Conservative VE
    current_map_output.safety_cut = false;
    current_map_output.rev_limiter_active = false;
    
    // Validate map integrity on startup
    if (!maps_validate_integrity()) {
        // Handle map validation failure
        // In a real system, you'd set error flags and use safe defaults
    }
}

bool maps_validate_integrity(void) {
    // Check RPM axis is monotonically increasing
    for (uint8_t i = 1; i < FUEL_MAP_RPM_SIZE; i++) {
        if (base_fuel_map.rpm_axis[i] <= base_fuel_map.rpm_axis[i-1]) {
            return false;
        }
    }
    
    // Check load axis is monotonically increasing
    for (uint8_t i = 1; i < FUEL_MAP_LOAD_SIZE; i++) {
        if (base_fuel_map.load_axis[i] <= base_fuel_map.load_axis[i-1]) {
            return false;
        }
    }
    
    // Check for reasonable fuel values (100us to 10ms)
    for (uint8_t rpm_idx = 0; rpm_idx < FUEL_MAP_RPM_SIZE; rpm_idx++) {
        for (uint8_t load_idx = 0; load_idx < FUEL_MAP_LOAD_SIZE; load_idx++) {
            uint16_t fuel_val = base_fuel_map.fuel_values[rpm_idx][load_idx];
            if (fuel_val < 100 || fuel_val > 10000) {
                return false; // Unreasonable fuel pulse width
            }
        }
    }
    
    return true;
}

// ===========================================================
// MAIN CALCULATION FUNCTION
// ===========================================================

MapOutput_t calculate_engine_parameters(uint16_t rpm, float map_pressure, float ect, float iat) {
    MapOutput_t output = {0};
    
    // Safety checks
    if (!check_sensor_validity(map_pressure, ect, iat)) {
        output.safety_cut = true;
        return output;
    }
    
    if (!check_rpm_limits(rpm)) {
        output.rev_limiter_active = true;
        output.safety_cut = true;
        return output;
    }
    
    // Calculate engine load from MAP and RPM
    uint8_t engine_load = calculate_engine_load(map_pressure, rpm, 85); // Assume 85% VE for load calc
    
    // Lookup base fuel and ignition values
    uint16_t base_fuel = lookup_fuel_map(rpm, engine_load);
    int8_t base_timing = lookup_ignition_map(rpm, engine_load);
    uint8_t target_lambda = lookup_lambda_target(rpm, engine_load);
    
    // Apply temperature corrections
    uint16_t corrected_fuel = apply_corrections(base_fuel, ect, iat, target_lambda, 100); // Assume lambda feedback later
    
    // Fill output structure
    output.fuel_pulse_width = corrected_fuel;
    output.ignition_timing = base_timing;
    output.target_lambda = target_lambda;
    output.ve_value = lookup_ve_map(rpm, engine_load);
    output.safety_cut = false;
    output.rev_limiter_active = false;
    
    // Store for diagnostics
    current_map_output = output;
    
    return output;
}

// ===========================================================
// MAP LOOKUP FUNCTIONS
// ===========================================================

uint16_t lookup_fuel_map(uint16_t rpm, uint8_t load) {
    // Find RPM boundaries
    uint8_t rpm_index_low = 0;
    uint8_t rpm_index_high = FUEL_MAP_RPM_SIZE - 1;
    
    for (uint8_t i = 0; i < FUEL_MAP_RPM_SIZE - 1; i++) {
        if (rpm >= base_fuel_map.rpm_axis[i] && rpm < base_fuel_map.rpm_axis[i + 1]) {
            rpm_index_low = i;
            rpm_index_high = i + 1;
            break;
        }
    }
    
    // Find load boundaries
    uint8_t load_index_low = 0;
    uint8_t load_index_high = FUEL_MAP_LOAD_SIZE - 1;
    
    for (uint8_t i = 0; i < FUEL_MAP_LOAD_SIZE - 1; i++) {
        if (load >= base_fuel_map.load_axis[i] && load < base_fuel_map.load_axis[i + 1]) {
            load_index_low = i;
            load_index_high = i + 1;
            break;
        }
    }
    
    // Store current indices for diagnostics
    current_rpm_index = rpm_index_low;
    current_load_index = load_index_low;
    
    // Perform bilinear interpolation
    uint16_t f00 = base_fuel_map.fuel_values[rpm_index_low][load_index_low];
    uint16_t f01 = base_fuel_map.fuel_values[rpm_index_low][load_index_high];
    uint16_t f10 = base_fuel_map.fuel_values[rpm_index_high][load_index_low];
    uint16_t f11 = base_fuel_map.fuel_values[rpm_index_high][load_index_high];
    
    // Calculate interpolation factors (0-256 range for integer math)
    uint16_t rpm_factor = 0;
    uint16_t load_factor = 0;
    
    if (base_fuel_map.rpm_axis[rpm_index_high] != base_fuel_map.rpm_axis[rpm_index_low]) {
        rpm_factor = ((uint32_t)(rpm - base_fuel_map.rpm_axis[rpm_index_low]) * 256) / 
                     (base_fuel_map.rpm_axis[rpm_index_high] - base_fuel_map.rpm_axis[rpm_index_low]);
    }
    
    if (base_fuel_map.load_axis[load_index_high] != base_fuel_map.load_axis[load_index_low]) {
        load_factor = ((uint32_t)(load - base_fuel_map.load_axis[load_index_low]) * 256) / 
                      (base_fuel_map.load_axis[load_index_high] - base_fuel_map.load_axis[load_index_low]);
    }
    
    // Bilinear interpolation
    uint32_t temp1 = f00 + (((f10 - f00) * rpm_factor) >> 8);
    uint32_t temp2 = f01 + (((f11 - f01) * rpm_factor) >> 8);
    uint32_t result = temp1 + (((temp2 - temp1) * load_factor) >> 8);
    
    return (uint16_t)result;
}

int8_t lookup_ignition_map(uint16_t rpm, uint8_t load) {
    // Similar interpolation logic as fuel map but for ignition timing
    // Simplified for prototype - in reality you'd want the same bilinear interpolation
    
    uint8_t rpm_index = 0;
    for (uint8_t i = 0; i < IGN_MAP_RPM_SIZE - 1; i++) {
        if (rpm >= base_ignition_map.rpm_axis[i] && rpm < base_ignition_map.rpm_axis[i + 1]) {
            rpm_index = i;
            break;
        }
    }
    
    uint8_t load_index = 0;
    for (uint8_t i = 0; i < IGN_MAP_LOAD_SIZE - 1; i++) {
        if (load >= base_ignition_map.load_axis[i] && load < base_ignition_map.load_axis[i + 1]) {
            load_index = i;
            break;
        }
    }
    
    return base_ignition_map.timing_values[rpm_index][load_index];
}

uint8_t lookup_ve_map(uint16_t rpm, uint8_t load) {
    // For prototype, return a simple calculation
    // In real implementation, you'd have a proper VE map
    if (rpm < 2000) return 70;
    else if (rpm < 4000) return 85;
    else if (rpm < 7000) return 90;
    else return 80;
}

uint8_t lookup_lambda_target(uint16_t rpm, uint8_t load) {
    // Formula Student typically runs rich under load for safety
    if (load > 180) return 90;  // 0.90 lambda (rich)
    else if (load > 128) return 95;  // 0.95 lambda
    else return 100;  // 1.00 lambda (stoichiometric)
}

// ===========================================================
// CORRECTION FUNCTIONS
// ===========================================================

uint8_t get_temperature_correction(int16_t temperature, TempCorrection_t *correction_map) {
    // Find temperature boundaries and interpolate
    for (uint8_t i = 0; i < TEMP_CORR_SIZE - 1; i++) {
        if (temperature >= correction_map->temp_axis[i] && temperature < correction_map->temp_axis[i + 1]) {
            // Linear interpolation
            int32_t temp_diff = correction_map->temp_axis[i + 1] - correction_map->temp_axis[i];
            int32_t value_diff = correction_map->correction_values[i + 1] - correction_map->correction_values[i];
            int32_t temp_offset = temperature - correction_map->temp_axis[i];
            
            return correction_map->correction_values[i] + ((value_diff * temp_offset) / temp_diff);
        }
    }
    
    // Return boundary values if outside range
    if (temperature < correction_map->temp_axis[0]) {
        return correction_map->correction_values[0];
    } else {
        return correction_map->correction_values[TEMP_CORR_SIZE - 1];
    }
}

uint16_t apply_corrections(uint16_t base_fuel, float ect, float iat, uint8_t target_lambda, uint8_t actual_lambda) {
    // Get temperature corrections
    uint8_t ect_corr = get_temperature_correction((int16_t)(ect * 10), (TempCorrection_t*)&ect_correction);
    uint8_t iat_corr = get_temperature_correction((int16_t)(iat * 10), (TempCorrection_t*)&iat_correction);
    
    // Apply corrections (128 = 100%)
    uint32_t corrected_fuel = base_fuel;
    corrected_fuel = (corrected_fuel * ect_corr) >> 7;  // Divide by 128
    corrected_fuel = (corrected_fuel * iat_corr) >> 7;  // Divide by 128
    
    // Lambda correction (simplified closed loop)
    if (actual_lambda != 0 && target_lambda != 0) {
        uint32_t lambda_correction = (target_lambda * 128) / actual_lambda;
        corrected_fuel = (corrected_fuel * lambda_correction) >> 7;
    }
    
    return (uint16_t)corrected_fuel;
}

// ===========================================================
// UTILITY FUNCTIONS
// ===========================================================

uint8_t calculate_engine_load(float map_pressure, uint16_t rpm, uint8_t ve_value) {
    // Simplified load calculation based on MAP
    // Real formula: Load = (MAP / Barometric_Pressure) * VE * temperature_correction
    
    float normalized_map = map_pressure / 100.0f;  // Normalize to atmospheric (assuming 100 kPa)
    if (normalized_map > 1.0f) normalized_map = 1.0f;
    if (normalized_map < 0.1f) normalized_map = 0.1f;
    
    return (uint8_t)(normalized_map * 255.0f);
}

bool check_rpm_limits(uint16_t rpm) {
    if (rpm > MAX_RPM_LIMIT || rpm < MIN_RPM_LIMIT) {
        return false;
    }
    return true;
}

bool check_sensor_validity(float map, float ect, float iat) {
    // Check MAP sensor range
    if (map < MIN_MAP_PRESSURE || map > MAX_MAP_PRESSURE) {
        return false;
    }
    
    // Check temperature sensor ranges
    if (ect < -40.0f || ect > 150.0f) {  // Reasonable ECT range
        return false;
    }
    
    if (iat < -40.0f || iat > 100.0f) {  // Reasonable IAT range
        return false;
    }
    
    return true;
}

// ===========================================================
// CALIBRATION SUPPORT FUNCTIONS
// ===========================================================

void update_fuel_map_cell(uint8_t rpm_index, uint8_t load_index, uint16_t new_value) {
    // In a real ECU, this would update flash memory or EEPROM
    // For prototype, we can't modify const data, so this is placeholder
    // You'd implement this with a writable map overlay system
}

void update_ignition_map_cell(uint8_t rpm_index, uint8_t load_index, int8_t new_value) {
    // Same as above - placeholder for real calibration system
}

// ===========================================================
// DIAGNOSTIC FUNCTIONS
// ===========================================================

uint16_t get_current_fuel_cell_value(void) {
    if (current_rpm_index < FUEL_MAP_RPM_SIZE && current_load_index < FUEL_MAP_LOAD_SIZE) {
        return base_fuel_map.fuel_values[current_rpm_index][current_load_index];
    }
    return 0;
}

int8_t get_current_ignition_cell_value(void) {
    if (current_rpm_index < IGN_MAP_RPM_SIZE && current_load_index < IGN_MAP_LOAD_SIZE) {
        return base_ignition_map.timing_values[current_rpm_index][current_load_index];
    }
    return 0;
}