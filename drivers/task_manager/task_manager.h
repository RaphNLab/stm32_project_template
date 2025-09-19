/*
 * task_manager.h
 *
 *  Created on: Mar 23, 2023
 *      Author: silvere
 */

#include "global.h"

#ifndef INCLUDES_TASK_MANAGER_H_
#define INCLUDES_TASK_MANAGER_H_

extern TaskHandle_t xledTaskHandle;
extern TaskHandle_t xuartTaskHandle;

typedef enum
{
	ACCELEROMETER_TASK = 0,
	GYROSCOPE_TASK,
	TEMPERATURE_TASK,
	DEFAULT_TASK
}TaskType_T;


/* functions prototypes */
void vUartCmdTaskHandler(void *params);
void vledTaskHandler(void *params);

#endif /* INCLUDES_TASK_MANAGER_H_ */
