#ifndef SERIAL_DRIVER_H_
#define SERIAL_DRIVER_H_

#include "global.h"
#include <libopencm3/stm32/usart.h>

/*User defines*/
#define SERIAL_BUF_SIZE			1024U
#define SERIAL_MAX_SATA_SIZE	SERIAL_BUF_SIZE
#define SERIAL_DATA_REG			(0x40004400U + 0x04U)

#define MY_USART_DEVICE			USART2
#define CONSOLE_BAUDRATE 		9600U
#define CONSOLE_DATABIT			8U
#define USART_DATA_LEN			20U



/*User  Typedef and enum */

#define AT_CMD(action,  status) "AT+CMD" #action " " #status

typedef enum
{
	RUN_T0 = 0,
	RUN_T1,
	RUN_T2,
	RUN_T3,
	RUN_T4,
	RUN_T5,
	RUN_T6,
	RUN_T7,
	RUN_T8,
	RUN_T9,
	RUN_T10,
	RUN_T11,
	CALIBRATE,
	HELP,
	SET_LTD,
	SET_CTL,
	SET_HUL,
	SET_HYL,
	SET_NL,
	SET_PAGF,
	SET_IT,
	SET_IRC,
	SET_LB,
	LTDE,
	HUSH,
	LBH,
	EOL,
	SET_TS,
	INVALID
}UartAtCmd_t;


typedef enum
{
	UART_RX_CMP = 0,
	UART_TX_CMP,
	UART_NO_RX,
	UART_NO_TX
}UartItFlag_T;


/*User global variables*/


/*User global functions*/
int _write(int file, char *ptr, int len);

typedef struct
{
	uint32_t uartBase;
	uint8_t *uartRxBuffer;
	uint8_t *uartTxBuffer;
	UartItFlag_T uartRxFlag;
	UartItFlag_T uartTxFlag;
	uint8_t size;
}UartDev_T;

extern uint8_t uartRxBuffer[USART_DATA_LEN];
extern uint8_t uartTxBuffer[USART_DATA_LEN];

extern UartDev_T myUartDev;
extern char *uartCmdList[];

void uartDevConfig(UartDev_T *uartDev, uint32_t uartBase, uint8_t *rxBuffer, uint8_t *txBuffer, uint8_t size);
void UartHandleCmd_Task(UartDev_T *uartDev);
void printMenu(void);


#endif
