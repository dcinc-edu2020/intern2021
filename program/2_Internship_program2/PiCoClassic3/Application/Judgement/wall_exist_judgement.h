/*==============================================================================*/
/* Wall Exist Judgement Header File						*/
/*==============================================================================*/
#ifndef WALL_EXIST_JUDGEMENT_H
#define WALL_EXIST_JUDGEMENT_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �ǗL�����茋�� */
#define	WALL	(0)	// �ǗL��
#define	NO_WALL	(1)	// �ǖ���

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/
extern int existence_front_wall;			// �O�ǗL��
extern int existence_left_wall;				// ���ǗL��
extern int existence_right_wall;			// �E�ǗL��

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
void init_wall_exist_judgement(void);			// ������
void judgement_existence_front_wall(void);		// �O�ǌ��m
void judgement_existence_left_wall(void);		// ���ǌ��m
void judgement_existence_right_wall(void);		// �E�ǌ��m

#endif
