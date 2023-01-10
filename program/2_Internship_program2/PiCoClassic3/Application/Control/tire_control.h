/*==============================================================================*/
/* Tire Control Header File							*/
/*==============================================================================*/
#ifndef TIRE_CONTROL_H
#define TIRE_CONTROL_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* ������� */
#define TURN_RIGHT	(0)
#define TURN_LEFT	(1)

/* �쓮���� */
#define HALF_SECTION	(90)	// �����̋���(mm)
#define SECTION		(180)	// 1���̋���(mm)
#define TURN_90		(90)	// �^�[���p�x90�x
#define TURN_180	(180)	// �^�[���p�x180�x

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_tire_control(void);					// �^�C�����䏉����
void tire_control(void);					// �^�C������
void run_straight(int distance, float target_speed);		// �^�C������(���i)
void run_rotate(int rotate_direction, int rotate_angle);	// �^�C������(����)

#endif