#ifndef __BSP_EEPROM_H__
#define __BSP_EEPROM_H__

#ifdef __cplusplus 
extern "C"{
#endif
	
#include "stm32f7xx_hal.h"

__weak uint8_t 	eeprom_read_byte (const uint8_t *__p);
__weak uint16_t	eeprom_read_word (const uint16_t *__p);
__weak uint32_t	eeprom_read_dword (const uint32_t *__p);
__weak float	eeprom_read_float (const float *__p);
__weak void 	eeprom_read_block (void *__dst, const void *__src, size_t __n);
__weak void 	eeprom_write_byte (uint8_t *__p, uint8_t __value);
__weak void 	eeprom_write_word (uint16_t *__p, uint16_t __value);
__weak void 	eeprom_write_dword (uint32_t *__p, uint32_t __value);
__weak void 	eeprom_write_float (float *__p, float __value);
__weak void 	eeprom_write_block (const void *__src, void *__dst, size_t __n);
__weak void 	eeprom_update_byte (uint8_t *__p, uint8_t __value);
__weak void 	eeprom_update_word (uint16_t *__p, uint16_t __value);
__weak void 	eeprom_update_dword (uint32_t *__p, uint32_t __value);
__weak void 	eeprom_update_float (float *__p, float __value);
__weak void 	eeprom_update_block (const void *__src, void *__dst, size_t __n);
	
#ifdef __cplusplus 
}
#endif
	
#endif//__BSP_EEPROM_H__

