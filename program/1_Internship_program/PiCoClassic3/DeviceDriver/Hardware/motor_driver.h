/*==============================================================================*/
/* Motor Driver Header File							*/
/*==============================================================================*/
#ifndef _MOTOR_DRIVER_H
#define _MOTOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ���[�^�[��� */
#define MOTOR_RIGHT	(0)	// �E�X�e�b�s���O���[�^�[
#define MOTOR_LEFT	(1)	// ���X�e�b�s���O���[�^�[

/* ���[�^�쓮�p�p�����[�^ */
#define MOT_FORWARD	(0)	// ���[�^�h���C�o��CWCCW�[�q��LOW���o�͂���ƑO�i����
#define MOT_BACK	(1)	// ���[�^�h���C�o��CWCCW�[�q��HIGH���o�͂���ƃo�b�N����

/* �����I�ȃp�����[�^ */
#define TIRE_DIAMETER	(48.0)			// �^�C���̒��a [mm]
#define TREAD_WIDTH	(65.0+4.2)		// �g���b�h�� [mm]
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)	// ���M�n����̎��Ƀ^�C������������
#define PI 		(3.141592653589793)	// �~����
#define TIRE_CIRCUIT	(PI*TIRE_DIAMETER)	//�^�C���̉~���c���a����Z�o(PI�͉~����)

/* ���s�p�����[�^ */
#define MIN_SPEED	(30)			// �Œᑬ�x.�W�F�l�������W�X�^��16bit�ł��邱�ƂƁAMTU�̓�����g�����狁�߂���l�������悻18mm/s�Ȃ̂ŁA�]�T��������30mm/s
#define DEFAULT_ACCEL	(1.5)			// ���s�̉����x
#define DEFAULT_SPEED	(400)			// ���s���x 400[mm/s]
#define MAX_SPEED	(400)			// �ō����x 400[mm/s]
#define TURN_ACCEL	(0.3)			// ���M�n����̉����x
#define TURN_SPEED	(400)			// ���M�n����̍ō����̃��~�b�g

/* �֐��}�N�� */
#define SPEED2GREG(v)	(7500/(((v)/TIRE_CIRCUIT)))		//�X�s�[�h����W�F�l�������W�X�^�̒l���v�Z

/*------------------------------------------------------------------------------*/
/* Variable Externs								*/
/*------------------------------------------------------------------------------*/
extern	unsigned int	step_r;			// �E���[�^�[�X�e�b�v��(���荞�ݓ��ŃJ�E���g�A�b�v)
extern	unsigned int	step_l;			// �����[�^�[�X�e�b�v��(���荞�ݓ��ŃJ�E���g�A�b�v)
extern	float		accel;			// �����x(�ݒ�l�������Ȃ�)
extern	float		r_accel;		// �����x(���ۂ̒l����������)
extern	float		max_speed;		// �ō����x(�ݒ�l)
extern	float		min_speed;		// �Œᑬ�x(�ݒ�l)
extern	float		speed;			// ���x(���݂̒l)

/*------------------------------------------------------------------------------*/
/* Function prototype								*/
/*------------------------------------------------------------------------------*/
void init_motor(void);						// ���[�^�[����p�p�����[�^������
void motor_power_on(void);					// ���[�^�[�㎥
void motor_power_off(void);					// ���[�^�[�E��
void set_motor_direction_r(int motor_direction);		// �E���[�^�[��]�����ݒ�
void set_motor_direction_l(int motor_direction);		// �����[�^�[��]�����ݒ�
void reset_motor_step(void);					// ���[�^�[�X�e�b�v�����Z�b�g
void start_motor_control(void);					// ���[�^�[��]�J�n
void stop_motor_control(void);					// ���[�^�[��]��~
unsigned int get_motor_step(float distance);			// ���s�X�e�b�v���擾
unsigned int get_mileage_step(int motor_kind);			// ���[�^�[���s�����擾
void set_current_speed(float set_speed);			// ���ݑ��x�ݒ�
void set_max_speed(float set_speed);				// �ō����x�ݒ�
void set_min_speed(float set_speed);				// �Œᑬ�x�ݒ�
void control_accel(int mileage, float target_speed);		// �����x�ݒ�
void control_accel_turn(int mileage, float target_speed);	// �����x�ݒ�i����j
void set_accel(float set_accel);				// �����x�ݒ�
void set_r_accel(float set_accel);				// �����x�ݒ�

#endif