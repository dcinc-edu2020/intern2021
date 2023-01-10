/*==============================================================================*/
/* LED Driver Header File							*/
/*==============================================================================*/
#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ���[�h�\���pLED */
#define LED0	(PORTB.PODR.BIT.B0)	// �ԑ̏�ʍ�LED
#define LED1	(PORTA.PODR.BIT.B6)	// �ԑ̏�ʍ��OLED
#define LED2	(PORTA.PODR.BIT.B4)	// �ԑ̏�ʉE�OLED
#define LED3	(PORTA.PODR.BIT.B0)	// �ԑ̏�ʉELED

/* ���W�����v���pLED */
#define SLED_L	(PORT5.PODR.BIT.B4)	// ���Z���TLED
#define SLED_R	(PORT0.PODR.BIT.B5)	// �E�Z���TLED
#define SLED_FL	(PORT2.PODR.BIT.B7)	// ���O�Z���TLED
#define SLED_FR	(PORTB.PODR.BIT.B5)	// �E�O�Z���TLED

/* �o�b�e���c�ʕ\���pLED */
#define BLED0	(PORTB.PODR.BIT.B1)	// �o�b�e���d���\��LED ��
#define BLED1	(PORTA.PODR.BIT.B3)	// �o�b�e���d���\��LED ��

/* ���[�h�\��LED�̕\�� */
#define MODE_LED_PATTERN_1	(1)	// LED0:ON�@LED1:OFF�@LED2:OFF�@LED3:OFF�@

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void display_led(int led_mode);		// ���[�h�\��(LED)

#endif