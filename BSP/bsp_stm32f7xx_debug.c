#include "bsp_stm32f7xx_debug.h"

void init_debug_io(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  BSP_DBG_IO_GPIO_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = BSP_DBG_IO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(BSP_DBG_IO_PORT, &GPIO_InitStruct);
  
  write_debug_io(GPIO_PIN_RESET); 
}


void write_debug_io(GPIO_PinState level)
{
  HAL_GPIO_WritePin(BSP_DBG_IO_PORT, BSP_DBG_IO_PIN, level); 
}

void toggle_debug_io(void)
{
  HAL_GPIO_TogglePin(BSP_DBG_IO_PORT, BSP_DBG_IO_PIN); 
}

void onepuls_debug_io(void)
{
  uint32_t i;
  write_debug_io(GPIO_PIN_SET);
//  for(i = 0; i < 0x100; i++)
//  {
//    __nop();//asm("nop");
//  }
  write_debug_io(GPIO_PIN_RESET);
}


void delay_debug_ms(void)
{
  uint32_t i = 0;
  for(i = 0; i < 0x19000; i++)
  {
    __nop();//asm("nop");
  }
}

