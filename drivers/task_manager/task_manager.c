#include "task_manager.h"
#include "uart_drv.h"
#include "led_driver.h"
//#include "timer_drv.h"

TaskHandle_t xledTaskHandle = NULL;
TaskHandle_t xuartTaskHandle = NULL;

/* Handles incoming commands over uart */
void vUartCmdTaskHandler(void *params __attribute((unused)))
{
	while(1)
	{
		UartHandleCmd_Task(&myUartDev);
	}
}


void vledTaskHandler(void *params __attribute((unused)))
{
	while(1)
	{
		gpio_toggle(PORT_LED_VERTE, LED_VERTE); //Toogle green LED
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}



