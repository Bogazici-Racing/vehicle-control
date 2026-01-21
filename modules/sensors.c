#include "sensors.h"
#include "ecu_config.h"
#include "adc_driver.h"

// ===========================================================
// ADC Channel Mapping
// ===========================================================
// MUST match CubeMX Rank Order
#define IDX_TPS             0
#define IDX_MAP             1
#define IDX_IAT             2
#define IDX_ECT             3
#define IDX_O2              4
#define IDX_CKP             5
#define IDX_FUEL_PRESSURE   6
#define IDX_VSS             7

#define IDX_EGT             8
#define IDX_OIL_PRESSURE    9
#define IDX_OIL_TEMP        10
#define IDX_BRAKE_PRESSURE  11
#define IDX_STEERING_ANGLE  12
#define IDX_ACCEL_X         13

// ===========================================================
// Internal Storage
// ===========================================================
static SensorData sensor_data;  
static SensorOutput sensor_output;

// ===========================================================
// MANDATORY SENSORS
// ===========================================================

// TPS
uint16_t read_TPS(void){ return (uint16_t)adc_raw_buffer[IDX_TPS]; };
float convert_TPS(uint16_t val){ return (float)val * CONF_TPS_SCALE; };
float process_TPS(float val){ return val; };
float get_output_TPS(void) { return sensor_output.TPS; };

// MAP
uint16_t read_MAP(void){ return (uint16_t)adc_raw_buffer[IDX_MAP]; };
float convert_MAP(uint16_t val){ return (float)val * CONF_MAP_SCALE; };
float process_MAP(float val){ return val; };
float get_output_MAP(void) { return sensor_output.MAP; };

// IAT
uint16_t read_IAT(void){ return (uint16_t)adc_raw_buffer[IDX_IAT]; };
float convert_IAT(uint16_t val){ return (float)val * CONF_IAT_SCALE; };
float process_IAT(float val){ return val; };
float get_output_IAT(void) { return sensor_output.IAT; };

// ECT
uint16_t read_ECT(void){ return (uint16_t)adc_raw_buffer[IDX_ECT]; };
float convert_ECT(uint16_t val){ return (float)val * CONF_ECT_SCALE; };
float process_ECT(float val){ return val; };
float get_output_ECT(void) { return sensor_output.ECT; };

// O2
uint16_t read_O2(void){ return (uint16_t)adc_raw_buffer[IDX_O2]; };
float convert_O2(uint16_t val){ return (float)val * CONF_O2_SCALE; };
float process_O2(float val){ return val; };
float get_output_O2(void) { return sensor_output.O2; };

// CKP (Analog Backup)
uint16_t read_CKP(void){ return (uint16_t)adc_raw_buffer[IDX_CKP]; };
float convert_CKP(uint16_t val){ return (float)val * CONF_CKP_SCALE; };
float process_CKP(float val){ return val; };
float get_output_CKP(void) { return sensor_output.CKP; };

// Fuel Pressure
uint16_t read_FuelPressure(void){ return (uint16_t)adc_raw_buffer[IDX_FUEL_PRESSURE]; };
float convert_FuelPressure(uint16_t val){ return (float)val * CONF_FUELPRESSURE_SCALE; };
float process_FuelPressure(float val){ return val; };
float get_output_FuelPressure(void) { return sensor_output.FuelPressure; };

// VSS
uint16_t read_VSS(void){ return (uint16_t)adc_raw_buffer[IDX_VSS]; };
float convert_VSS(uint16_t val){ return (float)val * CONF_VSS_SCALE; };
float process_VSS(float val){ return val; };
float get_output_VSS(void) { return sensor_output.VSS; };

// ===========================================================
// ADVANCED SENSORS
// ===========================================================

// EGT
uint16_t read_EGT(void){ return (uint16_t)adc_raw_buffer[IDX_EGT]; };
float convert_EGT(uint16_t val){ return (float)val * CONF_EGT_SCALE; };
float process_EGT(float val){ return val; };
float get_output_EGT(void) { return sensor_output.EGT; };

// Oil Pressure
uint16_t read_OilPressure(void){ return (uint16_t)adc_raw_buffer[IDX_OIL_PRESSURE]; };
float convert_OilPressure(uint16_t val){ return (float)val * CONF_OILPRESSURE_SCALE; };
float process_OilPressure(float val){ return val; };
float get_output_OilPressure(void) { return sensor_output.OilPressure; };

// Oil Temp
uint16_t read_OilTemp(void){ return (uint16_t)adc_raw_buffer[IDX_OIL_TEMP]; };
float convert_OilTemp(uint16_t val){ return (float)val * CONF_OILTEMP_SCALE; };
float process_OilTemp(float val){ return val; };
float get_output_OilTemp(void) { return sensor_output.OilTemp; };

// Brake Pressure
uint16_t read_BrakePressure(void){ return (uint16_t)adc_raw_buffer[IDX_BRAKE_PRESSURE]; };
float convert_BrakePressure(uint16_t val){ return (float)val * CONF_BRAKE_PRESSURE_SCALE; };
float process_BrakePressure(float val){ return val; };
float get_output_BrakePressure(void) { return sensor_output.BrakePressure; };

// Steering Angle
uint16_t read_SteeringAngle(void){ return (uint16_t)adc_raw_buffer[IDX_STEERING_ANGLE]; };
float convert_SteeringAngle(uint16_t val){ return (float)val * CONF_STEERING_ANGLE_SCALE; };
float process_SteeringAngle(float val){ return val; };
float get_output_SteeringAngle(void) { return sensor_output.SteeringAngle; };

// Accel X
uint16_t read_AccelX(void){ return (uint16_t)adc_raw_buffer[IDX_ACCEL_X]; };
float convert_AccelX(uint16_t val){ return (float)val * CONF_ACCEL_X_SCALE; };
float process_AccelX(float val){ return val; };
float get_output_AccelX(void) { return sensor_output.AccelX; };

// ===========================================================
// UPDATE LOOPS
// ===========================================================

void update_mandatory_sensors(void) {
    sensor_data.TPS          = convert_TPS(read_TPS());
    sensor_data.MAP          = convert_MAP(read_MAP());
    sensor_data.IAT          = convert_IAT(read_IAT());
    sensor_data.ECT          = convert_ECT(read_ECT());
    sensor_data.O2           = convert_O2(read_O2());
    sensor_data.CKP          = convert_CKP(read_CKP());
    sensor_data.FuelPressure = convert_FuelPressure(read_FuelPressure());
    sensor_data.VSS          = convert_VSS(read_VSS());

    sensor_output.TPS          = process_TPS(sensor_data.TPS);
    sensor_output.MAP          = process_MAP(sensor_data.MAP);
    sensor_output.IAT          = process_IAT(sensor_data.IAT);
    sensor_output.ECT          = process_ECT(sensor_data.ECT);
    sensor_output.O2           = process_O2(sensor_data.O2);
    sensor_output.CKP          = process_CKP(sensor_data.CKP);
    sensor_output.FuelPressure = process_FuelPressure(sensor_data.FuelPressure);
    sensor_output.VSS          = process_VSS(sensor_data.VSS);
}

void update_advanced_sensors(void) {
    sensor_data.EGT           = convert_EGT(read_EGT());
    sensor_data.OilPressure   = convert_OilPressure(read_OilPressure());
    sensor_data.OilTemp       = convert_OilTemp(read_OilTemp());
    sensor_data.BrakePressure = convert_BrakePressure(read_BrakePressure());
    sensor_data.SteeringAngle = convert_SteeringAngle(read_SteeringAngle());
    sensor_data.AccelX        = convert_AccelX(read_AccelX());

    sensor_output.EGT           = process_EGT(sensor_data.EGT);
    sensor_output.OilPressure   = process_OilPressure(sensor_data.OilPressure);
    sensor_output.OilTemp       = process_OilTemp(sensor_data.OilTemp);
    sensor_output.BrakePressure = process_BrakePressure(sensor_data.BrakePressure);
    sensor_output.SteeringAngle = process_SteeringAngle(sensor_data.SteeringAngle);
    sensor_output.AccelX        = process_AccelX(sensor_data.AccelX);
}