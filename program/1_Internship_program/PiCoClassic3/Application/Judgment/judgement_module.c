/*==============================================================================*/
/* Judgement Module C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "distance_recognition.h"
#include "wall_exist_judgement.h"
#include "goal_judgement.h"
#include "run_mode_judgement.h"
#include "judgement_module.h"

/*------------------------------------------------------------------------------*/
/* Externs Variable								*/
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/* ���f					                                        */
/* 										*/
/* �F�m�O���[�v����^������������ƂɁA�}�C�N���}�E�X�̈ړ������邽�߂�	*/
/* �o�͂𐧌䂷�������W�P�ʂŔ��f����						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void judgement(void)
{
	int existence_right_wall;	// �E�ǗL�����f����
	int existence_left_wall;	// ���ǗL�����f����
	int existence_front_wall;	// �O�ǗL�����f����
	int goal_judgement_result;	// �S�[�����茋��
	
	/* �ǌ��m */
	existence_right_wall = judgement_existence_right_wall(rightside_dictance);			// �E�ǌ��m
	existence_left_wall  = judgement_existence_left_wall(leftside_distance);			// ���ǌ��m
	existence_front_wall = judgement_existence_front_wall(front_left_distance, front_right_distance);// �O�ǌ��m

	/* �S�[�����m */ 
	goal_judgement_result = judgement_goal(existence_front_wall, existence_left_wall, existence_right_wall);
	
	/* ���s���[�h���� */
	judgement_run_mode(existence_front_wall, existence_left_wall, existence_right_wall, goal_judgement_result);

	return;
}