#include "task_manager.h"
#include "uart_drv.h"
#include "timer_drv.h"
#include "led_driver.h"




int main(void)
{
	sleep_config();
	led_config();

	uartDevConfig(&myUartDev, MY_USART_DEVICE, uartRxBuffer, uartTxBuffer, USART_DATA_LEN);

	xTaskCreate(vUartCmdTaskHandler, "Command handler", 500, NULL, 2, &xuartTaskHandle);

	while (1);
}
