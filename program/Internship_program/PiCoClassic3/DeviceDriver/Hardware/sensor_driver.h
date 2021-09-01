/*==============================================================================*/
/* Sesor Driver Header File							*/
/*==============================================================================*/
#ifndef _SENSOR_DRIVER_H
#define _SENSOR_DRIVER_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �Z���T�[��� */
#define SENSOR_R	(0)	// �E�����W�����Z���T�[
#define SENSOR_L	(1)	// �������W�����Z���T�[
#define SENSOR_FR	(2)	// �E�O�����W�����Z���T�[
#define SENSOR_FL	(3)	// ���O�����W�����Z���T�[

/* �Z���T�֘A�p�����[�^ */
#define WAITLOOP_SLED	300				// LED�����点�Ă���AD�ϊ����J�n����܂ł̎��ԉ҂��p�萔

// �}�E�XD �p�����[�^
#define REF_SEN_R	1704				// �}�E�X����H�����ɒu�������̃Z���T�̒l
#define REF_SEN_L	1728				// �}�E�X����H�����ɒu�������̃Z���T�̒l

#define TH_SEN_R	1660				// �ǂ����邩�ۂ���臒l
#define TH_SEN_L	1677				// �ǂ����邩�ۂ���臒l
#define TH_SEN_FR	1661				// �ǂ����邩�ۂ���臒l
#define TH_SEN_FL	1671				// �ǂ����邩�ۂ���臒l

#define CONTH_SEN_R	TH_SEN_R			// ����������邩�ۂ���臒l
#define CONTH_SEN_L	TH_SEN_L			// ����������邩�ۂ���臒l
#define CON_WALL_KP	(0.3)				// �ǃZ���T�ɂ��p������̔�ᐧ��̔��萔

/* �֐��}�N�� */
#define CONV_SEN2WALL(w) ((w) ? WALL : NOWALL)		// �Z���T��񂩂�Ǐ��֕ϊ�

/*------------------------------------------------------------------------------*/
/* Type Definitions								*/
/*------------------------------------------------------------------------------*/
/* �^�U�l����舵���񋓌^ */
typedef enum
{
	false = 0,		// �U
	true = 1,		// �^
}t_bool;

/* �Z���T�\���� */
typedef struct
{
	short value;		// ���݂̒l
	short p_value;		// 1mS�ߋ��̒l
	short error;		// value - ref
	short ref;		// ���t�@�����X�l
	short th_wall;		// �ǂ����邩�ۂ���臒l
	short th_control;	// ����������邩�ۂ���臒l
	t_bool is_wall;		// �ǂ����邩������ ( true = �ǂ��� false = �ǂȂ� )
	t_bool is_control;	// ����Ɏg�����ۂ�
}t_sensor;

/* ����\���� */
typedef struct
{
	float control;		// �ŏI�I�Ȑ����
	float error;		// �΍�
	float p_error;		// �ߋ��̕΍�
	float diff;		// �΍��̔����l
	float sum;		// �΍��̐ϕ��l
	float sum_max;		// �ϕ��l�̐����l
	float kp;		// ��ᐧ��萔
	float kd;		// ��������萔
	float ki;		// �ϕ�����萔
	t_bool enable;		// �����on/off
}t_control;

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/
extern t_sensor	sen_r;		// �E�Z���T�\����
extern t_sensor	sen_l;		// ���Z���T�\����
extern t_sensor	sen_fr;		// �E�O�Z���T�\����
extern t_sensor	sen_fl;		// ���O�Z���T�\����
extern t_control	con_wall;	// ����\����

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_sensor(void);			// �Z���T�[�p�����[�^������
int get_distance(int sensor_kind);	// ���W�����擾
void set_pid_enable(void);		// PID����L�����ݒ�
void set_pid_disable(void);		// PID���䖳�����ݒ�

#endif