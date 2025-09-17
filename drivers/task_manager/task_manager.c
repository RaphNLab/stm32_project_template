#include "task_manager.h"
#include "uart_drv.h"

TaskHandle_t xuartTaskHandle = NULL;


/* Handles incoming commands over uart */
void vUartCmdTaskHandler(void *params)
{
	while(1)
	{
		UartHandleCmd_Task(&myUartDev);
	}
}




