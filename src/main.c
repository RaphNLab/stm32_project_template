#include "RE46C109_drv.h"
#include "uart_drv.h"
#include "timer_drv.h"
#include "uart_drv.h"
#include "led_driver.h"



int main(void)
{
	sleep_config();
	re46c109_config();
	led_config();

	uartDevConfig(&myUartDev, MY_USART_DEVICE, uartRxBuffer, uartTxBuffer, USART_DATA_LEN);


	while (1)
	{
		UartHandleCmd_Task(&myUartDev);
	}
	return (0);
}
