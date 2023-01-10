/*********************************************************************
*
* Device     : RX/RX600
*
* File Name  : resetprg.c
*
* Abstract   : Reset Program.
*
* History    : 1.00  (2009-08-07)
*            : 1.10  (2011-02-21)
*            : 1.11  (2011-06-20)
*            : 1.12  (2014-02-20)
*            : 1.20  (2014-10-22)
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2009 (2014) Renesas Electronics Corporation.
* and Renesas Solutions Corp.
*
*********************************************************************/

#include	<machine.h>
#include	<_h_c_lib.h>

#include	"stacksct.h"		// Stack Sizes (Interrupt and User)

extern void _INIT_IOLIB(void);
void PowerON_Reset_PC(void);
void main(void);


#define PSW_init  0x00010000		// PSW bit pattern
#define FPSW_init 0x00000000		// FPSW bit base pattern


#pragma section ResetPRG		// output PowerON_Reset to PResetPRG section

#pragma entry PowerON_Reset_PC


void PowerON_Reset_PC(void)
{
#ifdef __RXV2
	set_extb(__sectop("EXCEPTVECT"));
#endif
	set_intb(__sectop("C$VECT"));

#ifdef __FPU
#ifdef __ROZ					// Initialize FPSW
#define _ROUND 0x00000001			// Let FPSW RMbits=01 (round to zero)
#else
#define _ROUND 0x00000000			// Let FPSW RMbits=00 (round to nearest)
#endif
#ifdef __DOFF
#define _DENOM 0x00000100			// Let FPSW DNbit=1 (denormal as zero)
#else
#define _DENOM 0x00000000			// Let FPSW DNbit=0 (denormal as is)
#endif
	set_fpsw(FPSW_init | _ROUND | _DENOM);
#endif

	_INITSCT();
	_INIT_IOLIB();

	nop();

	set_psw(PSW_init);				// Set Ubit & Ibit for PSW

	main();

	brk();
}

