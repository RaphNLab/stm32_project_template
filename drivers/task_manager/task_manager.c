#include "task_manager.h"
#include "uart_drv.h"
#include "led_driver.h"


QueueHandle_t uart_txq; // UART transmit queue


static void vUartSendTask(void *params __attribute((unused)));
static void usart_puts(char *buf);
static void vTestUsart(void *params __attribute((unused)));
static void vLedTaskHandler(void *params __attribute((unused)));

static void vUartSendTask(void *params __attribute((unused)))
{
	char c;

	while(1)
	{
		if(xQueueReceive(uart_txq, &c, 500) == pdPASS)
		{
			while(!usart_get_flag(myUartDev.uartBase, USART_SR_TXE))
			{
				taskYIELD();
			}
			usart_send(myUartDev.uartBase, c);
		}
	}
}

static void usart_puts(char *buf)
{
	for( ; *buf; ++buf)
	{
		xQueueSend(uart_txq, buf, portMAX_DELAY);
	}
}

static void vTestUsart(void *params __attribute((unused)))
{
	while(1)
	{
		usart_puts("This is a message ...\n\r");
		usart_puts(" from RAPNLAB with FreeRTOS queues.\n\n\r");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


static void vLedTaskHandler(void *params __attribute((unused)))
{
	while(1)
	{
		gpio_toggle(GREEN_LED_PORT, GREEN_LED_PIN); //Toogle green LED
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void vInitTask(void)
{
	uart_txq = xQueueCreate(500, sizeof(char));

	xTaskCreate(vLedTaskHandler, "LED handler", 250, NULL, 1, NULL);
	xTaskCreate(vUartSendTask, "Send char", 250, NULL, 1, NULL);
	xTaskCreate(vTestUsart, "Send text", 250, NULL, 1, NULL);
}

