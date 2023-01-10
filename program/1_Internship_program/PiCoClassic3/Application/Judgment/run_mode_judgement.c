/*==============================================================================*/
/* Run Mode Judgement C File							*/
/*==============================================================================*/

/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "goal_judgement.h"
#include "wall_exist_judgement.h"
#include "tire_control.h"
#include "run_mode_judgement.h"

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/

/*==============================================================================*/
/*  ���s���[�h����			                                        */
/* 										*/
/*  �i�s���������肷��								*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		existence_front_Wall	�O�ǗL��		       	*/
/*  			existence_left_wall	���ǗL��			*/
/*  			existence_right_wall	�E�ǗL��			*/
/*  	         	goal_judgment_result	�S�[�����茋��			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void judgement_run_mode(int existence_front_wall, int existence_left_wall, int existence_right_wall, int goal_judgement_result)
{
	/* ���s���[�h�̌��� */
	if(goal_judgement_result == GOAL)			
	{	
		set_run_mode(Stop);		// �S�[���Ȃ��~
		return;
	}
	
	if(existence_left_wall == NO_WALL)		// ���ɕǂ������Ȃ獶����
	{	
		set_run_mode(TurnLeft);
	}
	else if(existence_front_wall == NO_WALL)	// �O�ɕǂ������Ȃ�O�i
	{	
		set_run_mode(Forward);
	}
	else if(existence_right_wall == NO_WALL)	// �E�ɕǂ������Ȃ�E����
	{	
		set_run_mode(TurnRight);
	}
	else						// 3�����̂�����ɂ��ǂ��L��ꍇ�͔��]
	{
		set_run_mode(Reverse);
	}
	
	return;
}