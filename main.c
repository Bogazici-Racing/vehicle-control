#include "sensors.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>  // printf için

ADC_HandleTypeDef hadc1;

int main(void)
{
    HAL_Init();
    SystemClock_Config(); // CubeMX tarafından üretilen saat ayarları
    MX_GPIO_Init();
    MX_ADC1_Init(); // hadc1 burada başlatılır

    while (1)
    {
        // 1️⃣ TPS değerini oku
        uint32_t adc_val = read_TPS();
        float tps_percent = convert_TPS(adc_val);

        // 2️⃣ Konsola yazdır (debug için)
        printf("ADC: %lu, TPS: %.2f%%\n", adc_val, tps_percent);

        HAL_Delay(100); // 100ms bekle, yoksa çok hızlı döner
    }
}
