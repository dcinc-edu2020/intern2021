/*==============================================================================*/
/* Battery Driver C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Core/iodefine.h"
#include "DeviceDriver/Hardware/led_driver.h"
#include "DeviceDriver/Hardware/motor_driver.h"
#include "DeviceDriver/Hardware/buzzer_driver.h"
#include "DeviceDriver/Hardware/battery_driver.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* バッテリー電圧閾値 */
#define BATT_MAX	(2552)		// 12.4 [V]
#define BATT_MIN	(2034)		// 10.0 [V]

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* バッテリー電圧取得					                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :         	battery_volt	バッテリー電圧				*/
/*==============================================================================*/
unsigned short get_battery_volt(void)
{
	unsigned short battery_volt = S12AD.ADDR8;

	S12AD.ADANS0.BIT.ANS0 = 0x0100;	// AN008
	S12AD.ADCSR.BIT.ADST  = 1;	// AD変換開始

	while(S12AD.ADCSR.BIT.ADST)
	{
		// AD変換終了まで待つ
	}

	return battery_volt;
}

/*==============================================================================*/
/* バッテリー電圧監視								*/
/* 										*/
/* バッテリー電圧に応じて、周辺ハードウェアを制御する				*/
/*  ※ CMT2 割込みから実行される						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		battery_volt	バッテリー電圧			       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void save_battery(unsigned short battery_volt)
{
	// バッテリ電圧監視用LEDのPWM用変数
	static int bled_cnt = 0;

	// バッテリ電圧表示
	bled_cnt++;

	if(bled_cnt > 10){
		bled_cnt= 0;
	}

	if( (10.0 * (battery_volt - BATT_MIN) / (BATT_MAX - BATT_MIN)) > bled_cnt ){
		BLED0 = 1;
		BLED1 = 0;
	}else{
		BLED0 = 0;
		BLED1 = 1;
	}

	if(battery_volt < BATT_MIN)
	{
		set_buzzer_freq(400);	// 値が増加した時の周波数を設定
		buzzer_on();		// ブザーを発振する
		motor_power_off();	// モータを停止する
		LED0 = LED1 = LED2 = LED3 = SLED_L = SLED_FL = SLED_FR = SLED_R = 0;	// LEDを停止する
	}

	return;
}