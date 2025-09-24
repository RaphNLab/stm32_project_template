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
		[RCC_CLOCK_VRANGE1_HSI_PLL_32MHZ]);

	led_config();

	uartDevConfig(&myUartDev, MY_USART_DEVICE, 
		uartRxBuffer, uartTxBuffer, USART_DATA_LEN);

	BaseType_t r1 = xTaskCreate(vledTaskHandler, 
		"LED handler", 250, NULL, 1, NULL);
	if (r1 != pdPASS) {
		// Task creation failed
		printf("LED Task creation failed");
	}

	BaseType_t r2 = xTaskCreate(vUartCmdTaskHandler, 
		"Command handler", 250, NULL, 1, NULL);
	if (r2 != pdPASS) {
		// Task creation failed
		printf("UART Task creation failed");
	}

	printf("CPU CLK: %ld\n", rcc_ahb_frequency);
	printf("Programm start\n");
	
	vTaskStartScheduler();

	if(xTaskGetSchedulerState() != taskSCHEDULER_RUNNING)
	{
		printf("Scheduler not started\n");
	}

	for (;;);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask 
	__attribute((unused)), char *pcTaskName __attribute((unused)))
{
    // handle error, maybe blink LED fast
	printf("Stack overflow\n");
    for (;;);
}