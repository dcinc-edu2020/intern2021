/*==============================================================================*/
/* Buzzer Driver C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Core/iodefine.h"
#include "DeviceDriver/Hardware/buzzer_driver.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ブザー ON/OFF */
#define BZ_ON           (1)                     // ブザー ON
#define BZ_OFF          (0)			// ブザー OFF

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ブザー周波数設定								*/
/* 										*/
/* ブザーの周波数を設定する							*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		frequency	ブザー周波数			       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_buzzer_freq(unsigned short frequency)
{
	// ブザーの発振周波数を算出して設定
	MTU0.TGRB = (unsigned short)(12000000 / (frequency));
	MTU0.TGRA = (unsigned short)(6000000  / (frequency));

	return;
}

/*==============================================================================*/
/* ブザー発振開始								*/
/* 										*/
/* ブザーを吹鳴させる								*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void buzzer_on(void)
{
	// ブザーの発振を開始
	PORTB.PMR.BIT.B3  = BZ_ON;
	MTU.TSTR.BIT.CST0 = BZ_ON;

	return;
}

/*==============================================================================*/
/* ブザー発振停止								*/
/* 										*/
/* ブザー吹鳴を停止させる							*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void buzzer_off(void)
{
	//ブザーの発振を停止
	PORTB.PMR.BIT.B3  = BZ_OFF;
	MTU.TSTR.BIT.CST0 = BZ_OFF;

	return;
}