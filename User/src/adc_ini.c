#include "adc_ini.h"

void ADC_ini(GPIO_TypeDef* GPIOPORT, uint16_t Pin)
{
	ADC_InitTypeDef ADC_module;
	
	GPIO_ini(GPIOPORT, Pin, AN);
	
	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	
	 /* Initialize the ADC_Mode member */
  ADC_module.ADC_Resolution = ADC_Resolution_12b;

  /* initialize the ADC_ScanConvMode member */
  ADC_module.ADC_ScanConvMode = ENABLE;

  /* Initialize the ADC_ContinuousConvMode member */
  ADC_module.ADC_ContinuousConvMode = DISABLE;

  /* Initialize the ADC_ExternalTrigConvEdge member */
  ADC_module.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_module.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;

  /* Initialize the ADC_DataAlign member */
  ADC_module.ADC_DataAlign = ADC_DataAlign_Right;

  /* Initialize the ADC_NbrOfConversion member */
  ADC_module.ADC_NbrOfConversion = 2;
	
	
	ADC_Init(ADC1, &ADC_module);
	ADC_Init(ADC2, &ADC_module);
	ADC_Init(ADC3, &ADC_module);

	ADC_InjectedSequencerLengthConfig(ADC1, 2);
	ADC_InjectedSequencerLengthConfig(ADC2, 2);
	ADC_InjectedSequencerLengthConfig(ADC3, 2);
	
	ADC_InjectedChannelConfig (ADC1, ADC_Channel_11, 1, ADC_SampleTime_56Cycles);
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_56Cycles);
	ADC_InjectedChannelConfig (ADC2, ADC_Channel_13, 1, ADC_SampleTime_56Cycles);
	ADC_InjectedChannelConfig(ADC2, ADC_Channel_14, 2, ADC_SampleTime_56Cycles);
	ADC_InjectedChannelConfig (ADC3, ADC_Channel_15, 1, ADC_SampleTime_56Cycles);
	ADC_InjectedChannelConfig(ADC3, ADC_Channel_10, 2, ADC_SampleTime_56Cycles);
	
	 NVIC_EnableIRQ(ADC_IRQn);
	 
	 ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
	 ADC_ITConfig(ADC2, ADC_IT_JEOC, ENABLE);
	 ADC_ITConfig(ADC3, ADC_IT_JEOC, ENABLE);
	
	ADC_Cmd (ADC1, ENABLE);
	ADC_Cmd (ADC2, ENABLE);
	ADC_Cmd (ADC3, ENABLE);
	
}
