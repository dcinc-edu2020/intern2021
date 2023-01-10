/*==============================================================================*/
/* Wall Exist Judgement Header File						*/
/*==============================================================================*/
#ifndef _WALL_EXIST_JUDGEMENT_H
#define _WALL_EXIST_JUDGEMENT_H

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �ǗL�����茋�� */
#define	WALL	(0)	// �ǗL��
#define	NO_WALL	(1)	// �ǖ���

/*------------------------------------------------------------------------------*/
/* Function Prototype								*/
/*------------------------------------------------------------------------------*/
int judgement_existence_front_wall(int front_right_distance, int front_left_distance);	// �O�ǌ��m
int judgement_existence_left_wall(int leftside_distance);				// ���ǌ��m
int judgement_existence_right_wall(int rightside_dictance);				// �E�ǌ��m

#endif
