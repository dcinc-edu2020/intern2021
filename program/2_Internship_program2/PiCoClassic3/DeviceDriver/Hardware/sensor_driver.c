/*==============================================================================*/
/* Sensor Driver C File								*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Core/iodefine.h"
#include "DeviceDriver/Hardware/led_driver.h"
#include "DeviceDriver/Hardware/sensor_driver.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
t_sensor	sen_r;		// �E�Z���T�\����
t_sensor	sen_l;		// ���Z���T�\����
t_sensor	sen_fr;		// �E�O�Z���T�\����
t_sensor	sen_fl;		// ���O�Z���T�\����
t_control	con_wall;	// ����\����

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* �Z���T�[�p�����[�^������		                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_sensor(void)
{
	sen_r.ref = REF_SEN_R;			// �E�Z���T�̃��t�@�����X�l��������
	sen_l.ref = REF_SEN_L;			// ���Z���T�̃��t�@�����X�l��������

	sen_r.th_wall = TH_SEN_R;		// �E�Z���T�̕ǗL�����f��臒l��������
	sen_l.th_wall = TH_SEN_L;		// ���Z���T�̕ǗL�����f��臒l��������

	sen_fr.th_wall = TH_SEN_FR;		// �E�O�Z���T�̕ǗL�����f��臒l��������
	sen_fl.th_wall = TH_SEN_FL;		// ���O�Z���T�̕ǗL�����f��臒l��������

	sen_r.th_control = CONTH_SEN_R;		// �E�Z���T�̕ǐ��䂩���邩�ۂ���臒l��������
	sen_l.th_control = CONTH_SEN_L;		// ���Z���T�̕ǐ��䂩���邩�ۂ���臒l��������

	con_wall.kp = CON_WALL_KP;		// �ǔ�ᐧ��̔��萔��������

	return;
}

/*==============================================================================*/
/* ���W�����擾		                                        		*/
/* 										*/
/* �w�肳�ꂽ�Z���T�[��ʂ̕��W�������擾����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		sensor_kind	�Z���T�[���			       	*/
/*  Return   :         	distance	���W����				*/
/*==============================================================================*/
int get_distance(int sensor_kind)
{
	int distance = 0;

	switch(sensor_kind)
	{
		case SENSOR_R:
			distance = sen_r.value;		// �E�����W����
			break;
		case SENSOR_L:
			distance = sen_l.value;		// �������W����
			break;
		case SENSOR_FR:
			distance = sen_fr.value;	// �E�O�����W����
			break;
		case SENSOR_FL:
			distance = sen_fl.value;	// ���O�����W����
			break;
		default:
			break;
	}

	return distance;
}

/*==============================================================================*/
/* PID����L�����ݒ�	                                        		*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_pid_enable(void)
{
	con_wall.enable = true;

	return;
}
/*==============================================================================*/
/* PID���䖳�����ݒ�	                                        		*/
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_pid_disable(void)
{
	con_wall.enable = false;

	return;
}

/*==============================================================================*/
/*  �Z���T�[�ǂݍ��ݗp(CMT1)	           		                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void int_periodic_sensor(void)
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
