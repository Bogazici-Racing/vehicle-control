/*
 * ECU Configuration Master File
 * Project: Formula Student ECU
 * Description: Central file for ALL engine settings, hardware params, and tuning.
 */

#ifndef ECU_CONFIG_H
#define ECU_CONFIG_H

// ===========================================================
// SECTION 1: ENGINE PHYSICAL PROPERTIES
// ===========================================================

// Engine Geometry
#define CONF_CYLINDER_COUNT         4       // Number of cylinders
#define CONF_DISPLACEMENT_CC        599.0f  // Total engine volume (CBR600RR ~599cc)

// Crank Trigger Wheel Setup
// Honda CBR 600 RR is typically 12 teeth.
#define CONF_CRANK_TEETH_COUNT      12      
#define CONF_CRANK_ANGLE_PER_TOOTH  (360.0f / CONF_CRANK_TEETH_COUNT) // Auto-calc: 30 deg

// ===========================================================
// SECTION 2: FIRING ORDER & TIMING
// ===========================================================
// CBR 600 RR Firing Order: 1-2-4-3
// Defines at which angle the POWER stroke begins.

#define CONF_CYL1_ANGLE             0.0f
#define CONF_CYL2_ANGLE             180.0f
#define CONF_CYL4_ANGLE             360.0f
#define CONF_CYL3_ANGLE             540.0f

// ===========================================================
// SECTION 3: INJECTION SETTINGS
// ===========================================================

// Injection Timing Offset
// 0.0 means injection calculation starts exactly at the cycle start logic.
#define CONF_INJ_START_OFFSET       0.0f 

// Tuning: Fuel Amounts (Pulse Width in ms)
// Default fallback values if maps are not ready.
#define CONF_CRANKING_FUEL_MS       5.0f    // Fuel when starting (RPM < 400)
#define CONF_IDLE_FUEL_MS           2.5f    // Fuel at idle

// ===========================================================
// SECTION 4: IGNITION SETTINGS
// ===========================================================

// Coil Charging Time (Dwell)
// WARNING: Do not exceed 3.5ms for stick coils!
#define CONF_COIL_DWELL_MS          3.0f

// Base Timing Fallback (Safety)
#define CONF_IGNITION_BASE_ANGLE    10.0f   // 10 degrees BTDC

// ===========================================================
// SECTION 5: SAFETY LIMITS
// ===========================================================

#define CONF_REV_LIMIT_RPM          13500.0f // Cut fuel above this
#define CONF_MAX_COOLANT_TEMP       115.0f   // Emergency mode temp

// ===========================================================
// SECTION 6: SENSOR CALIBRATION (SCALES)
// ===========================================================
// Formula: Real_Value = ADC_Value * SCALE
// ADC is 12-bit (0-4095)

// Mandatory Sensors
#define CONF_TPS_SCALE              0.0244f // 100% / 4095
#define CONF_MAP_SCALE              0.0732f // 300kPa / 4095
#define CONF_IAT_SCALE              0.1f
#define CONF_ECT_SCALE              0.1f
#define CONF_O2_SCALE               0.01f
#define CONF_FUELPRESSURE_SCALE     0.02f
#define CONF_VSS_SCALE              0.1f
#define CONF_CKP_SCALE              1.0f    // Not typically used for analog reading

// Advanced Sensors
#define CONF_EGT_SCALE              0.25f
#define CONF_OILPRESSURE_SCALE      0.05f
#define CONF_OILTEMP_SCALE          0.1f
#define CONF_BRAKE_PRESSURE_SCALE   0.05f
#define CONF_STEERING_ANGLE_SCALE   0.1f
#define CONF_ACCEL_X_SCALE          0.01f

#endif // ECU_CONFIG_H