#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include "ecu_config.h"


// ===========================================================
// Raw sensor data structure
// ===========================================================

typedef struct {
    // Mandatory sensors
    float TPS;
    float MAP;
    float IAT;
    float ECT;
    float O2;
    float CKP;
    float FuelPressure;
    float VSS;
    
    // Advanced sensors
    float EGT;
    float OilPressure;
    float OilTemp;
    float BrakePressure;
    float SteeringAngle;
    float AccelX;
} SensorData;








// ===========================================================
// Processed sensor output structure
// ===========================================================

typedef struct {
    // Mandatory sensors
    float TPS;
    float MAP;
    float IAT;
    float ECT;
    float O2;
    float CKP;
    float FuelPressure;
    float VSS;
    
    // Advanced sensors
    float EGT;
    float OilPressure;
    float OilTemp;
    float BrakePressure;
    float SteeringAngle;
    float AccelX;
} SensorOutput;








// ===========================================================
// Mandatory sensors
// ===========================================================

uint16_t read_TPS(void);
float convert_TPS(uint16_t adc_value);
float process_TPS(float measured_value);
float get_output_TPS(void);

uint16_t read_MAP(void);
float convert_MAP(uint16_t adc_value);
float process_MAP(float measured_value);
float get_output_MAP(void);

uint16_t read_IAT(void);
float convert_IAT(uint16_t adc_value);
float process_IAT(float measured_value);
float get_output_IAT(void);

uint16_t read_ECT(void);
float convert_ECT(uint16_t adc_value);
float process_ECT(float measured_value);
float get_output_ECT(void);

uint16_t read_O2(void);
float convert_O2(uint16_t adc_value);
float process_O2(float measured_value);
float get_output_O2(void);

uint16_t read_CKP(void);
float convert_CKP(uint16_t adc_value);
float process_CKP(float measured_value);
float get_output_CKP(void);

uint16_t read_FuelPressure(void);
float convert_FuelPressure(uint16_t adc_value);
float process_FuelPressure(float measured_value);
float get_output_FuelPressure(void);

uint16_t read_VSS(void);
float convert_VSS(uint16_t adc_value);
float process_VSS(float measured_value);
float get_output_VSS(void);








// ===========================================================
// Advanced sensors
// ===========================================================

uint16_t read_EGT(void);
float convert_EGT(uint16_t adc_value);
float process_EGT(float measured_value);
float get_output_EGT(void);

uint16_t read_OilPressure(void);
float convert_OilPressure(uint16_t adc_value);
float process_OilPressure(float measured_value);
float get_output_OilPressure(void);

uint16_t read_OilTemp(void);
float convert_OilTemp(uint16_t adc_value);
float process_OilTemp(float measured_value);
float get_output_OilTemp(void);

uint16_t read_BrakePressure(void);
float convert_BrakePressure(uint16_t adc_value);
float process_BrakePressure(float measured_value);
float get_output_BrakePressure(void);

uint16_t read_SteeringAngle(void);
float convert_SteeringAngle(uint16_t adc_value);
float process_SteeringAngle(float measured_value);
float get_output_SteeringAngle(void);

uint16_t read_AccelX(void);
float convert_AccelX(uint16_t adc_value);
float process_AccelX(float measured_value);
float get_output_AccelX(void);







// ===========================================================
// Mandatory and advanced sensors update functions
// ===========================================================

void update_mandatory_sensors(void);
void update_advanced_sensors(void);

#endif // SENSORS_H