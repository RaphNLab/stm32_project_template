   1              		.cpu cortex-m7
   2              		.eabi_attribute 28, 1	@ Tag_ABI_VFP_args
   3              		.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
   4              		.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
   5              		.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
   6              		.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
   7              		.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
   8              		.eabi_attribute 26, 1	@ Tag_ABI_enum_size
   9              		.eabi_attribute 30, 6	@ Tag_ABI_optimization_goals
  10              		.eabi_attribute 34, 1	@ Tag_CPU_unaligned_access
  11              		.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
  12              		.file	"systick.c"
  13              	@ GNU C99 (15:10.3-2021.07-4) version 10.3.1 20210621 (release) (arm-none-eabi)
  14              	@	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl v
  15              	
  16              	@ GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
  17              	@ options passed: 
  18              	@ -I /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/global
  19              	@ -I /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/gpio
  20              	@ -I /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/memory
  21              	@ -I /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick
  22              	@ -I /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/libopencm3/include
  23              	@ -imultilib thumb/v7e-m+dp/hard
  24              	@ -MD CMakeFiles/arm_cortex_m4_test.elf.dir/drivers/systick/systick.c.d
  25              	@ -MF CMakeFiles/arm_cortex_m4_test.elf.dir/drivers/systick/systick.c.obj.d
  26              	@ -MT CMakeFiles/arm_cortex_m4_test.elf.dir/drivers/systick/systick.c.obj
  27              	@ -D__USES_INITFINI__ -D STM32F7
  28              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c
  29              	@ -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb
  30              	@ -mlibarch=armv7e-m+fp.dp -march=armv7e-m+fp.dp
  31              	@ -auxbase-strip CMakeFiles/arm_cortex_m4_test.elf.dir/drivers/systick/systick.c.obj
  32              	@ -g3 -g -O0 -Wall -Wextra -std=c99 -fdata-sections -ffunction-sections
  33              	@ -ffreestanding -fverbose-asm
  34              	@ options enabled:  -faggressive-loop-optimizations -fallocation-dce
  35              	@ -fauto-inc-dec -fdata-sections -fdelete-null-pointer-checks
  36              	@ -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
  37              	@ -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
  38              	@ -ffunction-sections -fgcse-lm -fgnu-unique -fident -finline-atomics
  39              	@ -fipa-stack-alignment -fira-hoist-pressure -fira-share-save-slots
  40              	@ -fira-share-spill-slots -fivopts -fkeep-static-consts
  41              	@ -fleading-underscore -flifetime-dse -fmath-errno -fmerge-debug-strings
  42              	@ -fpeephole -fplt -fprefetch-loop-arrays -freg-struct-return
  43              	@ -fsched-critical-path-heuristic -fsched-dep-count-heuristic
  44              	@ -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
  45              	@ -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
  46              	@ -fsched-stalled-insns-dep -fsemantic-interposition -fshow-column
  47              	@ -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
  48              	@ -fssa-backprop -fstdarg-opt -fstrict-volatile-bitfields -fsync-libcalls
  49              	@ -ftrapping-math -ftree-cselim -ftree-forwprop -ftree-loop-if-convert
  50              	@ -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
  51              	@ -ftree-parallelize-loops= -ftree-phiprop -ftree-reassoc -ftree-scev-cprop
  52              	@ -funit-at-a-time -fverbose-asm -fzero-initialized-in-bss
  53              	@ -masm-syntax-unified -mbe32 -mlittle-endian -mpic-data-is-text-relative
  54              	@ -msched-prolog -mthumb -munaligned-access -mvectorize-with-neon-quad
  55              	
  56              		.text
  57              	.Ltext0:
  58              		.cfi_sections	.debug_frame
  59              		.global	system_millis
  60              		.section	.bss.system_millis,"aw",%nobits
  61              		.align	2
  64              	system_millis:
  65 0000 00000000 		.space	4
  66              		.section	.text.msleep,"ax",%progbits
  67              		.align	1
  68              		.global	msleep
  69              		.arch armv7e-m
  70              		.syntax unified
  71              		.thumb
  72              		.thumb_func
  73              		.fpu fpv5-d16
  75              	msleep:
  76              	.LFB3:
  77              		.file 1 "/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c"
   1:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /*
   2:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * systick.c
   3:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
   4:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *  Created on: 28 Apr 2020
   5:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *      Author: silvere
   6:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  */
   7:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
   8:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** #include <libopencm3/stm32/timer.h>
   9:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** #include <libopencm3/cm3/systick.h>
  10:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** #include <stdio.h>
  11:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  12:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** #include "systick.h"
  13:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  14:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  15:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /**
  16:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * Data type, Constant and macro definitions
  17:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
  18:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** */
  19:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  20:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /**
  21:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * Static data declaration
  22:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
  23:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** */
  24:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /* monotonically increasing number of milliseconds from reset
  25:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * overflows every 49 days if you're wondering
  26:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  */
  27:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** volatile uint32_t system_millis;
  28:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  29:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /**
  30:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * Private function prototypes
  31:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
  32:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** */
  33:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  34:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /**
  35:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * Public functions
  36:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
  37:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** */
  38:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /* sleep for delay milliseconds */
  39:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** void msleep(uint32_t delay)
  40:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** {
  78              		.loc 1 40 1
  79              		.cfi_startproc
  80              		@ args = 0, pretend = 0, frame = 16
  81              		@ frame_needed = 1, uses_anonymous_args = 0
  82              		@ link register save eliminated.
  83 0000 80B4     		push	{r7}	@
  84              		.cfi_def_cfa_offset 4
  85              		.cfi_offset 7, -4
  86 0002 85B0     		sub	sp, sp, #20	@,,
  87              		.cfi_def_cfa_offset 24
  88 0004 00AF     		add	r7, sp, #0	@,,
  89              		.cfi_def_cfa_register 7
  90 0006 7860     		str	r0, [r7, #4]	@ delay, delay
  91              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:41: 	uint
  41:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	uint32_t wake = system_millis + delay;
  92              		.loc 1 41 32
  93 0008 084B     		ldr	r3, .L3	@ tmp115,
  94 000a 1B68     		ldr	r3, [r3]	@ system_millis.0_1, system_millis
  95              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:41: 	uint
  96              		.loc 1 41 11
  97 000c 7A68     		ldr	r2, [r7, #4]	@ tmp117, delay
  98 000e 1344     		add	r3, r3, r2	@ tmp116, tmp117
  99 0010 FB60     		str	r3, [r7, #12]	@ tmp116, wake
 100              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:42: 	whil
  42:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	while (wake > system_millis);
 101              		.loc 1 42 8
 102 0012 00BF     		nop	
 103              	.L2:
 104              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:42: 	whil
 105              		.loc 1 42 14 discriminator 1
 106 0014 054B     		ldr	r3, .L3	@ tmp118,
 107 0016 1B68     		ldr	r3, [r3]	@ system_millis.1_2, system_millis
 108              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:42: 	whil
 109              		.loc 1 42 8 discriminator 1
 110 0018 FA68     		ldr	r2, [r7, #12]	@ tmp119, wake
 111 001a 9A42     		cmp	r2, r3	@ tmp119, system_millis.1_2
 112 001c FAD8     		bhi	.L2		@,
 113              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:43: }
  43:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** }
 114              		.loc 1 43 1
 115 001e 00BF     		nop	
 116 0020 00BF     		nop	
 117 0022 1437     		adds	r7, r7, #20	@,,
 118              		.cfi_def_cfa_offset 4
 119 0024 BD46     		mov	sp, r7	@,
 120              		.cfi_def_cfa_register 13
 121              		@ sp needed	@
 122 0026 5DF8047B 		ldr	r7, [sp], #4	@,
 123              		.cfi_restore 7
 124              		.cfi_def_cfa_offset 0
 125 002a 7047     		bx	lr	@
 126              	.L4:
 127              		.align	2
 128              	.L3:
 129 002c 00000000 		.word	system_millis
 130              		.cfi_endproc
 131              	.LFE3:
 133              		.section	.text.systick_ms_setup,"ax",%progbits
 134              		.align	1
 135              		.global	systick_ms_setup
 136              		.syntax unified
 137              		.thumb
 138              		.thumb_func
 139              		.fpu fpv5-d16
 141              	systick_ms_setup:
 142              	.LFB4:
  44:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  45:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /*
  46:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * systick_setup(void)
  47:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
  48:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * This function sets up the 1khz "system tick" count. The SYSTICK counter is a
  49:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * standard feature of the Cortex-M series.
  50:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  */
  51:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** void systick_ms_setup(void)
  52:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** {
 143              		.loc 1 52 1
 144              		.cfi_startproc
 145              		@ args = 0, pretend = 0, frame = 0
 146              		@ frame_needed = 1, uses_anonymous_args = 0
 147 0000 80B5     		push	{r7, lr}	@
 148              		.cfi_def_cfa_offset 8
 149              		.cfi_offset 7, -8
 150              		.cfi_offset 14, -4
 151 0002 00AF     		add	r7, sp, #0	@,,
 152              		.cfi_def_cfa_register 7
 153              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:54: 	syst
  53:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	/* clock rate / 1000 to get 1mS interrupt rate */
  54:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	systick_set_reload(32000);
 154              		.loc 1 54 2
 155 0004 4FF4FA40 		mov	r0, #32000	@,
 156 0008 FFF7FEFF 		bl	systick_set_reload		@
 157              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:55: 	syst
  55:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
 158              		.loc 1 55 2
 159 000c 0420     		movs	r0, #4	@,
 160 000e FFF7FEFF 		bl	systick_set_clocksource		@
 161              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:56: 	syst
  56:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	systick_counter_enable();
 162              		.loc 1 56 2
 163 0012 FFF7FEFF 		bl	systick_counter_enable		@
 164              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:58: 	syst
  57:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	/* this done last */
  58:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	systick_interrupt_enable();
 165              		.loc 1 58 2
 166 0016 FFF7FEFF 		bl	systick_interrupt_enable		@
 167              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:59: }
  59:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** }
 168              		.loc 1 59 1
 169 001a 00BF     		nop	
 170 001c 80BD     		pop	{r7, pc}	@
 171              		.cfi_endproc
 172              	.LFE4:
 174              		.section	.text.sys_tick_handler,"ax",%progbits
 175              		.align	1
 176              		.global	sys_tick_handler
 177              		.syntax unified
 178              		.thumb
 179              		.thumb_func
 180              		.fpu fpv5-d16
 182              	sys_tick_handler:
 183              	.LFB5:
  60:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  61:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  62:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /**
  63:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  * Private functions
  64:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c ****  *
  65:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** */
  66:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  67:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 
  68:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** /* Called when systick fires */
  69:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** void sys_tick_handler(void)
  70:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** {
 184              		.loc 1 70 1
 185              		.cfi_startproc
 186              		@ args = 0, pretend = 0, frame = 0
 187              		@ frame_needed = 1, uses_anonymous_args = 0
 188              		@ link register save eliminated.
 189 0000 80B4     		push	{r7}	@
 190              		.cfi_def_cfa_offset 4
 191              		.cfi_offset 7, -4
 192 0002 00AF     		add	r7, sp, #0	@,,
 193              		.cfi_def_cfa_register 7
 194              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:71: 	syst
  71:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** 	system_millis++;
 195              		.loc 1 71 15
 196 0004 044B     		ldr	r3, .L7	@ tmp115,
 197 0006 1B68     		ldr	r3, [r3]	@ system_millis.2_1, system_millis
 198 0008 0133     		adds	r3, r3, #1	@ _2, system_millis.2_1,
 199 000a 034A     		ldr	r2, .L7	@ tmp116,
 200 000c 1360     		str	r3, [r2]	@ _2, system_millis
 201              	@ /home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c:72: }
  72:/home/silvere/Work/Tuto/STM32_Projects/STM32_Project_Template/drivers/systick/systick.c **** }
 202              		.loc 1 72 1
 203 000e 00BF     		nop	
 204 0010 BD46     		mov	sp, r7	@,
 205              		.cfi_def_cfa_register 13
 206              		@ sp needed	@
 207 0012 5DF8047B 		ldr	r7, [sp], #4	@,
 208              		.cfi_restore 7
 209              		.cfi_def_cfa_offset 0
 210 0016 7047     		bx	lr	@
 211              	.L8:
 212              		.align	2
 213              	.L7:
 214 0018 00000000 		.word	system_millis
 215              		.cfi_endproc
 216              	.LFE5:
 218              		.text
 219              	.Letext0:
 220              		.file 2 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stdint.h"
DEFINED SYMBOLS
                            *ABS*:0000000000000000 systick.c
     /tmp/cciiZXbQ.s:64     .bss.system_millis:0000000000000000 system_millis
     /tmp/cciiZXbQ.s:61     .bss.system_millis:0000000000000000 $d
     /tmp/cciiZXbQ.s:67     .text.msleep:0000000000000000 $t
     /tmp/cciiZXbQ.s:75     .text.msleep:0000000000000000 msleep
     /tmp/cciiZXbQ.s:129    .text.msleep:000000000000002c $d
     /tmp/cciiZXbQ.s:134    .text.systick_ms_setup:0000000000000000 $t
     /tmp/cciiZXbQ.s:141    .text.systick_ms_setup:0000000000000000 systick_ms_setup
     /tmp/cciiZXbQ.s:175    .text.sys_tick_handler:0000000000000000 $t
     /tmp/cciiZXbQ.s:182    .text.sys_tick_handler:0000000000000000 sys_tick_handler
     /tmp/cciiZXbQ.s:214    .text.sys_tick_handler:0000000000000018 $d
                           .group:0000000000000000 wm4.0.9dde8e95e6092cb030e087570b2eb433
                           .group:0000000000000000 wm4.common.h.21.c9066c2f6b12c71b40226ea6107829a4
                           .group:0000000000000000 wm4.stdint.h.29.6d480f4ba0f60596e88234283d42444f
                           .group:0000000000000000 wm4.stdbool.h.29.07dce69c3b78884144b7f7bd19483461
                           .group:0000000000000000 wm4.common.h.67.7078fa5b6ba10a2783937983681b6c24
                           .group:0000000000000000 wm4.memorymap.h.21.8c90486dae5eea2d8efddd23fe5d09d9
                           .group:0000000000000000 wm4.memorymap.h.26.bea6318104dd6e05b39c6e53449db2b7
                           .group:0000000000000000 wm4.timer_common_all.h.38.1e06b1c38b4fa3b42e65fafbbc60bcfd
                           .group:0000000000000000 wm4.systick.h.56.ff3cb6f7cfe77c4455700b686abdae3f
                           .group:0000000000000000 wm4._newlib_version.h.4.1ef4e12f167f8b69d7c30054be56050d
                           .group:0000000000000000 wm4.newlib.h.21.1ae2897bc09bbe4bc80ffb801fb02432
                           .group:0000000000000000 wm4.ieeefp.h.77.3f06799abf5dd88bdddee084775a1223
                           .group:0000000000000000 wm4.features.h.22.0ca0b2e469d5b0fcf64dfa21c188c8f3
                           .group:0000000000000000 wm4.config.h.224.c701144a7b0518c6ee9b9b5465b79f81
                           .group:0000000000000000 wm4._ansi.h.31.de524f58584151836e90d8620a16f8e8
                           .group:0000000000000000 wm4.stdio.h.31.7c0e28c411445f3f9c5b11accf882760
                           .group:0000000000000000 wm4._default_types.h.6.959254cf5f09734ea7516c89e8bb21bd
                           .group:0000000000000000 wm4.stddef.h.181.c3f52a3b0f4c288bddb5dda1562858e2
                           .group:0000000000000000 wm4.cdefs.h.49.3d0fe8ea14e93bda8c589d4f684b21b8
                           .group:0000000000000000 wm4.stddef.h.39.c161261b198ee3a963897077fd6fa59f
                           .group:0000000000000000 wm4.stdarg.h.34.3a23a216c0c293b3d2ea2e89281481e6
                           .group:0000000000000000 wm4._types.h.20.dd0d04dca3800a0d2a6129b87f3adbb2
                           .group:0000000000000000 wm4.stddef.h.155.3588ebfdd1e8c7ede80509bb9c3b8009
                           .group:0000000000000000 wm4._types.h.127.34941de1b2539d59d5cac00e0dd27a45
                           .group:0000000000000000 wm4.reent.h.17.e292bf8b0bec6c96e131a54347145a30
                           .group:0000000000000000 wm4.lock.h.2.c0958401bd0ce484d507ee19aacab817
                           .group:0000000000000000 wm4.reent.h.77.dcd6129ff07fe81bd5636db29abe53b2
                           .group:0000000000000000 wm4.types.h.40.8b6acba56cefbb11746718204edc8f5e
                           .group:0000000000000000 wm4._stdint.h.10.c24fa3af3bc1706662bb5593a907e841
                           .group:0000000000000000 wm4.types.h.98.130d89e96751ac000105a0b2b27ceff8
                           .group:0000000000000000 wm4.stdio.h.2.4aa87247282eca6c8f36f9de33d8df1a
                           .group:0000000000000000 wm4.stdio.h.81.2a55589bfa3ee24eeb84e3c79458e4a9

UNDEFINED SYMBOLS
systick_set_reload
systick_set_clocksource
systick_counter_enable
systick_interrupt_enable
