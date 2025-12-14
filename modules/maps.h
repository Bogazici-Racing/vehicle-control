#ifndef MAPS_H
#define MAPS_H

#include <stdint.h>
#include "sensors.h"

// ===========================================================
// Maps Output Structure
// ===========================================================
typedef struct {
    float fuel_map_value;       // Placeholder fuel map output
    float ignition_map_value;   // Placeholder ignition map output
} MapsOutput;

// ===========================================================
// Function Prototypes
// ===========================================================

// Read map values (placeholder)
float read_fuel_map_value(float rpm, float tps);        // ToDo: use actual map later
float read_ignition_map_value(float rpm, float tps);   // ToDo: muğlak, test için placeholder

// Convert functions (minimal placeholder)
float convert_fuel_map(float raw_value);  
float convert_ignition_map(float raw_value);

// Process functions (minimal placeholder)
float process_fuel_map(float value);
float process_ignition_map(float value);

// Get output
float get_output_fuel_map(void);
float get_output_ignition_map(void);

// Update all maps
void update_maps(void);

#endif // MAPS_H
