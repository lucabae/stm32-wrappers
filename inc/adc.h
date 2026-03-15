#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void init_adc(char port, uint8_t pin)
uint16_t clean_adc_sampling();
uint16_t adc_sampling();

#endif