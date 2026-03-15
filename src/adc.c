#include "utils.h"
#include "adc.h"
#include "gpio.h"

#define MAX_PINS 15




void init_adc(char port, uint8_t pin){

	if(pin > MAX_PINS){
		while(1){}; // Hard fault
	}

	// set pin in Analog mode
	gpio_set_mode(port, pin, 'A');

	// Activate ADC on RCC clock
  	RCC->APBENR2 |= (1U << 20);

  	// Enable voltage regulator
	ADC1->CR |= (1U << 28);

	// Wait loop
	for(unsigned int = 0; i < 100000; i++){};

	// Start calibration
	ADC1->CR |= (1U << 31);

	// Wait for calibration to end
	while(((ADC1->ISR)&(1U << 11)) == 0){};

	// Enable ADC on control register
	ADC1->CR |= (1U << 0);

	// Wait until ADC is ready (ADRDY flag in ISR)
	while(((ADC1->ISR) & (1U << 0)) == 0){};

	// Select pin
	ADC1->CHSELR |= (1U << pin);
}

uint16_t clean_adc_sampling(){
  uint32_t sum = 0;
  
  for(int i = 0; i < 16; i++){
    sum += adc_sampling();
  }
  // Divide by 4
  return (uint16_t) (sum >> 4);
}

uint16_t adc_sampling(){
	// Signal start of sampling
	ADC1->CR |= (1U << 2);
	// While ISR flag is not ready
	while(((ADC1->ISR)&(1U << 2)) == 0){};
	// Return value
	return ADC1->DR;
}