#include "sensors.h"
#include "ecu_config.h"

static SensorData sensor_data;  
static SensorOutput sensor_output;










// ===========================================================
// MANDATORY AND IMPORTANT SENSORS
// ===========================================================

// Throttle Position Sensor(Hall sensor)
uint16_t read_TPS(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_TPS(uint16_t adc_value){ return (float)adc_value * TPS_SCALE; };
float process_TPS(float measured_value){
    float processed_TPS = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_TPS;
};
float get_output_TPS(void) { return sensor_output.TPS; };



// Manifold Absolute Pressure
uint16_t read_MAP(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_MAP(uint16_t adc_value){ return (float)adc_value * MAP_SCALE; };
float process_MAP(float measured_value){
    float processed_MAP = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_MAP;
};
float get_output_MAP(void) { return sensor_output.MAP; };



// Intake Air Temperature
uint16_t read_IAT(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_IAT(uint16_t adc_value){ return (float)adc_value * IAT_SCALE; };
float process_IAT(float measured_value){
    float processed_IAT = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_IAT;
};
float get_output_IAT(void) { return sensor_output.IAT; };



// Engine Coolant Temperature
uint16_t read_ECT(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_ECT(uint16_t adc_value){ return (float)adc_value * ECT_SCALE; };
float process_ECT(float measured_value){
    float processed_ECT = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_ECT;
};
float get_output_ECT(void) { return sensor_output.ECT; };



// Oxygen (Lambda)
uint16_t read_O2(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_O2(uint16_t adc_value){ return (float)adc_value * O2_SCALE; };
float process_O2(float measured_value){
    float processed_O2 = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_O2;
};
float get_output_O2(void) { return sensor_output.O2; };



// Crankshaft Position
uint16_t read_CKP(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_CKP(uint16_t adc_value){ return (float)adc_value * CKP_SCALE; };
float process_CKP(float measured_value){
    float processed_CKP = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_CKP;
};
float get_output_CKP(void) { return sensor_output.CKP; };



// Fuel Pressure
uint16_t read_FuelPressure(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_FuelPressure(uint16_t adc_value){ return (float)adc_value * FUELPRESSURE_SCALE; };
float process_FuelPressure(float measured_value){
    float processed_FuelPressure = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_FuelPressure;
};
float get_output_FuelPressure(void) { return sensor_output.FuelPressure; };



// Vehicle Speed Sensor
uint16_t read_VSS(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_VSS(uint16_t adc_value){ return (float)adc_value * VSS_SCALE; };
float process_VSS(float measured_value){
    float processed_VSS = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_VSS;
};
float get_output_VSS(void) { return sensor_output.VSS; };









// ===========================================================
// ADVANCED AND PREFERRED SENSORS NOT MANDATORY
// ===========================================================

// Exhaust Gas Temperature
uint16_t read_EGT(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_EGT(uint16_t adc_value){ return (float)adc_value * EGT_SCALE; };
float process_EGT(float measured_value){
    float processed_EGT = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_EGT;
};
float get_output_EGT(void) { return sensor_output.EGT; };



// Oil Pressure
uint16_t read_OilPressure(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_OilPressure(uint16_t adc_value){ return (float)adc_value * OILPRESSURE_SCALE; };
float process_OilPressure(float measured_value){
    float processed_OilPressure = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_OilPressure;
};
float get_output_OilPressure(void) { return sensor_output.OilPressure; };



// Oil Temperature
uint16_t read_OilTemp(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_OilTemp(uint16_t adc_value){ return (float)adc_value * OILTEMP_SCALE; };
float process_OilTemp(float measured_value){
    float processed_OilTemp = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_OilTemp;
};
float get_output_OilTemp(void) { return sensor_output.OilTemp; };



// Brake Pressure
uint16_t read_BrakePressure(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_BrakePressure(uint16_t adc_value){ return (float)adc_value * BRAKE_PRESSURE_SCALE; };
float process_BrakePressure(float measured_value){
    float processed_BrakePressure = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_BrakePressure;
};
float get_output_BrakePressure(void) { return sensor_output.BrakePressure; };



// Steering Angle
uint16_t read_SteeringAngle(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_SteeringAngle(uint16_t adc_value){ return (float)adc_value * STEERINGANGLE_SCALE; };
float process_SteeringAngle(float measured_value){
    float processed_SteeringAngle = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_SteeringAngle;
};
float get_output_SteeringAngle(void) { return sensor_output.SteeringAngle; };



// IMU (Acceleration)
uint16_t read_AccelX(void){
    uint16_t adc_value = 0;
    return adc_value;
};
float convert_AccelX(uint16_t adc_value){ return (float)adc_value * ACCELX_SCALE; };
float process_AccelX(float measured_value){
    float processed_AccelX = measured_value; // ToDo: filtreleme, normalize vb.
    return processed_AccelX;
};
float get_output_AccelX(void) { return sensor_output.AccelX; };









// ===========================================================
// MANDATORY SENSORS UPDATE
// ===========================================================


void update_mandatory_sensors(void) {
    // Read + convert
    sensor_data.TPS          = convert_TPS(read_TPS());
    sensor_data.MAP          = convert_MAP(read_MAP());
    sensor_data.IAT          = convert_IAT(read_IAT());
    sensor_data.ECT          = convert_ECT(read_ECT());
    sensor_data.O2           = convert_O2(read_O2());
    sensor_data.CKP          = convert_CKP(read_CKP());
    sensor_data.FuelPressure = convert_FuelPressure(read_FuelPressure());
    sensor_data.VSS          = convert_VSS(read_VSS());

    // Output update (for log/summary)
    sensor_output.TPS          = process_TPS(sensor_data.TPS);
    sensor_output.MAP          = process_MAP(sensor_data.MAP);
    sensor_output.IAT          = process_IAT(sensor_data.IAT);
    sensor_output.ECT          = process_ECT(sensor_data.ECT);
    sensor_output.O2           = process_O2(sensor_data.O2);
    sensor_output.CKP          = process_CKP(sensor_data.CKP);
    sensor_output.FuelPressure = process_FuelPressure(sensor_data.FuelPressure);
    sensor_output.VSS          = process_VSS(sensor_data.VSS);
}









// ===========================================================
// ADVANCED SENSORS UPDATE
// ===========================================================


void update_advanced_sensors(void) {
    // Read + convert
    sensor_data.EGT          = convert_EGT(read_EGT());
    sensor_data.OilPressure  = convert_OilPressure(read_OilPressure());
    sensor_data.OilTemp      = convert_OilTemp(read_OilTemp());
    sensor_data.BrakePressure= convert_BrakePressure(read_BrakePressure());
    sensor_data.SteeringAngle= convert_SteeringAngle(read_SteeringAngle());
    sensor_data.AccelX       = convert_AccelX(read_AccelX());

    // Output update (for log/summary)
    sensor_output.EGT          = process_EGT(sensor_data.EGT);
    sensor_output.OilPressure  = process_OilPressure(sensor_data.OilPressure);
    sensor_output.OilTemp      = process_OilTemp(sensor_data.OilTemp);
    sensor_output.BrakePressure= process_BrakePressure(sensor_data.BrakePressure);
    sensor_output.SteeringAngle= process_SteeringAngle(sensor_data.SteeringAngle);
    sensor_output.AccelX       = process_AccelX(sensor_data.AccelX);
}
