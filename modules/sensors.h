#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

// ===========================================================
// Data Structures
// ===========================================================

// Ham verilerin (fiziksel birime çevrilmiş ama filtrelenmemiş) tutulduğu yapı
typedef struct {
    float TPS;          // Throttle Position (%)
    float MAP;          // Manifold Pressure (kPa)
    float IAT;          // Intake Air Temp (C)
    float ECT;          // Engine Coolant Temp (C)
    float O2;           // Lambda / AFR
    float CKP;          // Crank Position (Analog Backup)
    float FuelPressure; // Bar
    float VSS;          // Vehicle Speed (km/h)
    
    // Advanced
    float EGT;
    float OilPressure;
    float OilTemp;
    float BrakePressure;
    float SteeringAngle;
    float AccelX;
} SensorData;

// Filtrelenmiş ve mantık devresine (Logic) girmeye hazır veriler
typedef struct {
    float TPS;
    float MAP;
    float IAT;
    float ECT;
    float O2;
    float CKP;
    float FuelPressure;
    float VSS;
    
    // Advanced
    float EGT;
    float OilPressure;
    float OilTemp;
    float BrakePressure;
    float SteeringAngle;
    float AccelX;
} SensorOutput;

// ===========================================================
// Function Prototypes
// ===========================================================

// --- Update Functions (Called by Scheduler) ---
void update_mandatory_sensors(void);
void update_advanced_sensors(void);

// --- Getters (Logic modules use these) ---
float get_output_TPS(void);
float get_output_MAP(void);
float get_output_IAT(void);
float get_output_ECT(void);
float get_output_O2(void);
float get_output_CKP(void);
float get_output_FuelPressure(void);
float get_output_VSS(void);

// Advanced Getters
float get_output_EGT(void);
float get_output_OilPressure(void);
float get_output_OilTemp(void);
float get_output_BrakePressure(void);
float get_output_SteeringAngle(void);
float get_output_AccelX(void);

// --- Low Level Read/Convert (Optional Public Access) ---
uint16_t read_TPS(void);
float convert_TPS(uint16_t adc_value);
float process_TPS(float measured_value);

uint16_t read_MAP(void);
float convert_MAP(uint16_t adc_value);
float process_MAP(float measured_value);

uint16_t read_IAT(void);
float convert_IAT(uint16_t adc_value);
float process_IAT(float measured_value);

uint16_t read_ECT(void);
float convert_ECT(uint16_t adc_value);
float process_ECT(float measured_value);

uint16_t read_O2(void);
float convert_O2(uint16_t adc_value);
float process_O2(float measured_value);

uint16_t read_CKP(void);
float convert_CKP(uint16_t adc_value);
float process_CKP(float measured_value);

uint16_t read_FuelPressure(void);
float convert_FuelPressure(uint16_t adc_value);
float process_FuelPressure(float measured_value);

uint16_t read_VSS(void);
float convert_VSS(uint16_t adc_value);
float process_VSS(float measured_value);

// Advanced Prototypes
uint16_t read_EGT(void);
float convert_EGT(uint16_t val);
float process_EGT(float val);

uint16_t read_OilPressure(void);
float convert_OilPressure(uint16_t val);
float process_OilPressure(float val);

uint16_t read_OilTemp(void);
float convert_OilTemp(uint16_t val);
float process_OilTemp(float val);

uint16_t read_BrakePressure(void);
float convert_BrakePressure(uint16_t val);
float process_BrakePressure(float val);

uint16_t read_SteeringAngle(void);
float convert_SteeringAngle(uint16_t val);
float process_SteeringAngle(float val);

uint16_t read_AccelX(void);
float convert_AccelX(uint16_t val);
float process_AccelX(float val);

#endif // SENSORS_H