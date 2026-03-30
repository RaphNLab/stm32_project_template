#include "led_driver.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// int main(void)
// {
// #if 0
// 	__asm volatile("LDR R1,=#0x20001000");
// 	__asm volatile("LDR R2,=#0x20001004");
// 	__asm volatile("LDR R0,[R1]");
// 	__asm volatile("LDR R1,[R2]");
// 	__asm volatile("ADD R0,R0,R1");
// 	__asm volatile("STR R0,[R2]");
// #endif

// 	/* store 'val' in to R0*/
// 	int val=50;
// 	__asm volatile("MOV R0,%0": :"r"(val));

// 	/*read CONTROL register value in to control_reg vriable */
// 	int control_reg;
// 	__asm volatile("MRS %0,CONTROL": "=r"(control_reg) );


//     /* Read the value present at pointer p2 in to p1 */
// 	int p1, *p2;
	
// 	p2 = (int*)0x20000008;

// 	__asm volatile("LDR %0,[%1]": "=r"(p1): "r"(p2));


// 	for(;;);
// 	return (0);
// }


#include<stdio.h>
#include<stdint.h>

/* This function executes in THREAD MODE of the processor */
void generate_interrupt()
{
	uint32_t *pSTIR  = (uint32_t*)0xE000EF00; //0x0000004C
	uint32_t *pISER0 = (uint32_t*)0xE000E100;

	//enable IRQ3 interrupt
	*pISER0 |= ( 1 << 3);

	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);

}

void change_access_level_unpriv(void)
{

	//read
	__asm volatile ("MRS R0,CONTROL");
	//modify
	__asm volatile ("ORR R0,R0,#0x01");
	//write
	__asm volatile ("MSR CONTROL,R0");

}

/* This function executes in THREAD MODE+ PRIV ACCESS LEVEL of the processor */
int main(void)
{
	printf("In thread mode : before interrupt\n");

	change_access_level_unpriv();

	generate_interrupt();

	printf("In thread mode : after interrupt\n");

	for(;;);
}

/* This function(ISR) executes in HANDLER MODE of the processor */
void RTC_WKUP_IRQHandler(void)
{
	printf("In handler mode : ISR\n");
}

void HardFault_Handler(void)
{
	printf("Hard fault detected\n");
	while(1);
}