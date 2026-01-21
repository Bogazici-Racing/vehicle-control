/*
 * ECU Main Header
 * Project: Formula Student ECU
 */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* ===========================================================
 * Includes
 * =========================================================== */
#include "stm32f4xx_hal.h"

/* ===========================================================
 * Exported Types & Handles
 * =========================================================== */

// Bu tanımlar sayesinde diğer dosyalar (adc_driver vb.)
// main.c içindeki donanım yapılarına erişebilir.
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

/* ===========================================================
 * Exported Functions Prototypes
 * =========================================================== */

// Hata durumunda (Sensör hatası, DMA hatası) çağrılacak acil durum fonksiyonu
void Error_Handler(void);

// Saat ayarı (main.c içinde tanımlı)
void SystemClock_Config(void);

/* ===========================================================
 * Private Defines (Optional - CubeMX Style)
 * =========================================================== */
// Eğer LED yakacaksan pinleri buraya ekleyebilirsin
// #define LED_PIN       GPIO_PIN_12
// #define LED_PORT      GPIOD

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */