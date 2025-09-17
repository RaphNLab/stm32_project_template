#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include "global.h"


#define TEST2_PIN GPIO1 /* PA1 */
#define TEST_PIN GPIO3 	/* PB3 */
#define FEED_PIN GPIO7 	/* PC7 */
#define IO_PIN GPIO4 	/* PB4 */
#define HB_PIN GPIO2	/* PA2 */

#define RE46C109_REG_SIZE 39U
#define MAX_MASK_VAL pow((double)2, (double)RE46C109_REG_SIZE)

struct __attribute__((packed, aligned(sizeof(uint64_t)))) re46c109_reg_t
{
	uint16_t ltd:5;  /*Long Term Drift Sample bits*/
	uint16_t ctl:5;  /*Chamber Test Limits bits*/
	uint16_t hul:5;  /*Hush limit bits*/
	uint16_t hyl:5;  /*Hysteresis Limit bits*/
	uint16_t nl:5;   /*Normal Limits bits*/
	uint16_t pagf:2; /*Photo Amplifier Gain Factor bits*/
	uint16_t it:2;   /*Integration Time bits*/
	uint16_t irc:2;  /*IRED Current bits*/
	uint16_t lb:3;   /*Low Battery Trip Point bits*/
	uint16_t ltde:1; /*Log-Term Drift Enable bit*/
	uint16_t hush:1; /* Hush Option bit*/
	uint16_t lbh:1;  /*Low Battery Hush Enable bit*/
	uint16_t eol:1;  /*End of Life Enable bit*/
	uint16_t ts:1;   /*Tone set bit*/	
};

typedef enum
{
	CAL_T1_MODE = 1,
	CAL_T2_MODE,
	CAL_T3_MODE,
	CAL_T4_MODE,
	CAL_T5_MODE,
	CAL_T6_MODE,
	CAL_MODE_END
}calibration_mode_t;


typedef enum
{
	VERIF_T7_MODE = 7,
	VERIF_T8_MODE,
	VERIF_T9_MODE,
	VERIF_T10_MODE,
	VERIF_T11_MODE,
}verification_mode_t;


typedef enum
{
	START = 0,
	SET_TEST,
	SET_FEED,
	RESET_FEED,
	RESET_TEST
}state_t;


typedef enum
{
	PARAMETRIC_SELECTION = 0,
	SMOKE_CALIBRATION,
	VERIFICATION,
	INVALID_SEQUENCE
}sequence_t;

extern struct re46c109_reg_t config_reg;
extern state_t next_state;
extern uint8_t isr_flag;


void re46c109_config(void);
void re46c109_smokeCalibrate(void);

void re46c109_runModeT0(struct re46c109_reg_t dataT0);
void re46c109_runModeT6(struct re46c109_reg_t dataT6);
void re46c109_runTest(verification_mode_t mode);
void re46c109_testHorn(void);


#endif
