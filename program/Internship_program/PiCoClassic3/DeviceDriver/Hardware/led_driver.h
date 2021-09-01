/*==============================================================================*/
/* LED Driver Header File							*/
/*==============================================================================*/
#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* モード表示用LED */
#define LED0	(PORTB.PODR.BIT.B0)	// 車体上面左LED
#define LED1	(PORTA.PODR.BIT.B6)	// 車体上面左前LED
#define LED2	(PORTA.PODR.BIT.B4)	// 車体上面右前LED
#define LED3	(PORTA.PODR.BIT.B0)	// 車体上面右LED

/* 物標距離計測用LED */
#define SLED_L	(PORT5.PODR.BIT.B4)	// 左センサLED
#define SLED_R	(PORT0.PODR.BIT.B5)	// 右センサLED
#define SLED_FL	(PORT2.PODR.BIT.B7)	// 左前センサLED
#define SLED_FR	(PORTB.PODR.BIT.B5)	// 右前センサLED

/* バッテリ残量表示用LED */
#define BLED0	(PORTB.PODR.BIT.B1)	// バッテリ電圧表示LED 青
#define BLED1	(PORTA.PODR.BIT.B3)	// バッテリ電圧表示LED 赤

/* モード表示LEDの表示 */
#define MODE_LED_PATTERN_1	(1)	// LED0:ON　LED1:OFF　LED2:OFF　LED3:OFF　

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void display_led(int led_mode);		// モード表示(LED)

#endif