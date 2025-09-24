#include "led_driver.h"


/**
 * Data type, Constant and macro definitions
 *
*/

/**
 * Static data declaration
 *
*/

/**
 * Private function prototypes
 *
*/

/**
 * Public functions
 *
*/
void led_config(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(PORT_LED_VERTE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_VERTE);
}


/**
 * Private functions
 *
*/

