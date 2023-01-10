/*==============================================================================*/
/* Wall Exist Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "DeviceDriver/Hardware/sensor_driver.h"
#include "Application/Recognition/distance_recognition.h"
#include "Application/Judgement/wall_exist_judgement.h"

/*------------------------------------------------------------------------------*/
/* Defines									*/
/*------------------------------------------------------------------------------*/
/* �ǂ����邩�ۂ���臒l */
#define THRESHOLD_R_WALL	(TH_SEN_R)	// �E�ǔ���p臒l
#define THRESHOLD_L_WALL	(TH_SEN_L)	// ���ǔ���p臒l
#define THRESHOLD_FR_WALL	(TH_SEN_FR)	// �E�O�ǔ���p臒l
#define THRESHOLD_FL_WALL	(TH_SEN_FL)	// ���O�ǔ���p臒l

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
int existence_front_wall;			// �O�ǗL��
int existence_left_wall;			// ���ǗL��
int existence_right_wall;			// �E�ǗL��

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  ������									*/
/* ---------------------------------------------------------------------------- */
/*  ����:		-							*/
/*  �o��:		existence_front_wall	�O�ǗL��			*/
/*			existence_left_wall	���ǗL��			*/
/*			existence_right_wall	�E�ǗL��			*/
/*==============================================================================*/
void init_wall_exist_judgement(void)
{
	existence_front_wall = NO_WALL;
	existence_left_wall = NO_WALL;
	existence_right_wall = NO_WALL;

	return;
}

/*==============================================================================*/
/*  �O�ǌ��m									*/
/* 										*/
/*  ���E�̑O�����W��������A�O�ǂ̗L���𔻒f����				*/
/* ---------------------------------------------------------------------------- */
/*  ����:		front_right_distance	�E�O�����W����			*/
/*			front_left_distance	���O�����W����			*/
/*  �o��:		existence_front_wall	�O�ǗL��			*/
/*==============================================================================*/
void judgement_existence_front_wall(void)
{
	// �O�ǂ���̋����ɏ]���ǂ̗L���𔻒f
	existence_front_wall = WALL;
	if( (front_right_distance < THRESHOLD_FR_WALL) && (front_left_distance < THRESHOLD_FL_WALL) )
	{
		existence_front_wall =  NO_WALL;
	}

	return;
}

/*==============================================================================*/
/*  ���ǌ��m									*/
/* 										*/
/*  �������W��������A���ǂ̗L���𔻒f����					*/
/* ---------------------------------------------------------------------------- */
/*  ����:		leftside_distance	�������W����			*/
/*  �o��:		existence_left_wall	���ǗL��			*/
/*==============================================================================*/
void judgement_existence_left_wall(void)
{
	// ���ǂ���̋����ɏ]���ǂ̗L���𔻒f
	existence_left_wall = WALL;
	if(leftside_distance < THRESHOLD_L_WALL)
	{
		existence_left_wall = NO_WALL;
	}

	return;
}

/*==============================================================================*/
/*  �E�ǌ��m									*/
/* 										*/
/*  �E�Ǖ��W��������A�E�ǂ̗L���𔻒f����					*/
/* ---------------------------------------------------------------------------- */
/*  ����:		rightside_distance	�E�����W����			*/
/*  �o��:		existence_right_wall	�E�ǗL��			*/
/*==============================================================================*/
void judgement_existence_right_wall(void)
{
	// �E�ǂ���̋����ɏ]���ǂ̗L���𔻒f
	existence_right_wall = WALL;
	if(rightside_distance < THRESHOLD_R_WALL)
	{
		existence_right_wall = NO_WALL;
	}

	return;
}