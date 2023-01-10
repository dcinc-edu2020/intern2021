/*==============================================================================*/
/* Wall Exist Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "sensor_driver.h"
#include "wall_exist_judgement.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �ǂ����邩�ۂ���臒l */
#define THRESHOLD_R_WALL	(TH_SEN_R)	// �E�ǔ���p臒l
#define THRESHOLD_L_WALL	(TH_SEN_L)	// ���ǔ���p臒l
#define THRESHOLD_FR_WALL	(TH_SEN_FR)	// �E�O�ǔ���p臒l
#define THRESHOLD_FL_WALL	(TH_SEN_FL)	// ���O�ǔ���p臒l


/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  �O�ǌ��m				                                        */
/* 										*/
/*  ���E�̑O�����W��������A�O�ǂ̗L���𔻒f����				*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		front_right_distance	�E�O�����W����		       	*/
/*  			front_left_distance	���O�����W����			*/
/*  Return   :         	existence_front_wall	�O�ǗL��			*/
/*			(WALL / NO_WALL)				        */
/*==============================================================================*/
int judgement_existence_front_wall(int front_right_distance, int front_left_distance)
{
	int existence_front_wall = WALL;		// �����l�͕ǗL��ɐݒ�
		
	// �O�ǂ̗L���𔻒f
	if( (front_right_distance < THRESHOLD_FR_WALL) && (front_left_distance < THRESHOLD_FL_WALL) )
	{
		existence_front_wall =  NO_WALL;	// �ǖ���
	}
	
	return existence_front_wall;
}

/*==============================================================================*/
/*  ���ǌ��m				                                        */
/* 										*/
/*  �������W��������A���ǂ̗L���𔻒f����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		leftside_distance	�������W����		       	*/
/*  Return   :         	existence_left_wall	���ǗL��			*/
/*			(WALL / NO_WALL)				        */
/*==============================================================================*/
int judgement_existence_left_wall(int leftside_distance)
{
	int existence_left_wall = WALL;		// �����l�͕ǗL��ɐݒ�
	
	// ���ǂ̗L���𔻒f
	if(leftside_distance < THRESHOLD_L_WALL)
	{
		existence_left_wall = NO_WALL;		// �ǖ���
	}
	
	return existence_left_wall;
}

/*==============================================================================*/
/*  �E�ǌ��m				                                        */
/* 										*/
/*  �E�Ǖ��W��������A�E�ǂ̗L���𔻒f����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		rightside_dictance	�E�����W����		       	*/
/*  Return   :         	existence_right_wall	�E�ǗL��			*/
/*			(WALL / NO_WALL)				        */
/*==============================================================================*/
int judgement_existence_right_wall(int rightside_dictance)
{
	int existence_right_wall = WALL;		// �����l�͕ǗL��ɐݒ�
	
	// �E�ǂ̗L���𔻒f
	if(rightside_dictance < THRESHOLD_R_WALL)	
	{
		existence_right_wall = NO_WALL;		// �ǖ���
	}
	
	return existence_right_wall;
}