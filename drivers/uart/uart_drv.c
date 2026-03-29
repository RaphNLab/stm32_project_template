#include "uart_drv.h"
#include "memory.h"
/**
 * Data type, Constant and macro definitions
 *
*/


uint8_t uartRxBuffer[USART_DATA_LEN];
uint8_t uartTxBuffer[USART_DATA_LEN];

UartDev_T myUartDev;
uint8_t isrCnt = 0;

char *uartCmdList[] =
{
	"RUN_T0",  /* Run T0 for calibration */
	"RUN_T1",  /* Run T1 To set Normal Limit */
	"RUN_T2",  /* Run T2 to set Hysteresis */
	"RUN_T3",  /* Run T3 to set hush limitation */
	"RUN_T4",  /* Run T4 to set ch test limitation*/
	"RUN_T5",  /* Run T5 to run LTD baseline */
	"RUN_T6",  /* Run T6 for serial read/write */
	"RUN_T7",  /* Run T7 to perform Norm limitation check*/
	"RUN_T8",  /* Run T8 to perform Hysteresis limitation check */
	"RUN_T9",  /* Run T9 to perform Hush limitation check*/
	"RUN_T10", /* Run T10 to perform Ch Test limitation check */
	"RUN_T11", /* Run T11 to perform Horn test */
	"CALIBRATE", /* Run mode T1 to T5*/
	"HELP",
	
	"SET_LTD",  /* Long Term Drift Sample bits From 0 to 31 */ 
	"SET_CTL", 	/* Chamber Test Limits bits From 0 to 31    */
	"SET_HUL",  /* Hush Limits bits From 0 to 31 			*/
	"SET_HYL",	/* Set Hysteresis Limits bits From 0 to 31  */
	"SET_NL",	/* Set Normal Limits bits NL [From 0 to 31] */
	"SET_PAGF",	/* Set Photo Amplifier Gain Factor bits
				   0 = 1
				   1 = 2
				   2 = 3
				   3 = 4
				*/
	"SET_IT",	/* Set Integration Time bits
				   0 = 400 µs
				   1 = 300 µs
				   2 = 200 µs
				   3 = 100 µs
				*/
	"SET_IRC",	/* Set IRED Current bits
				   0 = 50 mA
				   1 = 100 mA
				   2 = 150 mA
				   3 = 200 mA
				*/
	"SET_LB",	/* Set Low Battery Trip Point 
					0 = 2.1V
					1 = 2.5V
					2 = 2.3V
					3 = 2.7V
					4 = 2.2V
					5 = 2.6V
					6 = 2.4V
					7 = 2.8V  
				*/
	"LTDE",		/* Enable/Disable Long-Term Drift Enable bit 
				   1 = Enable
				   0 = Disable
				*/ 
	"HUSH", 	/* Enable/disable
				   1 = Canceled
				   0 = Never Cancel
				*/
	"LBH", 		/* Enable/Disable Low Battery Hush 
				   1 = Enable 
				   0 = Disable
				*/
	"EOL", 		/* Enable/Disable End of Life
				   1 = Enable
				   0 = Disable
				*/
	"SET_TS"   	/* Set tone 
				   1 = Temporal Horn
				   0 = Continuous Horn 
				 */
};


/**
 * Static data declaration
 *
*/

/**
 * Private function prototypes
 *
*/
static void uartGpioSetup(void);
static void serial_debug_setup(void);




/**
 * @brief Enable and configure GPIO pins used as alternate function for RX and TX pin
 * @param None
 * */
static void uartGpioSetup(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, (GPIO2 | GPIO3));
	gpio_set_af(GPIOA, GPIO_AF7, (GPIO2 | GPIO3));
}


/**
 * @brief Configure the serial console by setting the baudrate, databits, RX/TX mode
 * 		  Enable interupt and activate the USART device
 * @param None
 * */
static void serial_debug_setup(void)
{
	rcc_periph_clock_enable(RCC_USART2);

	usart_set_parity(MY_USART_DEVICE, USART_PARITY_NONE);
	usart_set_baudrate(MY_USART_DEVICE, CONSOLE_BAUDRATE);
	usart_set_stopbits(MY_USART_DEVICE, USART_STOPBITS_1);
	usart_set_databits(MY_USART_DEVICE, CONSOLE_DATABIT);
	usart_set_flow_control(MY_USART_DEVICE, USART_FLOWCONTROL_NONE);
	usart_set_mode(MY_USART_DEVICE, USART_MODE_TX);

	/*Enable Interrupt on RX pin*/
	//usart_enable_rx_interrupt(MY_USART_DEVICE);
	//nvic_enable_irq(NVIC_USART2_IRQ);

	uartGpioSetup();
	usart_enable(MY_USART_DEVICE);
}


/**
 * @brief This function configures the UART device as well as its transmit and receive buffers
 * @param uartDev uartDev UartDev_T* pointer to USART device
 * @param uartBase uint32_t USART base address
 * @param rxBuffer uint8_t* pointer to the receive buffer
 * @param txBuffer uint8_t* pointer to the transmit buffer
 * @param size uint8_t data size
 */

void uartDevConfig(UartDev_T *uartDev, uint32_t uartBase, uint8_t *rxBuffer, uint8_t *txBuffer, uint8_t size)
{
	if(uartDev == NULL)
	{
		/* Report invalid device pointer*/
	}
	else if (txBuffer == NULL)
	{
		/* Report invalid buffer pointer*/
	}
	else if (rxBuffer == NULL)
	{
		/* Report invalid buffer pointer*/
	}
	else
	{
		uartDev->uartBase = uartBase;
		uartDev->uartRxBuffer = rxBuffer;
		uartDev->uartTxBuffer = txBuffer;
		uartDev->uartRxFlag = UART_NO_RX;
		uartDev->uartTxFlag = UART_NO_TX;
		uartDev->size = size;

		serial_debug_setup();
	}
}



/**
 * @brief USART2 interrupt service routine handling every incoming byte from the console
 * 	      Once a command is fully received a flag is set to notify.
 * */
void usart2_isr(void)
{
	volatile uint8_t rcv_char = '\0';
	if(usart_get_flag(myUartDev.uartBase, USART_SR_RXNE))
	{
		rcv_char = usart_recv(myUartDev.uartBase);

		if(rcv_char != '\r')
		{
			myUartDev.uartRxBuffer[isrCnt] = rcv_char;
			isrCnt++;
		}
		else /* If the enter character is received*/
		{
			myUartDev.uartRxFlag = UART_RX_CMP;
			isrCnt = 0;
		}
	}
}


/**
 * Private functions
 *
*/

int _write(int file, char *ptr, int len)
{
	int i;

	if (file == STDOUT_FILENO || file == STDERR_FILENO) {
		for (i = 0; i < len; i++) {
			if (ptr[i] == '\n') {
				usart_send_blocking(MY_USART_DEVICE, '\r');
			}
			usart_send_blocking(MY_USART_DEVICE, ptr[i]);
		}
		return (i);
	}
	errno = EIO;
	return (-1);
}


void printMenu(void)
{
    printf(
		  "############################################################\t\n"
          "*\tWelcome to the RE46C109 smoke sensor programmer*   *\t\n"
          "*\t- Type *HELP* to print this menu                   *\t\n"
          "############################################################\t\n"
          "\n"
          "*\t- RUN_T0  to run T0 calibration mode               *\t\n"
          "*\t- RUN_T6  to run T6 read/write mode                *\t\n"
          "*\t- RUN_T7  to run Normal Limits test mode           *\t\n"
          "*\t- RUN_T8  to run Hysteresis Limits test mode       *\t\n"
          "*\t- RUN_T9  to run Hush Limits test mode             *\t\n"
          "*\t- RUN_T10  to run Chamber Test Limits test mode    *\t\n"
          "*\t- RUN_T11  to run horn Test                        *\t\n"
          "\n############################################################\t\n"
    );
}



