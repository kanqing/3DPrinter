#ifndef __BSP_STM32F7XX_TIM_H__
#define __BSP_STM32F7XX_TIM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
   
extern void Timer_Tick1Init(void);
extern void Timer_Tick1SetPeriod(uint32_t newTimPeriod);
extern void Timer_Tick1Start(void);   
extern void Timer_Tick1Stop(void);
__weak void StepperTimerHandle(TIM_HandleTypeDef *htim);
	 
extern void Timer_Tick2Init(void);
extern void Timer_Tick2SetPeriod(uint32_t newTimPeriod);
extern void Timer_Tick2Start(void);   
extern void Timer_Tick2Stop(void);
   
#ifdef __cplusplus
}
#endif



#endif//__BSP_STM32F7XX_TIM_H__

