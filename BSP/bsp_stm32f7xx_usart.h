#ifndef __BSP_STM32F7XX_USART_H__
#define __BSP_STM32F7XX_USART_H__


#ifdef __cplusplus
  extern "C" {
#endif
    

   /* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
   
/* Exported macros ------------------------------------------------------------*/
#define UART_TX_BUFFER_SIZE (2048)
#define UART_RX_BUFFER_SIZE (2048)
   
/* Definition for Usart resources *********************************************/

#define BSP_UART_MARLIN                           (USART6)
#define __BSP_UART_MARLIN_CLK_ENABLE()              __USART6_CLK_ENABLE()
#define __BSP_UART_MARLIN_CLK_DISABLE()             __USART6_CLK_DISABLE()
#define __BSP_UART_MARLIN_RX_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE()
#define __BSP_UART_MARLIN_TX_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE()

#define __BSP_UART_MARLIN_FORCE_RESET()             __USART6_FORCE_RESET()
#define __BSP_UART_MARLIN_RELEASE_RESET()           __USART6_RELEASE_RESET()

/* Definition for BSP_UART_MARLIN Pins */
#define BSP_UART_MARLIN_TX_PIN               (GPIO_PIN_6)
#define BSP_UART_MARLIN_TX_PORT              (GPIOC)
#define BSP_UART_MARLIN_RX_PIN               (GPIO_PIN_7)
#define BSP_UART_MARLIN_RX_PORT              (GPIOC)

/* Definition for BSP_UART_MARLIN's NVIC */
#define BSP_UART_MARLIN_IRQn                      (USART6_IRQn)
#define BSP_UART_MARLIN_IRQHandler                USART6_IRQHandler   

#define BSP_UART_MARLIN_TX_AF                     (GPIO_AF8_USART6)
#define BSP_UART_MARLIN_RX_AF                     (GPIO_AF8_USART6)
   
/* Exported types --- --------------------------------------------------------*/
typedef struct BspUartDataTag
{
  volatile uint8_t rxWriteChar;
  uint8_t *pRxBuffer;
  volatile uint8_t *pRxWriteBuffer;
  volatile uint8_t *pRxReadBuffer;
  uint8_t *pTxBuffer;
  volatile uint8_t *pTxWriteBuffer;
  volatile uint8_t *pTxReadBuffer;
  volatile uint8_t *pTxWrap;
  volatile uint8_t newTxRequestInThePipe;
  volatile uint8_t gCodeDataMode;
  volatile uint16_t nbTxBytesOnGoing;
  volatile ITStatus rxBusy;
  volatile ITStatus txBusy;
  void (*uartRxDataCallback)(uint8_t *,uint8_t);  
  void (*uartTxDoneCallback)(void);  
  UART_HandleTypeDef handle;
  uint32_t debugNbRxFrames; 
  uint32_t debugNbTxFrames;
  volatile uint32_t nbBridgedBytes;
}BspUartDataType;

/* Exported variables  --------------------------------------------------------*/
extern BspUartDataType gBspUartData;

/* Exported functions --------------------------------------------------------*/
uint8_t* BSP_UartIfGetFreeTxBuffer(void);
void BSP_UartHwInit(uint32_t newBaudRate);
void BSP_UartIfStart(void);
void BSP_UartIfQueueTxData(uint8_t *pBuf, uint8_t nbData);
void BSP_UartIfSendQueuedData(void);
void BSP_UartAttachRxDataHandler(void (*callback)(uint8_t *, uint8_t));
void BSP_UartAttachTxDoneCallback(void (*callback)(void));
uint32_t BSP_UartPrintf(const char* format,...);
uint32_t BSP_UartGetNbRxAvalaibleBytes(void);
int8_t BSP_UartGetNextRxBytes(void);
uint8_t BSP_UartIsTxOnGoing(void);
uint32_t BSP_UartCommandsFilter(char *pBufCmd, uint8_t nxRxBytes);

void BSP_UartLockingTx(uint8_t *pBuf, uint8_t nbData);    
extern void UART_ERROR(uint32_t nb);    

#ifdef __cplusplus
}
#endif


#endif//__BSP_STM32F7XX_USART_H__

