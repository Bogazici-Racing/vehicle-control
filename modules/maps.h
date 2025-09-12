#ifndef MAPS_H
#define MAPS_H

#include <stdint.h>
#include <stdbool.h>
#include "ecu_config.h"

// ===========================================================
// MAP DIMENSIONS AND LIMITS
// ===========================================================

// Fuel Map Dimensions
#define FUEL_MAP_RPM_SIZE       16    // RPM axis points
#define FUEL_MAP_LOAD_SIZE      12    // Load axis points

// Ignition Map Dimensions  
#define IGN_MAP_RPM_SIZE        16    // RPM axis points
#define IGN_MAP_LOAD_SIZE       12    // Load axis points

// VE Table Dimensions (Volumetric Efficiency)
#define VE_MAP_RPM_SIZE         16    // RPM axis points
#define VE_MAP_LOAD_SIZE        12    // Load axis points

// Correction Maps
#define TEMP_CORR_SIZE          20    // Temperature correction points
#define LAMBDA_TARGET_RPM_SIZE  12    // Lambda target RPM points
#define LAMBDA_TARGET_LOAD_SIZE 8     // Lambda target Load points

// Safety Limits
#define MAX_RPM_LIMIT           10000  // Maximum allowed RPM
#define MIN_RPM_LIMIT           500    // Minimum RPM for engine operation
#define MAX_MAP_PRESSURE        250    // kPa maximum MAP sensor reading
#define MIN_MAP_PRESSURE        20     // kPa minimum MAP sensor reading

// ===========================================================
// MAP STRUCTURES
// ===========================================================

// Fuel injection map structure
typedef struct {
    uint16_t rpm_axis[FUEL_MAP_RPM_SIZE];           // RPM breakpoints
    uint8_t load_axis[FUEL_MAP_LOAD_SIZE];          // Load breakpoints (0-255 representing 0-100%)
    uint16_t fuel_values[FUEL_MAP_RPM_SIZE][FUEL_MAP_LOAD_SIZE]; // Fuel pulse width in microseconds
} FuelMap_t;

// Ignition timing map structure
typedef struct {
    uint16_t rpm_axis[IGN_MAP_RPM_SIZE];            // RPM breakpoints
    uint8_t load_axis[IGN_MAP_LOAD_SIZE];           // Load breakpoints (0-255)
    int8_t timing_values[IGN_MAP_RPM_SIZE][IGN_MAP_LOAD_SIZE]; // Timing advance in degrees * 2 (for 0.5 degree resolution)
} IgnitionMap_t;

// Volumetric Efficiency map structure
typedef struct {
    uint16_t rpm_axis[VE_MAP_RPM_SIZE];             // RPM breakpoints
    uint8_t load_axis[VE_MAP_LOAD_SIZE];            // Load breakpoints (0-255)
    uint8_t ve_values[VE_MAP_RPM_SIZE][VE_MAP_LOAD_SIZE]; // VE values (0-255 representing 0-200%)
} VEMap_t;

// Temperature correction structure
typedef struct {
    int16_t temp_axis[TEMP_CORR_SIZE];              // Temperature breakpoints in °C * 10
    uint8_t correction_values[TEMP_CORR_SIZE];      // Correction factor (128 = 100%, 0-255 range)
} TempCorrection_t;

// Lambda target map
typedef struct {
    uint16_t rpm_axis[LAMBDA_TARGET_RPM_SIZE];      // RPM breakpoints
    uint8_t load_axis[LAMBDA_TARGET_LOAD_SIZE];     // Load breakpoints
    uint8_t lambda_values[LAMBDA_TARGET_RPM_SIZE][LAMBDA_TARGET_LOAD_SIZE]; // Target lambda * 100
} LambdaTargetMap_t;

// ===========================================================
// INTERPOLATION RESULTS
// ===========================================================

typedef struct {
    uint16_t fuel_pulse_width;      // Calculated fuel pulse width (microseconds)
    int8_t ignition_timing;         // Calculated ignition timing (degrees * 2)
    uint8_t target_lambda;          // Target lambda value * 100
    uint8_t ve_value;               // Volumetric efficiency value
    bool safety_cut;                // Safety cut flag
    bool rev_limiter_active;        // Rev limiter flag
} MapOutput_t;

// ===========================================================
// FUNCTION PROTOTYPES
// ===========================================================

// Map initialization
void maps_init(void);
bool maps_validate_integrity(void);

// Main map lookup functions
MapOutput_t calculate_engine_parameters(uint16_t rpm, float map_pressure, float ect, float iat);

// Individual map lookups
uint16_t lookup_fuel_map(uint16_t rpm, uint8_t load);
int8_t lookup_ignition_map(uint16_t rpm, uint8_t load);
uint8_t lookup_ve_map(uint16_t rpm, uint8_t load);
uint8_t lookup_lambda_target(uint16_t rpm, uint8_t load);

// Correction functions
uint8_t get_temperature_correction(int16_t temperature, TempCorrection_t *correction_map);
uint16_t apply_corrections(uint16_t base_fuel, float ect, float iat, uint8_t target_lambda, uint8_t actual_lambda);

// Utility functions
uint8_t calculate_engine_load(float map_pressure, uint16_t rpm, uint8_t ve_value);
uint16_t interpolate_2d(uint16_t *x_axis, uint8_t *y_axis, uint16_t **values, 
                        uint8_t x_size, uint8_t y_size, uint16_t x_input, uint8_t y_input);

// Safety functions
bool check_rpm_limits(uint16_t rpm);
bool check_sensor_validity(float map, float ect, float iat);

// Calibration support (for tuning)
void update_fuel_map_cell(uint8_t rpm_index, uint8_t load_index, uint16_t new_value);
void update_ignition_map_cell(uint8_t rpm_index, uint8_t load_index, int8_t new_value);

// Diagnostic functions
void get_map_statistics(void);
uint16_t get_current_fuel_cell_value(void);
int8_t get_current_ignition_cell_value(void);

#endif // MAPS_H