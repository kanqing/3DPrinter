
/* Includes ------------------------------------------------------------------*/
#include "user_utility.h"
#include "bsp_stm32f7xx_adc.h"

//#include "stm32f4xx_3dprinter_misc.h"

/* Private defines ----------------------------------------------------------*/
/* Private constant ----------------------------------------------------------*/
#define ADC_ERROR_TAG        (0x2000)
//#define ADC_ERROR(error)     BSP_MiscErrorHandler(error|ADC_ERROR_TAG)

#define BSP_ADC_CONVERTED_VALUES_BUFFER_SIZE (6)
    
/* Global variables ---------------------------------------------------------*/
BspAdcDataType gBspAdcData;

/* Private variables */
__IO uint16_t   aBspAdcConvertedValues[BSP_ADC_CONVERTED_VALUES_BUFFER_SIZE];

/* Extern function -----------------------------------------------------------*/

/******************************************************//**
 * @brief  ADC Hw initialisation
 * @param None
 * @retval None
 **********************************************************/
void BSP_AdcHwInit(void)
{
  BspAdcDataType *pAdc = &gBspAdcData;
  
  ADC_ChannelConfTypeDef sConfig;
  pAdc->acquisitionDone = RESET;
    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  pAdc->adcHandle.Instance = BSP_ADC_MARLIN;
  pAdc->adcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
  pAdc->adcHandle.Init.Resolution = ADC_RESOLUTION10b;
  pAdc->adcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  pAdc->adcHandle.Init.ScanConvMode = ENABLE;
  pAdc->adcHandle.Init.EOCSelection = EOC_SEQ_CONV;
  pAdc->adcHandle.Init.ContinuousConvMode = ENABLE;
  pAdc->adcHandle.Init.NbrOfConversion = BSP_ADC_CONVERTED_VALUES_BUFFER_SIZE;
  pAdc->adcHandle.Init.DiscontinuousConvMode = DISABLE;
  pAdc->adcHandle.Init.NbrOfDiscConversion = 1;
  pAdc->adcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  pAdc->adcHandle.Init.DMAContinuousRequests = ENABLE;
  
    
  if (HAL_ADC_Init(&pAdc->adcHandle) != HAL_OK)
  {
    /* ADC initialization error */
    ADC_ERROR(1);
  }

  /* Configure ADC for bed thermistor */
  sConfig.Channel = BSP_ADC_MARLIN_CHANNEL_THERM_BED1;
  sConfig.Rank = BSP_ADC_MARLIN_RANK_THERM_BED1;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&pAdc->adcHandle, &sConfig) != HAL_OK)
  {
    /* Channel configuration error */
    ADC_ERROR(2);
  }

  /* Configure ADC for E1 thermistor */
  sConfig.Channel = BSP_ADC_MARLIN_CHANNEL_THERM_E1;
  sConfig.Rank = BSP_ADC_MARLIN_RANK_THERM_E1;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&pAdc->adcHandle, &sConfig) != HAL_OK)
  {
    /* Channel configuration error */
    ADC_ERROR(3);
  }
  
  /* Configure ADC for E2 thermistor */
  sConfig.Channel = BSP_ADC_MARLIN_CHANNEL_THERM_E2;
  sConfig.Rank = BSP_ADC_MARLIN_RANK_THERM_E2;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&pAdc->adcHandle, &sConfig) != HAL_OK)
  {
    /* Channel configuration error */
    ADC_ERROR(4);
  }

   /* Configure ADC for E3 thermistor */
  sConfig.Channel = BSP_ADC_MARLIN_CHANNEL_THERM_E3;
  sConfig.Rank = BSP_ADC_MARLIN_RANK_THERM_E3;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&pAdc->adcHandle, &sConfig) != HAL_OK)
  {
    /* Channel configuration error */
    ADC_ERROR(5);
  }

   /* Configure ADC for BED2 thermistor */
  sConfig.Channel = BSP_ADC_MARLIN_CHANNEL_THERM_BED2;
  sConfig.Rank = BSP_ADC_MARLIN_RANK_THERM_BED2;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&pAdc->adcHandle, &sConfig) != HAL_OK)
  {
    /* Channel configuration error */
    ADC_ERROR(6);
  }
  
   /* Configure ADC for BED3*/
  sConfig.Channel = BSP_ADC_MARLIN_CHANNEL_THERM_BED3;
  sConfig.Rank = BSP_ADC_MARLIN_RANK_THERM_BED3;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&pAdc->adcHandle, &sConfig) != HAL_OK)
  {
    /* Channel configuration error */
    ADC_ERROR(7);
  }  

  /* Start conversion */
  if (HAL_ADC_Start_DMA(&pAdc->adcHandle,
                        (uint32_t *)aBspAdcConvertedValues, 
                         BSP_ADC_CONVERTED_VALUES_BUFFER_SIZE)   != HAL_OK)  
  {
      ADC_ERROR(8);
  } 
    
}


/******************************************************//**
 * @brief  Conversion complete callback in non blocking mode
 * @param hadc: ADC handle
 * @retval None
 **********************************************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
  BspAdcDataType *pAdc = &gBspAdcData;
  /* Report to main program that ADC sequencer has reached its end */
  pAdc->acquisitionDone = SET;
}

/******************************************************//**
 * @brief  Conversion DMA half-transfer callback in non blocking mode 
 * @param hadc: ADC handle
 * @retval None
 **********************************************************/
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
  
}

/******************************************************//**
 * @brief  DC error callback in non blocking mode
 *        (ADC conversion with interruption or transfer by DMA)
 * @param hadc: ADC handle
 * @retval None
 **********************************************************/
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* In case of ADC error, call main error handler */
  ADC_ERROR(9);
}

/******************************************************//**
 * @brief  ADC Hw initialisation
 * @param rankId: rank ok the analog pin to read 
 * (see BSP_ADC_RANK_... values)
 * @retval None
 **********************************************************/
uint16_t BSP_AdcGetValue(uint8_t rankId)
{
  BspAdcDataType *pAdc = &gBspAdcData;
  if (pAdc->acquisitionDone == RESET)
  {
      ADC_ERROR(10);
  }
  return (aBspAdcConvertedValues[rankId]);
}

void ADC_ERROR(uint32_t nb)
{
  printf("ADC_ERROR::[N%d]\r\n",nb);
  Error_Handler();
}
