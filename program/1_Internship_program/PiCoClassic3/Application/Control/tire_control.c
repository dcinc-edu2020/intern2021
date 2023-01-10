/*==============================================================================*/
/* Tire Control C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "motor_driver.h"
#include "sensor_driver.h"
#include "run_mode_judgement.h"
#include "tire_control.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
enum RUN_MODE run_mode = Stop;

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* �^�C������			                                        	*/
/* 										*/
/* ���s���[�h�ɉ����ă^�C�����䂷��						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		run_mode		���s���[�h		       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void tire_control(void)
{			
	/* ���䏈�� */
	switch(run_mode)
	{
		case Forward:		// ���i����
			run_straight(SECTION, DEFAULT_SPEED);		// 1��撼�i����
			break;
		case TurnRight:		// �E���񐧌�
			run_straight(HALF_SECTION, MIN_SPEED);		// 0.5��撼�i����i����O�Ɍ�������j
			run_rotate(TURN_RIGHT, TURN_90);		// ���̏��90�x�E���񂷂�
			run_straight(HALF_SECTION, DEFAULT_SPEED);	// 0.5��撼�i����i�����ɉ�������j
			break;		
		case TurnLeft:		// �����񐧌�
			run_straight(HALF_SECTION, MIN_SPEED);		// 0.5��撼�i����i����O�Ɍ�������j
			run_rotate(TURN_LEFT, TURN_90);			// ���̏��90�x�����񂷂�
			run_straight(HALF_SECTION, DEFAULT_SPEED);	// 0.5��撼�i����i�����ɉ�������j			
			break;	
		case Reverse:		// ���]����
			run_straight(HALF_SECTION, MIN_SPEED);		// 0.5��撼�i����i����O�Ɍ�������j
			run_rotate(TURN_RIGHT, TURN_180);		// ���̏��180�x�E���񂷂�
			run_straight(HALF_SECTION, DEFAULT_SPEED);	// 0.5��撼�i����i�����ɉ�������j
			break;
		case Stop:		// ��~����
			break;	
		default:
			break;
	}
	
	return;
}

/*==============================================================================*/
/*  �^�C������(���i)			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		distance		���s���� [mm]			*/
/*			target_speed		�ڕW���x(�����E�����̐ݒ�)	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void run_straight(int distance, float target_speed)
{
	/* ���s���������� */
	unsigned int mileage_r = 0;		// �E���[�^�[�̑��s����[mm]
	unsigned int mileage_l = 0;		// �����[�^�[�̑��s����[mm]
	
	/* ���[�^�̋쓮�����̐ݒ� */
	set_motor_direction_r(MOT_FORWARD);	// �E���[�^�[�쓮�����F���]
	set_motor_direction_l(MOT_FORWARD);	// �����[�^�[�쓮�����F���]
	
	/* ���i���͕ǐ���iPID����j��L���ɂ��� */
	set_pid_enable();
	
	/* ���[�^�[�쓮 */
	reset_motor_step();			// �X�e�b�s���O���[�^�[�̃X�e�b�v���J�E���g�����Z�b�g
	start_motor_control();			// ���[�^�[��]�J�n
		
	/* �ڕW�n�_�܂ő��s */
	while( ((mileage_r + mileage_l) / 2) < distance)	// �֍s���s�����l�����ĉE���[�^�[�ƍ����[�^�[�̑��s�����̕��ϒl�Ŕ���
	{
		/* �������̐ݒ� */
		control_accel(distance, target_speed);		// �������n�߂�K�v�����鋗���ɒB�����ꍇ�A�����x���}�C�i�X�ɐݒ肷�� 
		
		/* �e�X�e�b�s���O���[�^�[�̌��݂܂ł̑��s�������擾 */
		mileage_r = get_mileage_step(MOTOR_RIGHT);
		mileage_l = get_mileage_step(MOTOR_LEFT);		
	}
	
	stop_motor_control();	// ���[�^�[��]��~
	
	return;
}
/*==============================================================================*/
/*  �^�C������(����)			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		rotate_direction	��]�����i�E/���j		*/
/*			rotate_angle		��]�p�x�i90�x/180�x�j		*/
/*  Return   :         	-							*/
/*==============================================================================*/
void run_rotate(int rotate_direction, int rotate_angle)
{
	/* �ڕW���s�����Z�o */
	unsigned int distance = (TREAD_WIDTH * PI) / (360 / rotate_angle);	// �g���b�h���~��/ (360 / �p�x)
	
	/* ���s���������� */
	unsigned int mileage_r = 0;		// �E���[�^�[�̑��s����[mm]
	unsigned int mileage_l = 0;		// �����[�^�[�̑��s����[mm]

	/* ���[�^�̋쓮�����̐ݒ� */
	switch(rotate_direction)
	{
		case TURN_RIGHT:
			set_motor_direction_r(MOT_BACK);	// �E���[�^�[�쓮�����F�t�]
			set_motor_direction_l(MOT_FORWARD);	// �����[�^�[�쓮�����F���]
			break;
		case TURN_LEFT:
			set_motor_direction_r(MOT_FORWARD);	// �E���[�^�[�쓮�����F���]
			set_motor_direction_l(MOT_BACK);	// �����[�^�[�쓮�����F�t�]
			break;
		default:
			return;
			break;
	}
	
	/* ���񒆂͕ǐ���iPID����j�𖳌��ɂ��� */
	set_pid_disable();
	
	/* ���x�ݒ� */
	float target_speed = MIN_SPEED;		// �ڕW���x(�Œ�)�c30mm/s
	set_r_accel(TURN_ACCEL);		// �����x�ݒ�

	/* ���[�^�[�쓮 */
	reset_motor_step();			// �X�e�b�s���O���[�^�[�̃X�e�b�v���J�E���g�����Z�b�g
	wait_ms(250);				// �����Ȃ���Ǝp���������̂ŁA�����ҋ@
	start_motor_control();			// ���[�^�[��]�J�n
		
	/* �ڕW�n�_�܂ő��s */
	while( ((mileage_r + mileage_l) / 2) < distance)	// �֍s���s�����l�����ĉE���[�^�[�ƍ����[�^�[�̑��s�����̕��ϒl�Ŕ���
	{
		/* �������̐ݒ� */
		control_accel_turn(distance, target_speed);	// �������n�߂�K�v�����鋗���ɒB�����ꍇ�A�����x���}�C�i�X�ɐݒ肷�� 
		
		/* �e�X�e�b�s���O���[�^�[�̌��݂܂ł̑��s�������擾 */
		mileage_r = get_mileage_step(MOTOR_RIGHT);
		mileage_l = get_mileage_step(MOTOR_LEFT);		
	}
	
	stop_motor_control();	// ���[�^�[��]��~
	wait_ms(250);		// �����A�����ҋ@
	
	return;
}

/*==============================================================================*/
/* ���s���[�h�ݒ�			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		set_run_mode		���s���[�h			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_run_mode(enum RUN_MODE set_run_mode)
{
	run_mode = set_run_mode;
	
	return;
}