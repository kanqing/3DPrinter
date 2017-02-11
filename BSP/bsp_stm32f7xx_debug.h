#ifndef __BSP_STM32F7XX_DEBUG_H__
#define __BSP_STM32F7XX_DEBUG_H__

#ifdef __cplusplus
extern "C"{
  #endif
  
  
  #include "stm32f7xx_hal.h"
  
  
  
  #define BSP_DBG_IO_PIN               (GPIO_PIN_3)
  #define BSP_DBG_IO_PORT              (GPIOG)
  #define BSP_DBG_IO_GPIO_CLK_ENABLE()    __GPIOG_CLK_ENABLE()
  
  extern void init_debug_io(void);
  extern void write_debug_io(GPIO_PinState level);
  extern void toggle_debug_io(void);
  
  extern void delay_debug_ms(void);
  extern void onepuls_debug_io(void);
  
  #ifdef __cplusplus
}
#endif


#endif//__BSP_STM32F7XX_DEBUG_H__

