#ifndef __FASTIO_H__
#define __FASTIO_H__

#ifdef __cplusplus
extern "C" {
#endif 
   
#include "stm32f7xx_hal.h"
  
  #define LOW   GPIO_PIN_RESET
  #define HIGH  GPIO_PIN_SET
  #define INPUT   (0)
  #define OUTPUT  (1)  
  
  extern GPIO_TypeDef * PORT_TABLE[11];
  extern uint16_t PIN_TABLE[16];

  typedef enum port_p{
    PORT_A = 'A',
    PORT_B = 'B',
    PORT_C = 'C',
    PORT_D = 'D',
    PORT_E = 'E',
    PORT_F = 'F',
    PORT_G = 'G',
    PORT_H = 'H',
    PORT_I = 'I',
    PORT_J = 'J',
    PORT_K = 'K',
  }PORT_P;
  
  typedef enum pin_p{
    PIN_0 = 0,
    PIN_1 = 1,
    PIN_2 = 2,
    PIN_3 = 3,
    PIN_4 = 4,
    PIN_5 = 5,
    PIN_6 = 6,
    PIN_7 = 7,
    PIN_8 = 8,
    PIN_9 = 9,
    PIN_10 = 10,
    PIN_11 = 11,
    PIN_12 = 12,
    PIN_13 = 13,
    PIN_14 = 14,
    PIN_15 = 15,
  }PIN_P;
  
  //#define PIN_VAL(port,pin)  (((PORT_P)(port)<<8)|pin)
  #define PIN_VAL(port,pin)  (((port)<<8)|pin)
  #define PORT_NUM(val)      PORT_TABLE[((val&0xFF00)>>8)-'A']
  #define PIN_NUM(val)       PIN_TABLE[(val&0x00FF)]
  
  void _set_io_input(GPIO_TypeDef * port, uint16_t pin);
  void _set_io_output(GPIO_TypeDef * port, uint16_t pin);

  #define pinMode(x,y)    {}    //not handled 
  

  #define _READ(IO)       HAL_GPIO_ReadPin(PORT_NUM(IO), PIN_NUM(IO))
  #define _WRITE(IO, v)   HAL_GPIO_WritePin(PORT_NUM(IO), PIN_NUM(IO), (GPIO_PinState)v)
  #define _TOGGLE(IO)     HAL_GPIO_TogglePin(PORT_NUM(IO), PIN_NUM(IO))
  /// Read a pin wrapper
  #define READ(IO)        _READ(IO)
  /// Write to a pin wrapper
  #define WRITE(IO, v)    _WRITE(IO, v)

  /// toggle a pin wrapper
  #define TOGGLE(IO)      _TOGGLE(IO)

  /// set pin as input wrapper
  #define SET_INPUT(IO)   _set_io_input(PORT_NUM(IO),PIN_NUM(IO))
  /// set pin as output wrapper
  #define SET_OUTPUT(IO)  _set_io_output(PORT_NUM(IO),PIN_NUM(IO))

  /// check if pin is an input wrapper
  #define GET_INPUT(IO)  //_GET_INPUT(IO)
  /// check if pin is an output wrapper
  #define GET_OUTPUT(IO)  //_GET_OUTPUT(IO)

  /// check if pin is an timer wrapper
  #define GET_TIMER(IO)  //_GET_TIMER(IO)

  // Shorthand
  #define OUT_WRITE(IO, v) { SET_OUTPUT(IO); WRITE(IO, v); }

  #define digitalWrite(IO,v) ((IO) > (-1))?WRITE(IO, v):(HAL_GPIO_WritePin(0,0,(GPIO_PinState)v))//will generate an assert
  #define digitalRead(IO)   ((IO) > (-1))?READ(IO):0
  
  /// external macro 
  #define _BV(bit) (1<<(bit))
  #define PROGMEM
  #define millis(x)     HAL_GetTick(x)
  #define sq(x)  (x*x)
  #define GET_CPU_FREQ()	HAL_RCC_GetSysClockFreq()
  #define F_CPU GET_CPU_FREQ()
  typedef uint8_t  boolean;
  typedef uint8_t  byte;
  #define PSTR(x)          (x)
  #define sprintf_P sprintf
  #define strcpy_P strcpy
  #define strstr_P strstr
  #define strncpy_P strncpy
  #define MCUSR 0
  #define constrain(x, a, b)  ((x) < (a))?(a):(((x) > (b))? (b) : (x))
  #define min(a,b) (((a)<(b))?(a):(b))
  #define max(a,b) (((a)>(b))?(a):(b))
  #define square(x) ((x) * (x))
  #define _delay_ms(x)      HAL_Delay(x)   
  #define delay(x)      HAL_Delay(x) 
  #define cli()       __disable_irq()
  #define sei()       __enable_irq()
  
  /* */
  #define TICK_TIMER_PRESCALER  32
  #define BSP_MiscTickSetPeriod(x)  //void(x)
#ifdef __cplusplus
}
#endif

#endif//__FASTIO_H__

