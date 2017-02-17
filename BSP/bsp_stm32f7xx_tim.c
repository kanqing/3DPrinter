#include "bsp_stm32f7xx_tim.h"
#include "bsp_stm32f7xx_debug.h"

/// Timer handler for tick
TIM_HandleTypeDef hTimTick1;

/*##-1- Configure the TIM peripheral #######################################*/
  /* -----------------------------------------------------------------------
    In this example TIM1 input clock (TIM1CLK)  is set to APB2 clock (PCLK2) x2,
    since APB2 prescaler is equal to 2.
      TIM1CLK = PCLK2
      PCLK2 = HCLK
      => TIM1CLK = HCLK = SystemCoreClock
    To get TIM1 counter clock at 20 KHz, the Prescaler is computed as follows:
    Prescaler = (TIM1CLK / TIM3 counter clock) - 1
    Prescaler = ((SystemCoreClock) /20 KHz) - 1

    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f7xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  ----------------------------------------------------------------------- */

void Timer_Tick1Init(void)
{
  TIM_ClockConfigTypeDef	sClockSourceConfig;
  TIM_OC_InitTypeDef sConfigOC;
  //TIM_OnePulse_InitTypeDef sConfigOC;
  TIM_MasterConfigTypeDef sMasterConfig;
  
  uint32_t PrescalerValue = 0;
  
  /* Set Interrupt Group Priorit of Timer Interrupt*/ 
  HAL_NVIC_SetPriority(TIM1_CC_IRQn, 6, 0);

  /* Enable the timer global Interrupt */
  HAL_NVIC_EnableIRQ(TIM1_CC_IRQn); 
  
  __TIM1_CLK_ENABLE();

  //²ÎÕÕMarlin´úÂë£¬AVR2560 16MHzOSC 8 Divide Freq = 2MHz
  PrescalerValue = (uint16_t) ((HAL_RCC_GetSysClockFreq()) / 2000000) - 1;

  hTimTick1.Instance = TIM1;
	hTimTick1.Init.Prescaler = PrescalerValue;//32 - 1;
	hTimTick1.Init.CounterMode = TIM_COUNTERMODE_UP;
	if( hTimTick1.Instance == TIM2 )		
    hTimTick1.Init.Period = 0xffffffff;
	else if( hTimTick1.Instance == TIM5 )	
    hTimTick1.Init.Period = 0xffffffff;
	else									
    hTimTick1.Init.Period = 0xffff;
	hTimTick1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_OC_Init(&hTimTick1);
	//HAL_TIM_OnePulse_Init(&hTimTick1,TIM_OPMODE_REPETITIVE);
  //HAL_TIM_OnePulse_Init(&hTimTick1, TIM_OPMODE_REPETITIVE);//TIM_OPMODE_SINGLE);
  
	sConfigOC.OCMode = TIM_OCMODE_TIMING;//TIM_OCMODE_TOGGLE;//sConfigOC.OCMode = TIM_OCMODE_TIMING;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; 
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.Pulse = 0;
	HAL_TIM_OC_ConfigChannel(&hTimTick1, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_OC_ConfigChannel(&hTimTick1, &sConfigOC, TIM_CHANNEL_2);
 // TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef* sConfig, uint32_t OutputChannel,  uint32_t InputChannel
  //HAL_TIM_OnePulse_ConfigChannel(&hTimTick1, &sConfigOC, TIM_CHANNEL_1,TIM_CHANNEL_2);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&hTimTick1, &sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&hTimTick1, &sMasterConfig);
  Timer_Tick1SetPeriod(1000);
  Timer_Tick1Start();
  //HAL_TIM_OnePulse_Start(&hTimTick1, TIM_CHANNEL_1);
}


/****************************************************************
 * @FunName	: Timer_Tick1SetPeriod()
 * @Brief	: Sets the frequency of PWM_X used by device 0.
 * @Para	: newPeriod - In seconds.
 * @Return	: None.
****************************************************************/
void Timer_Tick1SetPeriod(uint32_t newTimPeriod)
{
	uint32_t timerCnt = hTimTick1.Instance->CNT + newTimPeriod;
	__HAL_TIM_SetCompare(&hTimTick1, TIM_CHANNEL_1, timerCnt-80);
  __HAL_TIM_SetCompare(&hTimTick1, TIM_CHANNEL_2, timerCnt-78);
}


/****************************************************************
 * @FunName	: Timer_Tick1Start()
 * @Brief	: Tick1 start work.
 * @Para	: None.
 * @Return	: None.
****************************************************************/
void Timer_Tick1Start(void)
{
	HAL_TIM_OC_Start_IT(&hTimTick1, TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&hTimTick1, TIM_CHANNEL_2);
}


/****************************************************************
 * @FunName	: Timer_Tick1Stop()
 * @Brief	: Stop the PWM used for the tick.
 * @Para	: None.
 * @Return	: None.
****************************************************************/
void Timer_Tick1Stop(void)
{
	HAL_TIM_OC_Stop_IT(&hTimTick1, TIM_CHANNEL_1);	
  HAL_TIM_OC_Stop_IT(&hTimTick1, TIM_CHANNEL_2);
//	bspTickEnabled = 0;
}

void Timer_Tick2Init(void)
{

}

void Timer_Tick2SetPeriod(uint32_t newTimPeriod)
{
	
}

void Timer_Tick2Start(void)
{
	
}

void Timer_Tick2Stop(void)
{
	
}

/****************************************************************
 * @FunName	: HAL_TIM_OC_DelayElapsedCallback()
 * @Brief	: Output Compare callback in non blocking mode.
 * @Para	: htim - pointer to a TIM_HandleTypeDef structure that
 *						contains the configuration information for TIM module.
 * @Return	: None.
****************************************************************/
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM1)
  {
    //toggle_debug_io();
    if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
    {
      write_debug_io(GPIO_PIN_SET);
    }
    else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
    {
      write_debug_io(GPIO_PIN_RESET);
      Timer_Tick1SetPeriod(2000);
    }
    StepperTimerHandle(htim);
	}
}

void TIM1_CC_IRQHandler(void)
{
  HAL_NVIC_ClearPendingIRQ(TIM1_CC_IRQn);
  HAL_TIM_IRQHandler(&hTimTick1);
  //toggle_debug_io();
}

__weak void StepperTimerHandle(TIM_HandleTypeDef *htim)
{
  UNUSED(htim);
}
