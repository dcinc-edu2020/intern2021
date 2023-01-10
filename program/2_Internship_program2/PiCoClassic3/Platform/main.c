/*==============================================================================*/
/* Main C File									*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Core/init.h"
#include "DeviceDriver/Hardware/buzzer_driver.h"
#include "DeviceDriver/Hardware/motor_driver.h"
#include "DeviceDriver/Hardware/led_driver.h"
#include "DeviceDriver/Hardware/switch_driver.h"
#include "DeviceDriver/Hardware/sensor_driver.h"
#include "Platform/timer.h"
#include "Platform/scheduler.h"

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void main(void);					// ���C���֐�
static void sound_buzzer_poweron(void);			// �u�U�[����(�d��ON)
static void wait_push_switch(void);			// �X�C�b�`�̉����҂�
static void sound_buzzer_enter(void);			// �u�U�[����(����{�^��)

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ���C���֐�									*/
/* 										*/
/* �e���[�h�I���X�C�b�`�̉������e�ɉ����āA�v���O�����̓���𐧌䂷��		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :		-							*/
/*==============================================================================*/
void main(void)
{
	// ���W�X�^������
	init_core();

	// �h���C�o������
	init_sensor();
	init_motor();

	// �d������ꂽ���̋N������炷
	sound_buzzer_poweron();

	// �X�C�b�`���������܂ő҂��A�����ꂽ��v���O�������N������
	motor_power_off();		// �X�e�b�s���O���[�^�[��E��

	wait_push_switch();		// �X�C�b�`���������܂ő҂�

	display_led(MODE_LED_PATTERN_1); // �ԑ̑O����LED��_������
	sound_buzzer_enter();		// ����X�C�b�`�������ꂽ�Ƃ��̉���炷
	motor_power_on();		// �X�e�b�s���O���[�^�[��㎥

	// �v���O�������s
	task_routine();

	return;
}

/*==============================================================================*/
/* �u�U�[����(�d��ON)								*/
/* 										*/
/* �d����ON�ɂȂ����Ƃ��̉���炷						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :		-							*/
/*==============================================================================*/
static void sound_buzzer_poweron(void)
{
	set_buzzer_freq(INC_FREQ);	// �l�������������̎��g����ݒ�
	buzzer_on();			// �u�U�[�𔭐U������
	wait_ms(80);			// �K���ȑ҂�����
	buzzer_off();			// �u�U�[�̔��U���~������

	return;
}

/*==============================================================================*/
/* �X�C�b�`�̉����҂�								*/
/* 										*/
/* �X�C�b�`���������܂ŃE�F�C�g����						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-							*/
/*  Return   :		-							*/
/*==============================================================================*/
static void wait_push_switch(void)
{
	/* �X�C�b�`��ԏ����� */
	int switch_state_left   = SW_OFF;	// ���X�C�b�`(��)�̏��
	int switch_state_center = SW_OFF;	// �����X�C�b�`(��)�̏��
	int switch_state_right  = SW_OFF;	// �E�X�C�b�`(��)�̏��

	wait_ms(CHATTERING_WAIT*3);		// �`���^�����O�h�~�̑҂�����

	while( !(switch_state_left & switch_state_center & switch_state_right) )
	{
		// �X�C�b�`���������܂ő҂�
		switch_state_left   = get_switch_state(MODE_SW_RED);
		switch_state_center = get_switch_state(MODE_SW_YELLOW);
		switch_state_right  = get_switch_state(MODE_SW_BLUE);
	}

	wait_ms(CHATTERING_WAIT);		// �`���^�����O�h�~�̑҂�����

	while( (switch_state_left & switch_state_center & switch_state_right) )
	{
		// �����ꂩ�̃X�C�b�`���������܂ő҂�
		switch_state_left   = get_switch_state(MODE_SW_RED);
		switch_state_center = get_switch_state(MODE_SW_YELLOW);
		switch_state_right  = get_switch_state(MODE_SW_BLUE);
	}

	return;
}

/*==============================================================================*/
/* �u�U�[����(����{�^��)							*/
/* 										*/
/* ����X�C�b�`�������ꂽ�Ƃ��̉���炷(�s���b��)				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
static void sound_buzzer_enter(void)
{
	set_buzzer_freq(DEC_FREQ);		// ��(���g��)��ύX����@�i�s�j
	buzzer_on();				// �u�U�[�𔭐U������
	wait_ms(80);				// �K���ȑ҂�����

	set_buzzer_freq(INC_FREQ);		// ��(���g��)��ύX����@�i���b�j
	wait_ms(80);				// �K���ȑ҂�����
	buzzer_off();				// �u�U�[�̔��U���~������

	return;
}
