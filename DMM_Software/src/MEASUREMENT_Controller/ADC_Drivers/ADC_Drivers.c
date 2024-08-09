#include "ADC_Drivers.h"
#include "stm32f407xx.h"

#define INIT_SAMPLE_SIZE 1000

static uint32_t ADC1_sampleSize = INIT_SAMPLE_SIZE;

//	INTERNAL DRIVER FUNCTIONS	///////////////////////////////////////////////////////////////////////////////////////////

// run ADC 1 conversion
// returns result register value
static uint32_t ADC1_run(void) {
	// Start conversion (bit is cleared after conversion begins)
	ADC1->CR2 |= ADC_CR2_SWSTART;
	
	// Wait till end of conversion flag
	while (!(ADC1->SR & ADC_SR_EOC)) {}
	return ADC1->DR;
}


// run x conversions on ADC 1
// returns averaged result register value
static double ADC1_convert(void) {
	double sampleTotal = 0;
	
	// take x samples
	for (uint32_t i = 0; i < ADC1_sampleSize; ++i) {
		sampleTotal += ADC1_run();
	}
	
	// return averaged result
	return sampleTotal / ADC1_sampleSize;
}


// Set ADC input to input n
static void ADC1_setInput(uint32_t n) {
	ADC1->SQR3 = (ADC1->SQR3 & ~ADC_SQR3_SQ1_Msk) | (n << ADC_SQR3_SQ1_Pos);
}


// Calibrate ADC 1
// Measure temperature regulated voltage reference
// Multiply register result by this reference to get the true voltage
// takes a uint32_t x which is the number of sample to run during calibration
static double ADC1_getCalibratedReference(void) {
	double calibratedReference;
	
	// Set input to reference channel (input 17)
	ADC1_setInput(17);
	
	// Enable regulated voltage
	ADC->CCR |= ADC_CCR_TSVREFE;
	
	calibratedReference = 1.212 / ADC1_convert();
	
	// Disable regulated voltage
	ADC->CCR &= ~ADC_CCR_TSVREFE;
	
	return calibratedReference;
}


//	EXTERNAL DRIVER FUNCTIONS	///////////////////////////////////////////////////////////////////////////////////////////


// Initialise ADC 1
// Sets PC4 and PC5 configuration registers to analog input
// Sets ADC 1 configuration registers and enables ADC 1
void ADC1_init(void) {
	// enable clock to port C
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 
	
	// Set config register to MODER = "11", PUPDR = "00"
	// PC4 = ADC12_Input14
	GPIOC->MODER |= 0x03 << GPIO_MODER_MODER4_Pos; 
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD4_Msk;
	
	// PC5 = ADC12_Input15
	GPIOC->MODER |= 0x03 << GPIO_MODER_MODER5_Pos; 
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD5_Msk;
	
	// disable clock to port C to save power
	RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN; 
	
	
	// CONFIGURE ADC
	// Enable clock to ADC 1
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// Set ADC 1 input to 14 for first conversion
	// (only need first as we do one conversion at a time)
  ADC1_setInput(14);
		
	// Enable ADC
	ADC1->CR2 |= ADC_CR2_ADON;
	
	// Set ADC to discontinuous mode
	ADC1->CR1 |= ADC_CR1_DISCEN;
	
	// Enable end-of-conversion Flag
	ADC1->CR2 |= ADC_CR2_EOCS;
	
	// Set sampling time
	ADC1->SMPR2 = (ADC1->SMPR2 & ~ADC_SMPR2_SMP1_Msk) | (0x07 << ADC_SMPR2_SMP1_Pos);
}


// converts input n of the ADC to voltage
// takes ADC input n of type uint
// returns calibrated conversion as double in Volts
double ADC1_getConversion(uint32_t n) {
	// note: calibration must happen BEFORE changing input
	double calibrationReference = ADC1_getCalibratedReference();
	ADC1_setInput(n);
	return ADC1_convert() * calibrationReference;
}


void ADC1_setSampleSize(uint32_t n) {
	ADC1_sampleSize = n;
}


// resets sample size to init value
void ADC1_resetSampleSize(void) {
	ADC1_sampleSize = INIT_SAMPLE_SIZE;
}
