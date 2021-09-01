/*==============================================================================*/
/* Main C File									*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "init.h"
#include "buzzer_driver.h"
#include "motor_driver.h"
#include "led_driver.h"
#include "switch_driver.h"
#include "scheduler.h"

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void main(void);					// ���C���֐�
void sound_buzzer_enter(void);				// �u�U�[����(����{�^��)
void execute_program(void);				// �v���O�������s

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ���C���֐�									*/
/* 										*/
/* �e���[�h�I���X�C�b�`�̉������e�ɉ����āA�v���O�����̓���𐧌䂷��		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void main(void)
{
	/* �X�C�b�`��ԏ����� */
	int switch_state_left   = SW_OFF;	// ���X�C�b�`(��)�̏��
	int switch_state_center = SW_OFF;	// �����X�C�b�`(��)�̏��
	int switch_state_right  = SW_OFF;	// �E�X�C�b�`(��)�̏��
	
	/* �S�̏����� */
	init_all();

	/* �X�C�b�`�̓��͎�t */	
	while(1)
	{
		wait_ms(CHATTERING_WAIT*3);		// �`���^�����O�h�~�̑҂�����
		motor_power_off();			// �X�e�b�s���O���[�^�[��E��
		buzzer_off();				// �u�U�[�̔��U���~������

		while( !(switch_state_left & switch_state_center & switch_state_right) )
		{
			// �X�C�b�`���������܂ő҂�
			switch_state_left   = get_switch_state(MODE_SW_RED);
			switch_state_center = get_switch_state(MODE_SW_YELLOW);
			switch_state_right  = get_switch_state(MODE_SW_BLUE);
		}		

		wait_ms(CHATTERING_WAIT);		// �`���^�����O�h�~�̑҂�����

		display_led(MODE_LED_PATTERN_1);	// �ԑ̑O����LED��\������

		while( (switch_state_left & switch_state_center & switch_state_right) )
		{
			// �����ꂩ�̃X�C�b�`���������܂ő҂�
			switch_state_left   = get_switch_state(MODE_SW_RED);
			switch_state_center = get_switch_state(MODE_SW_YELLOW);
			switch_state_right  = get_switch_state(MODE_SW_BLUE);
		}
		
		sound_buzzer_enter();			// ����X�C�b�`�������ꂽ�Ƃ��̉���炷
		execute_program();			// �v���O���������s����
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
void sound_buzzer_enter(void)
{
	set_buzzer_freq(DEC_FREQ);		// ��(���g��)��ύX����@�i�s�j
	buzzer_on();				// �u�U�[�𔭐U������
	wait_ms(80);				// �K���ȑ҂�����
	
	set_buzzer_freq(INC_FREQ);		// ��(���g��)��ύX����@�i���b�j
	wait_ms(80);				// �K���ȑ҂�����
	buzzer_off();				// �u�U�[�̔��U���~������
	
	return;
}

/*==============================================================================*/
/* �v���O�������s								*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void execute_program(void)
{
	/* �X�e�b�s���O���[�^�[��㎥ */
	motor_power_on();
	
	/* ����������s */
	task_routine();
	
	/* �X�e�b�s���O���[�^�[��E�� */
	motor_power_off();
	
	return;
}
