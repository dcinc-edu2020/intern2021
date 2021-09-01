/*==============================================================================*/
/* Interrupt C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "iodefine.h"
#include "led_driver.h"
#include "battery_driver.h"
#include "motor_driver.h"
#include "sensor_driver.h"
#include "interrupt.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  �p������p���荞��(CMT0)	           		                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_cmt0(void)
{
	float spd_r, spd_l;			// �ŏI�I�ȑ��x

	speed+=r_accel; 			// ��������

	if(speed > max_speed)			// �ō����x�𐧌�
	{
		speed = max_speed;
	}


	if(speed < min_speed)			// �Œᑬ�x�𐧌�
	{
		speed = min_speed;
	}


	// �Z���T����
	if(con_wall.enable == true)				// �ǐ��䂪������Ă��邩�`�F�b�N
	{
		
		con_wall.p_error = con_wall.error;			// �ߋ��̕΍���ۑ�
		
		// ���E�̃Z���T���A���ꂼ��g�����Ԃł��邩�ǂ����`�F�b�N���āA�p������̕΍����v�Z
		if( ( sen_r.is_control == true ) && ( sen_l.is_control == true ) )
		{												// �����Ƃ��L���������ꍇ�̕΍����v�Z
			con_wall.error = sen_r.error - sen_l.error;
		}
		else												// �Е��������͗����̃Z���T�������������ꍇ�̕΍����v�Z
		{
			con_wall.error = 2.0 * (sen_r.error - sen_l.error);	// �Е������g�p���Ȃ��̂�2�{����
		}
		
		
		// DI����v�Z
		con_wall.diff = con_wall.error - con_wall.p_error;	// �΍��̔����l���v�Z
		con_wall.sum += con_wall.error;					// �΍��̐ϕ��l���v�Z
		
		if(con_wall.sum > con_wall.sum_max)				// �΍��̐ϕ��l�̍ő�l�𐧌�
		{
			con_wall.sum = con_wall.sum_max;
		}
		else if(con_wall.sum < (-con_wall.sum_max))			// �΍��̐ϕ��l�̍Œ�l�𐧌�
		{
			con_wall.sum = -con_wall.sum_max;
		}
		
		con_wall.control = 0.001 * speed * con_wall.kp * con_wall.error;	// ����ʂ��v�Z
		
		spd_r = speed + con_wall.control;					// ��������E���[�^�̑��x���Ƃ����`�Ŕ��f
		spd_l = speed - con_wall.control;					// ��������E���[�^�̑��x���Ƃ����`�Ŕ��f

	}
	else
	{
		spd_r = speed;
		spd_l = speed;
	}	
	
	if(spd_r < MIN_SPEED)spd_r = MIN_SPEED;
	if(spd_l < MIN_SPEED)spd_l = MIN_SPEED;
		
	MTU3.TGRC = SPEED2GREG(spd_r);			// �E���x(mm/s)����W�F�l�������W�X�^�̒l�ɕϊ����āA�o�b�t�@���W�X�^�ɑ��
	MTU4.TGRC = SPEED2GREG(spd_l);			// �����x(mm/s)����W�F�l�������W�X�^�̒l�ɕϊ����āA�o�b�t�@���W�X�^�ɑ��

}		

/*==============================================================================*/
/*  �Z���T�[�ǂݍ��ݗp(CMT1)	           		                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_cmt1(void)
{
	static int state = 0;	// �ǂݍ��ރZ���T�̃��[�e�[�V�����Ǘ��p�ϐ�
	int i;
	
	switch(state)
	{
		case 0:							// �E�Z���T�ǂݍ���
			SLED_R = 1;					// LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++)	;	// �t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0040;			// AN006
			S12AD.ADCSR.BIT.ADST=1;				// AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			// AD�ϊ��I���܂ő҂�
			SLED_R = 0;					// LED����

			sen_r.p_value = sen_r.value;			// �ߋ��̒l��ۑ�
			sen_r.value = S12AD.ADDR6;			// �l��ۑ�

			if(sen_r.value > sen_r.th_wall)			// �ǂ̗L���𔻒f
			{
				sen_r.is_wall = true;			// �E�ǂ���
			}
			else
			{
				sen_r.is_wall = false;			// �E�ǂȂ�
			}
			
			if(sen_r.value > sen_r.th_control)		// ����������邩�ۂ��𔻒f
			{
				sen_r.error = sen_r.value - sen_r.ref;	// �����������ꍇ�͕΍����v�Z
				sen_r.is_control = true;		// �E�Z���T�𐧌�Ɏg��
			}
			else
			{
				sen_r.error = 0;			// ����Ɏg��Ȃ��ꍇ�͕΍���0�ɂ��Ă���
				sen_r.is_control = false;		// �E�Z���T�𐧌�Ɏg��Ȃ�
			}			
			break;


		case 1:							// �O���Z���T�ǂݍ���
			SLED_FL = 1;					// LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++);		// �t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0010;			// AN004
			S12AD.ADCSR.BIT.ADST=1;				// AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			// AD�ϊ��I���܂ő҂�
			SLED_FL = 0;					// LED����

			sen_fl.p_value = sen_fl.value;			// �ߋ��̒l��ۑ�
			sen_fl.value = S12AD.ADDR4;			// �l��ۑ�

			if(sen_fl.value > sen_fl.th_wall)		// �ǂ̗L���𔻒f
			{
				sen_fl.is_wall = true;			// ���O�ǂ���
			}
			else
			{
				sen_fl.is_wall = false;			// ���O�ǂȂ�
			}
			break;


		case 2:							// �O�E�Z���T�ǂݍ���
			SLED_FR = 1;					// LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++);		// �t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0200;			// AN009
			S12AD.ADCSR.BIT.ADST=1;				// AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			// AD�ϊ��I���܂ő҂�
			SLED_FR = 0;					// LED����

			sen_fr.p_value = sen_fr.value;			// �ߋ��̒l��ۑ�
			sen_fr.value = S12AD.ADDR9;			// �l��ۑ�

			if(sen_fr.value > sen_fr.th_wall)		// �ǂ̗L���𔻒f
			{
				sen_fr.is_wall = true;			// �E�O�ǂ���
			}
			else
			{
				sen_fr.is_wall = false;			// �E�O�ǂȂ�
			}			
			break;


		case 3:							// ���Z���T�ǂݍ���
			SLED_L = 1;					// LED�_��
			for(i = 0; i < WAITLOOP_SLED; i++)	;	// �t�H�g�g�����W�X�^�̉����҂����[�v
			S12AD.ADANS0.BIT.ANS0=0x0004;			// AN002
			S12AD.ADCSR.BIT.ADST=1;				// AD�ϊ��J�n
			while(S12AD.ADCSR.BIT.ADST);			// AD�ϊ��I���܂ő҂�
			SLED_L = 0;					// LED����

			sen_l.p_value = sen_l.value;			// �ߋ��̒l��ۑ�
			sen_l.value = S12AD.ADDR2;			// �l��ۑ�
			
			if(sen_l.value > sen_l.th_wall)			// �ǂ̗L���𔻒f
			{
				sen_l.is_wall = true;			// ���ǂ���
			}
			else
			{
				sen_l.is_wall = false;			// ���ǂȂ�
			}
			
			if(sen_l.value > sen_l.th_control)		// ����������邩�ۂ��𔻒f
			{
				sen_l.error = sen_l.value - sen_l.ref;	// �����������ꍇ�͕΍����v�Z����
				sen_l.is_control = true;		// ���Z���T�𐧌�Ɏg��
			}
			else
			{
				sen_l.error = 0;			// ����Ɏg��Ȃ��ꍇ�͕΍���0�ɂ��Ă���
				sen_l.is_control = false;		// ���Z���T�𐧌�Ɏg��Ȃ�
			}

			break;
	}
	
	state++;		//�S�񂲂ƂɌJ��Ԃ�
	if(state > 3)
	{
		state = 0;
	}
	
	return;	
}

/*==============================================================================*/
/*  1ms�^�C�}�[�p���荞��(CMT2)	           		                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_cmt2(void)
{
	timer++;				// 1mS���ƂɃJ�E���g�A�b�v
	save_battery(get_battery_volt());	// �o�b�e���Ď�
	
	return;
}

/*==============================================================================*/
/* �E���[�^�[�X�e�b�v�J�E���g���荞��(CMT2)					*/
/* 										*/
/* �E���[�^���P�X�e�b�v�i�ޖ��̊��荞��						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_mot_r(void)
{
	step_r++;	// �X�e�b�v�����J�E���g
	return;
}

/*==============================================================================*/
/* �����[�^�[�X�e�b�v�J�E���g���荞��(CMT2)					*/
/* 										*/
/* �����[�^���P�X�e�b�v�i�ޖ��̊��荞��						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_mot_l(void)
{
	step_l++;	// �X�e�b�v�����J�E���g
	return;
}
