#include "maps.h"

// ===========================================================
// Static data
// ===========================================================
static MapsOutput maps_output;

// Placeholder tables (sonradan değiştirilebilir)
static float fuel_map_table[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };        // RPM x TPS
static float ignition_map_table[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };    // RPM x TPS

// ===========================================================
// Read functions (placeholder)
// ===========================================================
float read_fuel_map_value(float rpm, float tps) {
    // Placeholder: seçilen index basit floor veya round
    int rpm_idx = 0;   // ToDo: implement index lookup
    int tps_idx = 0;   // ToDo: implement index lookup
    float value = fuel_map_table[rpm_idx][tps_idx]; 
    return value; // placeholder
}

float read_ignition_map_value(float rpm, float tps) {
    int rpm_idx = 0;    // ToDo: implement proper indexing
    int tps_idx = 0;    // ToDo: muğlak, placeholder
    float value = ignition_map_table[rpm_idx][tps_idx];
    return value;
}

// ===========================================================
// Convert functions (minimal placeholder)
// ===========================================================
float convert_fuel_map(float raw_value) {
    float val = raw_value; // ToDo: scale conversion if needed
    return val;
}

float convert_ignition_map(float raw_value) {
    float val = raw_value; // ToDo: scale conversion if needed
    return val;
}

// ===========================================================
// Process functions (minimal placeholder)
// ===========================================================
float process_fuel_map(float value) {
    float processed = value; // minimal placeholder
    maps_output.fuel_map_value = processed;
    return processed;
}

float process_ignition_map(float value) {
    float processed = value; // minimal placeholder
    maps_output.ignition_map_value = processed;
    return processed;
}

// ===========================================================
// Get output functions
// ===========================================================
float get_output_fuel_map(void) {
    return maps_output.fuel_map_value;
}

float get_output_ignition_map(void) {
    return maps_output.ignition_map_value;
}

// ===========================================================
// Update all maps
// ===========================================================
void update_maps(void) {
    // Read sensor outputs
    float rpm = get_output_CKP();  // CKP used as RPM placeholder
    float tps = get_output_TPS();

    // Read maps
    float fuel_raw = read_fuel_map_value(rpm, tps);
    float ign_raw  = read_ignition_map_value(rpm, tps);

    // Convert
    float fuel_conv = convert_fuel_map(fuel_raw);
    float ign_conv  = convert_ignition_map(ign_raw);

    // Process
    process_fuel_map(fuel_conv);
    process_ignition_map(ign_conv);
}
