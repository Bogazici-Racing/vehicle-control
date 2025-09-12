#ifndef ECU_CONFIG_H
#define ECU_CONFIG_H



// ===========================================================
// Sensors Configs
// ===========================================================

// Mandatory sensors scales
#define TPS_SCALE               0.1f    // ToDo: Throttle Position Sensor (percent per ADC unit)
#define MAP_SCALE               0.05f   // ToDo: Manifold Absolute Pressure (kPa per ADC unit)
#define IAT_SCALE               0.1f    // ToDo: Intake Air Temperature (°C per ADC unit)
#define ECT_SCALE               0.1f    // ToDo: Engine Coolant Temperature (°C per ADC unit)
#define O2_SCALE                0.01f   // ToDo: Oxygen sensor (lambda per ADC unit)
#define CKP_SCALE               0.01f   // ToDo: Crankshaft Position (degrees per ADC unit)
#define FUELPRESSURE_SCALE      0.02f   // ToDo: Fuel Pressure (bar per ADC unit)
#define VSS_SCALE               0.1f    // ToDo: Vehicle Speed Sensor (km/h per ADC unit)

/*
    Mandatory sensors max/min value scales for collect erorr

    ToDo
    ...
*/ 






// Advanced sensors scales
#define EGT_SCALE               0.1f    // ToDo: Exhaust Gas Temperature (°C per ADC unit)
#define OILPRESSURE_SCALE       0.05f   // TODo: Oil Pressure (bar per ADC unit)
#define OILTEMP_SCALE           0.1f    // ToDo: Oil Temperature (°C per ADC unit)
#define BRAKE_PRESSURE_SCALE    0.05f   // ToDo: Brake Pressure (bar per ADC unit)
#define STEERINGANGLE_SCALE     0.01f   // ToDo: Steering Angle (degrees per ADC unit)
#define ACCELX_SCALE            0.01f   // ToDo: Acceleration X (g per ADC unit)

/*
    Advanced sensors max/min value scales for collect erorr

    ToDo
    ...
*/ 










// ===========================================================
// Maps Configs
// ===========================================================



#endif // ECU_CONFIG_H
