#include "task_manager.h"
#include "uart_drv.h"
//#include "timer_drv.h"
#include "led_driver.h"

#include "task.h"

extern void vApplicationStackOverflowHook(TaskHandle_t xTask
	 __attribute((unused)), char *pcTaskName __attribute((unused)));

int main(void)
{
 	rcc_clock_setup_pll(&rcc_clock_config
		[RCC_CLOCK_VRANGE1_HSI_PLL_24MHZ]);

	led_config();

	uartDevConfig(&myUartDev, MY_USART_DEVICE, 
		uartRxBuffer, uartTxBuffer, USART_DATA_LEN);

	vInitTask();
	
	vTaskStartScheduler();

	for (;;);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask 
	__attribute((unused)), char *pcTaskName __attribute((unused)))
{
    for (;;);
}