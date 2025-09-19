#include "task_manager.h"
#include "uart_drv.h"
#include "timer_drv.h"
#include "led_driver.h"


int main(void)
{
	sleep_config();
	led_config();

	uartDevConfig(&myUartDev, MY_USART_DEVICE, uartRxBuffer, uartTxBuffer, USART_DATA_LEN);

	xTaskCreate(vledTaskHandler, "LED handler", 250, NULL, 1, NULL);

	xTaskCreate(vUartCmdTaskHandler, "Command handler", 250, NULL, 1, NULL);

	printf("Programm start\n");
	vTaskStartScheduler();
	while (1);
}
