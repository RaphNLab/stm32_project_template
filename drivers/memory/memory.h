/*
 * memory.h
 *
 *  Created on: Jan 16, 2025
 *      Author: silvere
 */

#ifndef DRIVERS_MEMORY_H_
#define DRIVERS_MEMORY_H_

#include "global.h"

void memCopy(uint8_t *scr, uint8_t *dest, uint8_t size);
void memErase(uint8_t *buffer, uint8_t size);
uint16_t memCRCCalc(uint8_t buffer, uint8_t size);


#endif /* DRIVERS_MEMORY_H_ */
