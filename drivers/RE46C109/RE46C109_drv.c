/* Copyright (C) 1883 Thomas Edison - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the XYZ license, which unfortunately won't be
 * written for another century.
 *
 * You should have received a copy of the XYZ license with
 * this file. If not, please write to: , or visit :
 */

#include "RE46C109_drv.h"
#include "global.h"
#include "timer_drv.h"


/**
 * Private function definition
 **/
static void re46c109_testConfig(void);
static void re46c109_feedConfig(void);
static void re46c109_TESTClock(uint8_t clockAmount);
static void re46c109_FEEDAdjust(calibration_mode_t mode);
static void re46c109_sendData(struct re46c109_reg_t configReg);
static void re46c109_initIo(void);

static void re46c109_setTest(void);
static void re46c109_setFeed(uint8_t repeat, uint16_t duration);
static void re46c109_setIo(void);

/**
 * Global variable declaration / definition
 * */

state_t next_state = START;
calibration_mode_t calibrationMode = CAL_T1_MODE;
verification_mode_t verificationMode = VERIF_T7_MODE;
bool_t parameterIsrFlag = FALSE;
bool_t smokeCalibrationIsrFalg = FALSE;
sequence_t next_sequence = PARAMETRIC_SELECTION;


/**
 * @brief Initialize configuration register
 * */
struct re46c109_reg_t config_reg =
{
	.ltd = 0b00110,
	.ctl = 0b00000,
	.hul = 0b00000,
	.hyl = 0b00000,
	.nl = 0b00000,
	.pagf = 0b00,
	.it = 0b10,
	.irc = 0b01,
	.lb = 0b100,
	.ltde = 0b0,
	.hush = 0b0,
	.lbh = 0b0,
	.eol = 0b0,
	.ts = 0b1
};


/**
 * @brief Configure FEED, TEST2, IO and HB pins
 * @param NOne
 * @returns None
 * */
static void re46c109_testConfig(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, TEST2_PIN);
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, HB_PIN);

	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, (TEST_PIN | IO_PIN));
}

/**
 * @brief Configure FEED pin
 * @param NOne
 * @returns None
 * */
static void re46c109_feedConfig(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, FEED_PIN);
}


/**
 * @brief Configure the timer, TEST, TEST2, IO, HB, and FEED pins
 * @param None
 * @returns None
 * */
void re46c109_config(void)
{
	timer3_init();
	re46c109_testConfig();
	re46c109_feedConfig();
}



/**
 * @brief Initialize all necessary IO-Pins
 * @param None
 * @returns none
**/
static void re46c109_initIo(void)
{
	/* Set all pins to Vss */
	gpio_clear(GPIOB, (IO_PIN | TEST_PIN));
	gpio_clear(GPIOA, TEST2_PIN);
	gpio_clear(GPIOC, FEED_PIN);


	/* Set TEST2_PIN to Vdd till the end of the calibration*/
	gpio_set(GPIOA, TEST2_PIN);
	/* Setup time*/
	sleep_us(5);
}

/**
 * @brief Configure the RE46C190 by setting calibration parameters
 * @param configReg struct re46c109_reg_t configuration register for parameter to set
 * @returns None
 */
static void re46c109_sendData(struct re46c109_reg_t configReg)
{
	volatile uint16_t i;
	bool_t bitSent = FALSE;
	
	uint64_t mask = 1;//(uint64_t)pow((double)2, (double)RE46C109_REG_SIZE);
	uint64_t *data;
	data = (uint64_t *)&configReg;
	
	gpio_set(GPIOA, TEST2_PIN);
	/* 5us setup time */
	sleep_us(5);
	
	for(i = 0; i < RE46C109_REG_SIZE; i++)
	{
		bitSent = FALSE;
		while(!bitSent)
		{			
			switch(next_state)
			{
				case START:
					/* Do nothing*/
					gpio_clear(GPIOB, TEST_PIN);
					gpio_clear(GPIOC, FEED_PIN);
					next_state = SET_TEST;
					break;
				case SET_TEST:
					if((*data) & mask)
					{
						gpio_set(GPIOB, TEST_PIN);
					}
					else
					{
						gpio_clear(GPIOB, TEST_PIN);
					}
					next_state = SET_FEED;
					sleep_us(50);
					break;
				case SET_FEED:
					gpio_set(GPIOC, FEED_PIN);
					next_state = RESET_FEED;
					sleep_us(20);
					break;
				case RESET_FEED:
					gpio_clear(GPIOC, FEED_PIN);
					next_state = RESET_TEST;
					sleep_us(50);
					break;
				case RESET_TEST:
					/* Reset TEST pin only if next bit is 0*/
					mask <<= 1;
					if(((*data) & mask) != 1)
					{
						gpio_clear(GPIOB, TEST_PIN);
					}
					next_state = START;
					bitSent = TRUE;
					break;
				default:
					gpio_clear(GPIOB, TEST_PIN);
					gpio_clear(GPIOC, FEED_PIN);
					break;
			}
		}
	}

	/*Register content completely transmitted*/
	if((mask == MAX_MASK_VAL) && parameterIsrFlag)
	{
		gpio_set(GPIOB, IO_PIN);
		sleep_ms(15);
		gpio_clear(GPIOB, IO_PIN);
		gpio_clear(GPIOA, TEST2_PIN);
		sleep_ms(5);
		mask = 1;//(uint64_t)pow((double)2, (double)RE46C109_REG_SIZE);
		i = 0;
		parameterIsrFlag = FALSE;
	}
}



/**
 * @brief Set and reset TEST pin to jump into a specific calibration mode
 * @param clockAmount uint8_t how many time the clock shall be set. Corresponds
 * to the calibration mode to apply
 * @returns none
**/
static void re46c109_TESTClock(uint8_t clockAmount)
{
	uint8_t i;
	for(i = 0; i < clockAmount; i++)
	{
		gpio_set(GPIOB, TEST_PIN);
		sleep_us(150);
		gpio_clear(GPIOB, TEST_PIN);
		sleep_us(50);
	}
}

static void re46c109_setTest(void)
{
	gpio_set(GPIOB, TEST_PIN);
	sleep_us(150);
	gpio_clear(GPIOB, TEST_PIN);
}

static void re46c109_setFeed(uint8_t repeat, uint16_t duration)
{
	uint8_t i;
	
	for(i = 0; i < repeat; i++)
	{
		gpio_set(GPIOC, FEED_PIN);
		sleep_us(duration);
		gpio_clear(GPIOC, FEED_PIN);
		sleep_us(20);	
	}
}

static void re46c109_setIo(void)
{
	gpio_set(GPIOB, IO_PIN);
	sleep_ms(15);
	gpio_clear(GPIOB, IO_PIN);
}

/**
 * @brief Adjust the FEED oin depending on the mode 
 * @param mode calibration_mode_t mode to adjust
 * @returns bool_t
 * TODO: Test this and write it better if necessary 
 */
static void re46c109_FEEDAdjust(calibration_mode_t mode)
{

	if(mode != CAL_T5_MODE)
	{
		re46c109_setTest();
		sleep_us(15);
		
		re46c109_setFeed(2, 15);
		sleep_us(10);
		
		re46c109_setIo();
	}
	else
	{
		re46c109_setTest();
		sleep_us(15);
		
		re46c109_setFeed(1, 4000);
		sleep_us(10);
	}
}


/**
 * @brief Calibrate the smoke sensor individual modes 
 * @param void
 * @returns None
 * TODO: Test this and write it better if necessary 
 */
void re46c109_smokeCalibrate(void)
{
	re46c109_initIo();
	
	while(calibrationMode != CAL_MODE_END)
	{
		switch(calibrationMode)
		{
		case CAL_T1_MODE:
			re46c109_FEEDAdjust(calibrationMode);
			calibrationMode = CAL_T2_MODE;
			break;
		case CAL_T2_MODE:
			re46c109_FEEDAdjust(calibrationMode);
			calibrationMode = CAL_T3_MODE;
			break;
		case CAL_T3_MODE:
			re46c109_FEEDAdjust(calibrationMode);
			calibrationMode = CAL_T4_MODE;
			break;
		case CAL_T4_MODE:
			re46c109_FEEDAdjust(calibrationMode);
			calibrationMode = CAL_T5_MODE;
			break;
		case CAL_T5_MODE:
			re46c109_FEEDAdjust(calibrationMode);
			re46c109_setIo();
			calibrationMode = CAL_MODE_END;
			break;
		case CAL_MODE_END:
				/* The Loop shall break */
				break;
		default:
			/* Error Handling */
			gpio_clear(GPIOB, (IO_PIN | TEST_PIN));
			gpio_clear(GPIOA, TEST2_PIN);
			gpio_clear(GPIOC, FEED_PIN);
		}
	}
	gpio_clear(GPIOB, (IO_PIN | TEST_PIN));
	gpio_clear(GPIOA, TEST2_PIN);
	gpio_clear(GPIOC, FEED_PIN);
	calibrationMode = CAL_T1_MODE;
}


/**
 * @brief Configure the RE46C190 by setting calibration parameters
 * @param configReg struct re46c109_reg_t configuration register for parameter to set
 * @returns None
 */
void re46c109_runModeT0(struct re46c109_reg_t dataT0)
{
	re46c109_sendData(dataT0);
}

/**
 * @brief Enter T6 read/write mode to store specific configuration data into EEPROM
 * @param dataT6 struct re46c109_reg_t configuration register for parameter to set
 * @returns None
 */
void re46c109_runModeT6(struct re46c109_reg_t dataT6)
{
	/*Enter T6 mode by clocking Test 6 times*/
	re46c109_TESTClock(CAL_T6_MODE);
	
	sleep_us(50);
	/* Send and store serial data to EEPROM */
	re46c109_sendData(dataT6);
}


/**
 * @brief Execute test mode between T7 and T10
 * @param testMode verification_mode_t mode to select
 * @returns None
 */
void re46c109_runTest(verification_mode_t testMode)
{
	uint8_t i;
	gpio_set(GPIOA, TEST2_PIN);
	/* 5s setup time */
	sleep_us(5);
	
	/*Enter mode by clocking Test for testMode (7,..;10) times*/
	re46c109_TESTClock((uint8_t)testMode);
	sleep_us(20);
	
	for(i = 0; i < 4; i++)
	{
		gpio_set(GPIOC, FEED_PIN);
		sleep_ms(4);
		gpio_clear(GPIOC, FEED_PIN);
		sleep_ms(8);
	}
	gpio_clear(GPIOA, TEST2_PIN);
}


/**
 * @brief Operate the horn test. Observe IO pin ans well as the horn output
 * @param void
 * @returns None
 */
void re46c109_testHorn(void)
{
	gpio_set(GPIOA, TEST2_PIN);
	/* 5s setup time */
	sleep_us(5);
	
	/*Enter T11 mode by clocking Test 11 times*/
	re46c109_TESTClock(VERIF_T11_MODE);
	sleep_us(20);
	
	gpio_set(GPIOB, IO_PIN);
	sleep_ms(1);
	
	gpio_clear(GPIOB, IO_PIN);
	gpio_clear(GPIOA, TEST2_PIN);
}


void tim3_isr(void)
{
	if (timer_get_flag(TIM3, TIM_SR_UIF))
	{
		timer_clear_flag(TIM3, TIM_SR_UIF);
		parameterIsrFlag = TRUE;
	}
}



